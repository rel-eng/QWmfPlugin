/* META_CREATEPATTERNBRUSH record implementation.

   Copyright (C) 2010 rel-eng

   This file is part of QWmfPlugin.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "MetaCreatepatternbrushRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaCreatepatternbrushRecord::MetaCreatepatternbrushRecord() : MetafileRecord(35, META_CREATEPATTERNBRUSH), type(0), width(0), height(0), widthBytes(0), planes(1), bitsPerPixel(24), patternBits(), patternBitsLength(0)
{
}

MetaCreatepatternbrushRecord::MetaCreatepatternbrushRecord(quint16 width, quint16 height, quint8 bitsPerPixel, const QScopedArrayPointer<quint8> &patternBits, size_t patternBitsLength) : MetafileRecord(35 + patternBitsLength, META_CREATEPATTERNBRUSH), type(0), width(width), height(height), planes(1), bitsPerPixel(bitsPerPixel), patternBits(), patternBitsLength(patternBitsLength)
{
    quint16 wb = (this->width * static_cast<quint16>(bitsPerPixel) + 15)/16;
    this->widthBytes = wb * 2;
    if(patternBitsLength != (this->widthBytes * this->height))
    {
        throw std::runtime_error("Invalid patternBitsLength value");
    }
    if(patternBitsLength > 0)
    {
        QScopedArrayPointer<quint8>(new quint8[patternBitsLength]).swap(this->patternBits);
        memcpy(reinterpret_cast<void *>(this->patternBits.data()), reinterpret_cast<const void *>(patternBits.data()), patternBitsLength);
    }
}

MetaCreatepatternbrushRecord::MetaCreatepatternbrushRecord(QIODevice &device) : MetafileRecord(device), patternBits()
{
    this->type = readUnsignedWord(device);
    this->width = readUnsignedWord(device);
    this->height = readUnsignedWord(device);
    this->widthBytes = readUnsignedWord(device);
    this->planes = readUnsignedByte(device);
    if(this->planes != 1)
    {
        throw std::runtime_error("Invalid patternBitsLength value");
    }
    this->bitsPerPixel = readUnsignedByte(device);
    seekDevice(device, Q_INT64_C(22));
    quint16 wb = (this->width * static_cast<quint16>(this->bitsPerPixel) + 15)/16;
    quint16 realWidthBytes = wb * 2;
    if(realWidthBytes != this->widthBytes)
    {
        throw std::runtime_error("Invalid widthBytes value");
    }
    this->patternBitsLength = this->widthBytes * this->height;
    QScopedArrayPointer<quint8>(new quint8[this->patternBitsLength]).swap(this->patternBits);
    fillBuffer(device, static_cast<qint64>(this->patternBitsLength), reinterpret_cast<void *>(this->patternBits.data()), static_cast<size_t>(this->patternBitsLength));
}

MetaCreatepatternbrushRecord::MetaCreatepatternbrushRecord(const MetaCreatepatternbrushRecord &rhs) : MetafileRecord(rhs), type(rhs.type), width(rhs.width), height(rhs.height), widthBytes(rhs.widthBytes), planes(rhs.planes), bitsPerPixel(rhs.bitsPerPixel), patternBits(), patternBitsLength(rhs.patternBitsLength)
{
    if(rhs.patternBitsLength > 0)
    {
        QScopedArrayPointer<quint8>(new quint8[rhs.patternBitsLength]).swap(this->patternBits);
        memcpy(static_cast<void *>(this->patternBits.data()), static_cast<const void *>(rhs.patternBits.data()), rhs.patternBitsLength);
    }
}

MetaCreatepatternbrushRecord::~MetaCreatepatternbrushRecord()
{
}

MetaCreatepatternbrushRecord & MetaCreatepatternbrushRecord::operator=(const MetaCreatepatternbrushRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator=(rhs);
        this->type = rhs.type;
        this->width = rhs.width;
        this->height = rhs.height;
        this->widthBytes = rhs.widthBytes;
        this->planes = rhs.planes;
        this->bitsPerPixel = rhs.bitsPerPixel;
        this->patternBitsLength = rhs.patternBitsLength;
        if(rhs.patternBitsLength > 0)
        {
            QScopedArrayPointer<quint8>(new quint8[rhs.patternBitsLength]).swap(this->patternBits);
            memcpy(static_cast<void *>(this->patternBits.data()), static_cast<const void *>(rhs.patternBits.data()), rhs.patternBitsLength);
        }
    }
    return *this;
}

quint16 MetaCreatepatternbrushRecord::getWidth() const
{
    return this->width;
}

quint16 MetaCreatepatternbrushRecord::getHeight() const
{
    return this->height;
}

quint8 MetaCreatepatternbrushRecord::getBitsPerPixel() const
{
    return this->bitsPerPixel;
}

QImage MetaCreatepatternbrushRecord::getPattern() const
{
    QImage image(this->width, this->height, QImage::Format_ARGB32);
    if(this->bitsPerPixel == 24)
    {
        for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
        {
            for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
            {
                quint8 blueIn = this->patternBits[row * this->widthBytes + col * 3];
                quint8 greenIn = this->patternBits[row * this->widthBytes + col * 3 + 1];
                quint8 redIn = this->patternBits[row * this->widthBytes + col * 3 + 2];
                image.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
            }
        }
    }
    else
    {
        throw std::runtime_error("Need a palette for non 24-bit per pixel bitmaps");
    }
    return image;
}

QImage MetaCreatepatternbrushRecord::getPattern(const PaletteObject &palette) const
{
    QImage image(this->width, this->height, QImage::Format_ARGB32);
    if(this->bitsPerPixel == 1)
    {
        if(palette.getPaletteEntriesCount() < 2)
        {
            throw std::runtime_error("Palette is too small");
        }
        quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
        for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
        {
            for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
            {
                if ((this->patternBits[row * this->widthBytes + col / 8] & masks[col % 8]) != 0)
                {
                    image.setPixel(col, row, palette.getPaletteEntryColor(1));
                }
                else
                {
                    image.setPixel(col, row, palette.getPaletteEntryColor(0));
                }
            }
        }
    }
    else
    {
        if(this->bitsPerPixel == 4)
        {
            if(palette.getPaletteEntriesCount() < 16)
            {
                throw std::runtime_error("Palette is too small");
            }
            for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
            {
                for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
                {
                    quint8 colorIndex = 0;
                    if ((col & 1) == 0)
                    {
                        colorIndex = this->patternBits[row * this->widthBytes + col / 2];
                        colorIndex = colorIndex >> 4;
                    }
                    else
                    {
                        colorIndex = this->patternBits[row * this->widthBytes + col / 2] & 15;
                    }
                    image.setPixel(col, row, palette.getPaletteEntryColor(colorIndex));
                }
            }
        }
        else
        {
            if(this->bitsPerPixel == 8)
            {
                if(palette.getPaletteEntriesCount() < 256)
                {
                    throw std::runtime_error("Palette is too small");
                }
                for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
                    {
                        quint8 colorIndex = this->patternBits[row * this->widthBytes + col];
                        image.setPixel(col, row, palette.getPaletteEntryColor(colorIndex));
                    }
                }
            }
            else
            {
                if(this->bitsPerPixel == 24)
                {
                    for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
                    {
                        for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
                        {
                            quint8 blueIn = this->patternBits[row * this->widthBytes + col * 3];
                            quint8 greenIn = this->patternBits[row * this->widthBytes + col * 3 + 1];
                            quint8 redIn = this->patternBits[row * this->widthBytes + col * 3 + 2];
                            image.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                        }
                    }
                }
            }
        }
    }
    return image;
}

bool MetaCreatepatternbrushRecord::isPaletteRequired() const
{
    if(this->bitsPerPixel == 24)
    {
        return false;
    }
    else
    {
        return true;
    }
}
