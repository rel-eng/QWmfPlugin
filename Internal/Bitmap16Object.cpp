/* Bitmap16 object implementation.

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

#include "Bitmap16Object.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

Bitmap16Object::Bitmap16Object() :  type(0), width(0), height(0), widthBytes(0), planes(1), bitsPerPixel(24), imageBits(), imageBitsLength(0)
{
}

Bitmap16Object::Bitmap16Object(quint16 width, quint16 height, quint8 bitsPerPixel, QScopedArrayPointer<quint8> imageBits, size_t imageBitsLength) :  type(0), width(width), height(height), planes(1), bitsPerPixel(bitsPerPixel), imageBits(), imageBitsLength(imageBitsLength)
{
    quint16 wb = (this->width * static_cast<quint16>(bitsPerPixel) + 15)/16;
    this->widthBytes = wb * 2;
    if(imageBitsLength != (this->widthBytes * this->height))
    {
        throw std::runtime_error("Invalid imageBitsLength value");
    }
    if(imageBitsLength > 0)
    {
        QScopedArrayPointer<quint8>(new quint8[imageBitsLength]).swap(this->imageBits);
        memcpy(reinterpret_cast<void *>(this->imageBits.data()), reinterpret_cast<const void *>(imageBits.data()), imageBitsLength);
    }
}

Bitmap16Object::Bitmap16Object(QIODevice &device) : imageBits()
{
    this->type = readUnsignedWord(device);
    this->width = readUnsignedWord(device);
    this->height = readUnsignedWord(device);
    this->widthBytes = readUnsignedWord(device);
    this->planes = readUnsignedByte(device);
    if(this->planes != 1)
    {
        throw std::runtime_error("Invalid imageBitsLength value");
    }
    this->bitsPerPixel = readUnsignedByte(device);
    quint16 wb = (this->width * static_cast<quint16>(this->bitsPerPixel) + 15)/16;
    quint16 realWidthBytes = wb * 2;
    if(realWidthBytes != this->widthBytes)
    {
        throw std::runtime_error("Invalid widthBytes value");
    }
    this->imageBitsLength = this->widthBytes * this->height;
    QScopedArrayPointer<quint8>(new quint8[this->imageBitsLength]).swap(this->imageBits);
    fillBuffer(device, static_cast<qint64>(this->imageBitsLength), reinterpret_cast<void *>(this->imageBits.data()), static_cast<size_t>(this->imageBitsLength));
}

Bitmap16Object::Bitmap16Object(const Bitmap16Object &rhs) :  type(rhs.type), width(rhs.width), height(rhs.height), widthBytes(rhs.widthBytes), planes(rhs.planes), bitsPerPixel(rhs.bitsPerPixel), imageBits(), imageBitsLength(rhs.imageBitsLength)
{
    if(rhs.imageBitsLength > 0)
    {
        QScopedArrayPointer<quint8>(new quint8[rhs.imageBitsLength]).swap(this->imageBits);
        memcpy(static_cast<void *>(this->imageBits.data()), static_cast<const void *>(rhs.imageBits.data()), rhs.imageBitsLength);
    }
}

Bitmap16Object::~Bitmap16Object()
{
}

Bitmap16Object & Bitmap16Object::operator=(const Bitmap16Object &rhs)
{
    if (this != &rhs)
    {
        this->type = rhs.type;
        this->width = rhs.width;
        this->height = rhs.height;
        this->widthBytes = rhs.widthBytes;
        this->planes = rhs.planes;
        this->bitsPerPixel = rhs.bitsPerPixel;
        this->imageBitsLength = rhs.imageBitsLength;
        if(rhs.imageBitsLength > 0)
        {
            QScopedArrayPointer<quint8>(new quint8[rhs.imageBitsLength]).swap(this->imageBits);
            memcpy(static_cast<void *>(this->imageBits.data()), static_cast<const void *>(rhs.imageBits.data()), rhs.imageBitsLength);
        }
    }
    return *this;
}

quint16 Bitmap16Object::getWidth() const
{
    return this->width;
}

quint16 Bitmap16Object::getHeight() const
{
    return this->height;
}

quint8 Bitmap16Object::getBitsPerPixel() const
{
    return this->bitsPerPixel;
}

QImage Bitmap16Object::getImage()
{
    QImage image(this->width, this->height, QImage::Format_ARGB32);
    if(this->bitsPerPixel == 24)
    {
        for (size_t row = 0; row < static_cast<size_t>(this->height); row++)
        {
            for (size_t col = 0; col < static_cast<size_t>(this->width); col++)
            {
                quint8 blueIn = this->imageBits[row * this->widthBytes + col * 3];
                quint8 greenIn = this->imageBits[row * this->widthBytes + col * 3 + 1];
                quint8 redIn = this->imageBits[row * this->widthBytes + col * 3 + 2];
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

QImage Bitmap16Object::getImage(const PaletteObject &palette)
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
                if ((this->imageBits[row * this->widthBytes + col / 8] & masks[col % 8]) != 0)
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
                        colorIndex = this->imageBits[row * this->widthBytes + col / 2];
                        colorIndex = colorIndex >> 4;
                    }
                    else
                    {
                        colorIndex = this->imageBits[row * this->widthBytes + col / 2] & 15;
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
                        quint8 colorIndex = this->imageBits[row * this->widthBytes + col];
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
                            quint8 blueIn = this->imageBits[row * this->widthBytes + col * 3];
                            quint8 greenIn = this->imageBits[row * this->widthBytes + col * 3 + 1];
                            quint8 redIn = this->imageBits[row * this->widthBytes + col * 3 + 2];
                            image.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                        }
                    }
                }
            }
        }
    }
    return image;
}
