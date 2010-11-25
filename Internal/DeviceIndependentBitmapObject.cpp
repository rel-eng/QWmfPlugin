/* DeviceIndependentBitmap object implementation.

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

#include "DeviceIndependentBitmapObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

DeviceIndependentBitmapObject::DeviceIndependentBitmapObject() : headersLoaded(false), isInfoHeader(false), coreHeader(), infoHeader(), image(), imageBits(), imageBitsValid(false), imageBitsSize(0), colorUsage(DIB_RGB_COLORS), size(0)
{
}

DeviceIndependentBitmapObject::DeviceIndependentBitmapObject(QIODevice &device, qint64 maxSize) : headersLoaded(true), isInfoHeader(false), coreHeader(), infoHeader(), image(), imageBits(), imageBitsValid(false), imageBitsSize(0), colorUsage(DIB_RGB_COLORS), size(static_cast<quint32>(maxSize))
{
    this->loadWithRGBPalette(device, maxSize);
}

DeviceIndependentBitmapObject::DeviceIndependentBitmapObject(QIODevice &device, quint16 colorUsage, qint64 maxSize) : headersLoaded(true), isInfoHeader(false), coreHeader(), infoHeader(), image(), imageBits(), imageBitsValid(false), imageBitsSize(0), colorUsage(colorUsage), size(static_cast<quint32>(maxSize))
{
    switch(colorUsage)
    {
    case DIB_RGB_COLORS:
        this->loadWithRGBPalette(device, maxSize);
        break;
    case DIB_PAL_COLORS:
        {
            qint64 pos = device.pos();
            quint32 headerSize = readUnsignedDWord(device);
            seekDevice(device, pos);
            if(headerSize == 12)
            {
                this->coreHeader = BitmapCoreHeaderObject(device);
            }
            else
            {
                this->infoHeader = BitmapInfoHeaderObject(device);
                this->isInfoHeader = true;
            }
            if(maxSize < static_cast<qint64>(headerSize))
            {
                throw std::runtime_error("Bitmap is too small");
            }
            seekDevice(device, pos + static_cast<qint64>(headerSize));
            this->imageBitsSize = static_cast<size_t>(maxSize - static_cast<qint64>(headerSize));
            QScopedArrayPointer<quint8>(new quint8[this->imageBitsSize]).swap(this->imageBits);
            fillBuffer(device, static_cast<qint64>(this->imageBitsSize), reinterpret_cast<void *>(this->imageBits.data()), this->imageBitsSize);
            this->imageBitsValid = true;
        }
        break;
    case DIB_PAL_INDICES:
        {
            qint64 pos = device.pos();
            quint32 headerSize = readUnsignedDWord(device);
            seekDevice(device, pos);
            if(headerSize == 12)
            {
                this->coreHeader = BitmapCoreHeaderObject(device);
            }
            else
            {
                this->infoHeader = BitmapInfoHeaderObject(device);
                this->isInfoHeader = true;
            }
            if(maxSize < static_cast<qint64>(headerSize))
            {
                throw std::runtime_error("Bitmap is too small");
            }
            seekDevice(device, pos + static_cast<qint64>(headerSize));
            this->imageBitsSize = static_cast<size_t>(maxSize - static_cast<qint64>(headerSize));
            QScopedArrayPointer<quint8>(new quint8[this->imageBitsSize]).swap(this->imageBits);
            fillBuffer(device, static_cast<qint64>(this->imageBitsSize), reinterpret_cast<void *>(this->imageBits.data()), this->imageBitsSize);
            this->imageBitsValid = true;
        }
        break;
    default:
        throw std::runtime_error("Invalid color usage value");
    }
}

DeviceIndependentBitmapObject::DeviceIndependentBitmapObject(const QImage &image) : headersLoaded(false), isInfoHeader(false), coreHeader(), infoHeader(), image(image), imageBits(), imageBitsValid(false), imageBitsSize(0), colorUsage(DIB_RGB_COLORS), size(12 + image.bytesPerLine()*image.height())
{
}

DeviceIndependentBitmapObject::DeviceIndependentBitmapObject(const DeviceIndependentBitmapObject &rhs) : headersLoaded(rhs.headersLoaded), isInfoHeader(rhs.isInfoHeader), coreHeader(rhs.coreHeader), infoHeader(rhs.infoHeader), image(rhs.image), imageBits(), imageBitsValid(rhs.imageBitsValid), imageBitsSize(rhs.imageBitsSize), colorUsage(rhs.colorUsage), size(rhs.size)
{
    if(rhs.imageBitsValid && !rhs.imageBits.isNull() && (rhs.imageBitsSize != 0))
    {
        QScopedArrayPointer<quint8>(new quint8[rhs.imageBitsSize]).swap(this->imageBits);
        memcpy(reinterpret_cast<void *>(this->imageBits.data()), reinterpret_cast<void *>(rhs.imageBits.data()), rhs.imageBitsSize);
    }
}

DeviceIndependentBitmapObject::~DeviceIndependentBitmapObject()
{
}

DeviceIndependentBitmapObject & DeviceIndependentBitmapObject::operator=(const DeviceIndependentBitmapObject &rhs)
{
    if (this != &rhs)
    {
        this->headersLoaded = rhs.headersLoaded;
        this->isInfoHeader = rhs.isInfoHeader;
        this->coreHeader = rhs.coreHeader;
        this->infoHeader = rhs.infoHeader;
        this->image = rhs.image;
        if(rhs.imageBitsValid && !rhs.imageBits.isNull() && (rhs.imageBitsSize != 0))
        {
            QScopedArrayPointer<quint8>(new quint8[rhs.imageBitsSize]).swap(this->imageBits);
            memcpy(reinterpret_cast<void *>(this->imageBits.data()), reinterpret_cast<void *>(rhs.imageBits.data()), rhs.imageBitsSize);
        }
        this->imageBitsValid = rhs.imageBitsValid;
        this->imageBitsSize = rhs.imageBitsSize;
        this->colorUsage = rhs.colorUsage;
        this->size = rhs.size;
    }
    return *this;
}

QImage DeviceIndependentBitmapObject::getImage() const
{
    return this->image;
}

QImage DeviceIndependentBitmapObject::getImage(const PaletteObject &palette) const
{
    if(!this->imageBitsValid)
    {
        return this->image;
    }
    if(!this->headersLoaded)
    {
        return this->image;
    }
    switch(this->colorUsage)
    {
    case DIB_RGB_COLORS:
        return this->image;
        break;
    case DIB_PAL_COLORS:
        return this->loadWithPalColors(palette);
        break;
    case DIB_PAL_INDICES:
        return this->loadWithPalIndices(palette);
        break;
    default:
        throw std::runtime_error("Invalid color usage value");
    }
}

void DeviceIndependentBitmapObject::readUncompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, bool paletteQuad)
{
    quint32 wb = (width * static_cast<quint32>(bitCount) + 31) & 0xFFFFFFE0;
    size_t widthBytes = static_cast<size_t>(wb/8);
    size_t dataSize = widthBytes * static_cast<size_t>(height);
    QScopedArrayPointer<quint8> imageData(new quint8[dataSize]);
    switch(bitCount)
    {
    //1 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_1:
        {
            QScopedArrayPointer<QRgb> palette(new QRgb[2]);
            memset(reinterpret_cast<void *>(palette.data()), 0, sizeof(QRgb) * 2);
            if(paletteSize == 0)
            {
                paletteSize = 2;
            }
            if(paletteQuad)
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRDword(device);
                }
            }
            else
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRBytes(device);
                }
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            this->image.setPixel(col, height - 1 - row, palette[1]);
                        }
                        else
                        {
                            this->image.setPixel(col, height - 1 - row, palette[0]);
                        }
                    }
                }
            }
            else
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            this->image.setPixel(col, row, palette[1]);
                        }
                        else
                        {
                            this->image.setPixel(col, row, palette[0]);
                        }
                    }
                }
            }
        }
        break;
    //4 бита на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_2:
        {
            QScopedArrayPointer<QRgb> palette(new QRgb[16]);
            memset(reinterpret_cast<void *>(palette.data()), 0, sizeof(QRgb) * 16);
            if(paletteSize == 0)
            {
                paletteSize = 16;
            }
            if(paletteQuad)
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRDword(device);
                }
            }
            else
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRBytes(device);
                }
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        image.setPixel(col, height - 1 - row, palette[colorIndex]);
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        image.setPixel(col, row, palette[colorIndex]);
                    }
                }
            }
        }
        break;
    //8 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_3:
        {
            QScopedArrayPointer<QRgb> palette(new QRgb[256]);
            memset(reinterpret_cast<void *>(palette.data()), 0, sizeof(QRgb) * 256);
            if(paletteSize == 0)
            {
                paletteSize = 256;
            }
            if(paletteQuad)
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRDword(device);
                }
            }
            else
            {
                for(int i = 0; i < paletteSize; i++)
                {
                    palette[i] = readBGRBytes(device);
                }
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        image.setPixel(col, height - 1 - row, palette[colorIndex]);
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        image.setPixel(col, row, palette[colorIndex]);
                    }
                }
            }
        }
        break;
    //16 бит на пиксел, RGB, без сжатия, 5 младших бит - голубой, следующие 5 бит - зеленый, следующие 5 бит - красный, старший бит не используется
    case BI_BITCOUNT_4:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        image.setPixel(col, height - 1 - row, qRgb(red, green, blue));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        image.setPixel(col, row, qRgb(red, green, blue));
                    }
                }
            }
        }
        break;
    //24 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный
    case BI_BITCOUNT_5:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        image.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        image.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    //32 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный, старший байт не используется
    case BI_BITCOUNT_6:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        image.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        image.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    default:
        throw std::runtime_error("Invalid bitmap bit count");
    }
}

void DeviceIndependentBitmapObject::readRLE4CompressedBitmap(QIODevice &device, quint32 width, quint32 height, qint64 maxSize, quint32 paletteSize, bool paletteQuad, quint32 headerSize)
{
    this->image.fill(0);
    int row = 0;
    int col = 0;
    QScopedArrayPointer<QRgb> palette(new QRgb[16]);
    memset(reinterpret_cast<void *>(palette.data()), 0, sizeof(QRgb) * 16);
    if(paletteSize == 0)
    {
        paletteSize = 16;
    }
    qint64 paletteBytes = 0;
    if(paletteQuad)
    {
        for(int i = 0; i < paletteSize; i++)
        {
            palette[i] = readBGRDword(device);
        }
        paletteBytes = static_cast<qint64>(paletteSize) * 4;
    }
    else
    {
        for(int i = 0; i < paletteSize; i++)
        {
            palette[i] = readBGRBytes(device);
        }
        paletteBytes = static_cast<qint64>(paletteSize) * 3;
    }
    qint64 leftToRead = maxSize - paletteBytes - static_cast<qint64>(headerSize);
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            quint8 firstColor = ((secondByte & 0xF0) >> 4) & 0x0F;
            quint8 secondColor = secondByte & 0x0F;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                this->image.setPixel(col, height - 1 - row, palette[firstColor]);
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
                quint8 tempColor = firstColor;
                firstColor = secondColor;
                secondColor = tempColor;
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0, 0, 0};
                    size_t currentIndex = 4;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 3)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = ((lowByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[1] = lowByte & 0x0F;
                                    colorIndexes[2] = ((highByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[3] = highByte & 0x0F;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        this->image.setPixel(col, height - 1 - row, palette[colorIndexes[currentIndex]]);
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
}

void DeviceIndependentBitmapObject::readRLE8CompressedBitmap(QIODevice &device, quint32 width, quint32 height, qint64 maxSize, quint32 paletteSize, bool paletteQuad, quint32 headerSize)
{
    this->image.fill(0);
    int row = 0;
    int col = 0;
    QScopedArrayPointer<QRgb> palette(new QRgb[256]);
    memset(reinterpret_cast<void *>(palette.data()), 0, sizeof(QRgb) * 256);
    if(paletteSize == 0)
    {
        paletteSize = 256;
    }
    qint64 paletteBytes = 0;
    if(paletteQuad)
    {
        for(int i = 0; i < paletteSize; i++)
        {
            palette[i] = readBGRDword(device);
        }
        paletteBytes = static_cast<qint64>(paletteSize) * 4;
    }
    else
    {
        for(int i = 0; i < paletteSize; i++)
        {
            palette[i] = readBGRBytes(device);
        }
        paletteBytes = static_cast<qint64>(paletteSize) * 3;
    }
    qint64 leftToRead = maxSize - paletteBytes - static_cast<qint64>(headerSize);
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                this->image.setPixel(col, height - 1 - row, palette[secondByte]);
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0};
                    size_t currentIndex = 2;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 1)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = lowByte;
                                    colorIndexes[1] = highByte;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        this->image.setPixel(col, height - 1 - row, palette[colorIndexes[currentIndex]]);
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
}

void DeviceIndependentBitmapObject::readBitfieldsCompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount)
{
    quint32 wb = (width * static_cast<quint32>(bitCount) + 31) & 0xFFFFFFE0;
    size_t widthBytes = static_cast<size_t>(wb/8);
    size_t dataSize = widthBytes * static_cast<size_t>(height);
    QScopedArrayPointer<quint8> imageData(new quint8[dataSize]);
    quint32 redMask = readUnsignedDWord(device);
    quint32 redShiftCount = this->calcShiftCount(redMask);
    quint32 redScaleCoef = 256 / ((redMask >> redShiftCount) + 1);
    quint32 greenMask = readUnsignedDWord(device);
    quint32 greenShiftCount = this->calcShiftCount(greenMask);
    quint32 greenScaleCoef = 256 / ((greenMask >> greenShiftCount) + 1);
    quint32 blueMask = readUnsignedDWord(device);
    quint32 blueShiftCount = this->calcShiftCount(blueMask);
    quint32 blueScaleCoef = 256 / ((blueMask >> blueShiftCount) + 1);
    fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
    if(bitCount == 16)
    {
        for (size_t row = 0; row < static_cast<size_t>(height); row++)
        {
            for (size_t col = 0; col < static_cast<size_t>(width); col++)
            {
                quint8 colorLow = imageData[row * widthBytes + col*2];
                quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                quint32 colorValue = static_cast<quint32>(colorLow) + static_cast<quint32>(colorHigh) * 0x100;
                quint32 red = ((colorValue & redMask) >> redShiftCount) * redScaleCoef;
                quint32 green = ((colorValue & greenMask) >> greenShiftCount) * greenScaleCoef;
                quint32 blue = ((colorValue & blueMask) >> blueShiftCount) * blueScaleCoef;
                image.setPixel(col, height - 1 - row, qRgb(red, green, blue));
            }
        }
    }
    else
    {
        if(bitCount == 32)
        {
            for (size_t row = 0; row < static_cast<size_t>(height); row++)
            {
                for (size_t col = 0; col < static_cast<size_t>(width); col++)
                {
                    quint8 color0 = imageData[row * widthBytes + col*4];
                    quint8 color1 = imageData[row * widthBytes + col*4 + 1];
                    quint8 color2 = imageData[row * widthBytes + col*4 + 2];
                    quint8 color3 = imageData[row * widthBytes + col*4 + 3];
                    quint32 colorValue = static_cast<quint32>(color0) + static_cast<quint32>(color1) * 0x100 + static_cast<quint32>(color2) * 0x10000 + static_cast<quint32>(color3) * 0x1000000;
                    quint32 red = ((colorValue & redMask) >> redShiftCount) * redScaleCoef;
                    quint32 green = ((colorValue & greenMask) >> greenShiftCount) * greenScaleCoef;
                    quint32 blue = ((colorValue & blueMask) >> blueShiftCount) * blueScaleCoef;
                    image.setPixel(col, height - 1 - row, qRgb(red, green, blue));
                }
            }
        }
        else
        {
            throw std::runtime_error("Invalid bit count");
        }
    }
}

quint32 DeviceIndependentBitmapObject::calcShiftCount(quint32 mask) const
{
    quint32 shiftCount = 0;
    while (mask && !(mask & 0x00000001))
    {
            shiftCount++;
            mask = mask >> 1;
    }
    return shiftCount;
}

void DeviceIndependentBitmapObject::loadWithRGBPalette(QIODevice &device, qint64 maxSize)
{
    qint64 pos = device.pos();
    quint32 headerSize = readUnsignedDWord(device);
    seekDevice(device, pos);
    qint32 width = 0;
    qint32 height = 0;
    quint16 bitCount = 0;
    quint32 paletteSize = 0;
    bool paletteQuad = true;
    if(headerSize == 12)
    {
        this->coreHeader = BitmapCoreHeaderObject(device);
        width = this->coreHeader.getWidth();
        height = this->coreHeader.getHeight();
        bitCount = this->coreHeader.getBitCount();
        paletteQuad = false;
    }
    else
    {
        this->infoHeader = BitmapInfoHeaderObject(device);
        this->isInfoHeader = true;
        width = this->infoHeader.getWidth();
        height = this->infoHeader.getHeight();
        bitCount = this->infoHeader.getBitCount();
        paletteSize = this->infoHeader.getColorsUsed();
    }
    bool bottomUp = true;
    if(height < 0)
    {
        bottomUp = false;
    }
    if(maxSize < static_cast<qint64>(headerSize))
    {
        throw std::runtime_error("Bitmap is too small");
    }
    seekDevice(device, pos + static_cast<qint64>(headerSize));
    if(this->isInfoHeader)
    {
        //Новый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            switch(this->infoHeader.getCompression())
            {
            case BI_RGB:
                //Несжатый битмап
                this->image = QImage(width, qAbs(height), QImage::Format_ARGB32);
                this->image.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                this->image.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                this->readUncompressedBitmap(device, width, qAbs(height), bitCount, bottomUp, paletteSize, paletteQuad);
                break;
            case BI_RLE8:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 8)
                {
                    this->image = QImage(width, qAbs(height), QImage::Format_ARGB32);
                    this->image.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    this->image.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                    this->readRLE8CompressedBitmap(device, width, height, maxSize, paletteSize, paletteQuad, headerSize);
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_RLE4:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 4)
                {
                    this->image = QImage(width, qAbs(height), QImage::Format_ARGB32);
                    this->image.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    this->image.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                    this->readRLE4CompressedBitmap(device, width, height, maxSize, paletteSize, paletteQuad, headerSize);
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_BITFIELDS:
                if((bitCount == 16) || (bitCount == 32))
                {
                    this->image = QImage(width, qAbs(height), QImage::Format_ARGB32);
                    this->image.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    this->image.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                    this->readBitfieldsCompressedBitmap(device, width, height, bitCount);
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_JPEG:
                if(bottomUp)
                {
                    QByteArray imageData = device.read(static_cast<qint64>(this->infoHeader.getImageSize()));
                    if(static_cast<quint32>(imageData.size()) != this->infoHeader.getImageSize())
                    {
                        throw std::runtime_error("Unable to read compressed bitmap");
                    }
                    this->image = QImage::fromData(imageData, "JPEG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            case BI_PNG:
                if(bottomUp)
                {
                    QByteArray imageData = device.read(static_cast<qint64>(this->infoHeader.getImageSize()));
                    if(static_cast<quint32>(imageData.size()) != this->infoHeader.getImageSize())
                    {
                        throw std::runtime_error("Unable to read compressed bitmap");
                    }
                    this->image = QImage::fromData(imageData, "PNG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            default:
                throw std::runtime_error("Unsupported bitmap compression type");
            }
        }
        else
        {
            //Сжатый битмап, JPEG или PNG
            if(!bottomUp)
            {
                throw std::runtime_error("Compression of top-down bitmaps is not supported");
            }
            QByteArray imageData = device.read(static_cast<qint64>(this->infoHeader.getImageSize()));
            if(static_cast<quint32>(imageData.size()) != this->infoHeader.getImageSize())
            {
                throw std::runtime_error("Unable to read compressed bitmap");
            }
            switch(this->infoHeader.getCompression())
            {
            case BI_JPEG:
                this->image = QImage::fromData(imageData, "JPEG");
                break;
            case BI_PNG:
                this->image = QImage::fromData(imageData, "PNG");
                break;
            default:
                throw std::runtime_error("Invalid bitmap compression type");
            }
        }
    }
    else
    {
        //Старый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            //Несжатый битмап
            this->image = QImage(width, qAbs(height), QImage::Format_ARGB32);
            this->readUncompressedBitmap(device, width, qAbs(height), bitCount, bottomUp, paletteSize, paletteQuad);
        }
        else
        {
            //Сжатый битмап
            QByteArray imageData = device.read(maxSize - Q_INT64_C(12));
            if(static_cast<quint64>(imageData.size()) != (maxSize - Q_INT64_C(12)))
            {
                throw std::runtime_error("Unable to read compressed bitmap");
            }
            this->image = QImage::fromData(imageData);
        }
    }
}

QImage DeviceIndependentBitmapObject::loadWithPalColors(const PaletteObject &palette) const
{
    int width = 0;
    int height = 0;
    int bitCount = 0;
    quint32 paletteSize = 0;
    if(this->isInfoHeader)
    {
        width = this->infoHeader.getWidth();
        height = this->infoHeader.getHeight();
        bitCount = this->infoHeader.getBitCount();
        paletteSize = this->infoHeader.getColorsUsed();
    }
    else
    {
        width = this->coreHeader.getWidth();
        height = this->coreHeader.getHeight();
        bitCount = this->coreHeader.getBitCount();
    }
    bool bottomUp = true;
    if(height < 0)
    {
        bottomUp = false;
    }
    QImage result;
    if(this->isInfoHeader)
    {
        //Новый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            switch(this->infoHeader.getCompression())
            {
            case BI_RGB:
                {
                    //Несжатый битмап
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readUncompressedBitmapPalColors(imageData, width, height, bitCount, bottomUp, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                break;
            case BI_RLE8:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 8)
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readRLE8CompressedBitmapPalColors(imageData, width, height, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_RLE4:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 4)
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readRLE4CompressedBitmapPalColors(imageData, width, height, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_BITFIELDS:
                if((bitCount == 16) || (bitCount == 32))
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->loadBitfieldsCompressedBitmap(imageData, width, height, bitCount);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_JPEG:
                if(bottomUp)
                {
                    QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    result = QImage::fromData(imageData, "JPEG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            case BI_PNG:
                if(bottomUp)
                {
                    QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    result = QImage::fromData(imageData, "PNG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            default:
                throw std::runtime_error("Unsupported bitmap compression type");
            }
        }
        else
        {
            //Сжатый битмап, JPEG или PNG
            if(!bottomUp)
            {
                throw std::runtime_error("Compression of top-down bitmaps is not supported");
            }
            QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            switch(this->infoHeader.getCompression())
            {
            case BI_JPEG:
                {
                    result = QImage::fromData(imageData, "JPEG");
                }
                break;
            case BI_PNG:
                {
                    result = QImage::fromData(imageData, "PNG");
                }
                break;
            default:
                throw std::runtime_error("Invalid bitmap compression type");
            }
        }
    }
    else
    {
        //Старый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            //Несжатый битмап
            QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            QBuffer imageData(&imageDataArray);
            imageData.open(QIODevice::ReadOnly);
            result = this->readUncompressedBitmapPalColors(imageData, width, height, bitCount, bottomUp, paletteSize, palette);
            imageData.close();

        }
        else
        {
            //Сжатый битмап
            QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            result = QImage::fromData(imageData);
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readUncompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, const PaletteObject &palette) const
{
    QImage result(width, height, QImage::Format_ARGB32);
    quint32 wb = (width * static_cast<quint32>(bitCount) + 31) & 0xFFFFFFE0;
    size_t widthBytes = static_cast<size_t>(wb/8);
    size_t dataSize = widthBytes * static_cast<size_t>(height);
    QScopedArrayPointer<quint8> imageData(new quint8[dataSize]);
    switch(bitCount)
    {
    //1 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_1:
        {
            QScopedArrayPointer<QRgb> paletteArray(new QRgb[2]);
            memset(reinterpret_cast<void *>(paletteArray.data()), 0, sizeof(QRgb) * 2);
            if(paletteSize == 0)
            {
                paletteSize = 2;
            }
            for(int i = 0; i < paletteSize; i++)
            {
                quint16 palIndex = readUnsignedWord(device);
                if(palIndex >= palette.getPaletteEntriesCount())
                {
                    throw std::runtime_error("Invalid color index");
                }
                paletteArray[i] = palette.getPaletteEntryColor(palIndex);
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            result.setPixel(col, height - 1 - row, paletteArray[1]);
                        }
                        else
                        {
                            result.setPixel(col, height - 1 - row, paletteArray[0]);
                        }
                    }
                }
            }
            else
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            result.setPixel(col, row, paletteArray[1]);
                        }
                        else
                        {
                            result.setPixel(col, row, paletteArray[0]);
                        }
                    }
                }
            }
        }
        break;
    //4 бита на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_2:
        {
            QScopedArrayPointer<QRgb> paletteArray(new QRgb[16]);
            memset(reinterpret_cast<void *>(paletteArray.data()), 0, sizeof(QRgb) * 16);
            if(paletteSize == 0)
            {
                paletteSize = 16;
            }
            for(int i = 0; i < paletteSize; i++)
            {
                quint16 palIndex = readUnsignedWord(device);
                if(palIndex >= palette.getPaletteEntriesCount())
                {
                    throw std::runtime_error("Invalid color index");
                }
                paletteArray[i] = palette.getPaletteEntryColor(palIndex);
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        result.setPixel(col, height - 1 - row, paletteArray[colorIndex]);
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        result.setPixel(col, row, paletteArray[colorIndex]);
                    }
                }
            }
        }
        break;
    //8 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_3:
        {
            QScopedArrayPointer<QRgb> paletteArray(new QRgb[256]);
            memset(reinterpret_cast<void *>(paletteArray.data()), 0, sizeof(QRgb) * 256);
            if(paletteSize == 0)
            {
                paletteSize = 256;
            }
            for(int i = 0; i < paletteSize; i++)
            {
                quint16 palIndex = readUnsignedWord(device);
                if(palIndex >= palette.getPaletteEntriesCount())
                {
                    throw std::runtime_error("Invalid color index");
                }
                paletteArray[i] = palette.getPaletteEntryColor(palIndex);
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        result.setPixel(col, height - 1 - row, paletteArray[colorIndex]);
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        result.setPixel(col, row, paletteArray[colorIndex]);
                    }
                }
            }
        }
        break;
    //16 бит на пиксел, RGB, без сжатия, 5 младших бит - голубой, следующие 5 бит - зеленый, следующие 5 бит - красный, старший бит не используется
    case BI_BITCOUNT_4:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        result.setPixel(col, height - 1 - row, qRgb(red, green, blue));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        result.setPixel(col, row, qRgb(red, green, blue));
                    }
                }
            }
        }
        break;
    //24 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный
    case BI_BITCOUNT_5:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        result.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        result.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    //32 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный, старший байт не используется
    case BI_BITCOUNT_6:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        result.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        result.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    default:
        throw std::runtime_error("Invalid bitmap bit count");
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readRLE4CompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const
{
    QImage result(width, height, QImage::Format_ARGB32);
    result.fill(0);
    int row = 0;
    int col = 0;
    QScopedArrayPointer<QRgb> paletteArray(new QRgb[16]);
    memset(reinterpret_cast<void *>(paletteArray.data()), 0, sizeof(QRgb) * 16);
    if(paletteSize == 0)
    {
        paletteSize = 16;
    }
    qint64 paletteBytes = 0;
    for(int i = 0; i < paletteSize; i++)
    {
        quint16 palIndex = readUnsignedWord(device);
        if(palIndex >= palette.getPaletteEntriesCount())
        {
            throw std::runtime_error("Invalid color index");
        }
        paletteArray[i] = palette.getPaletteEntryColor(palIndex);
    }
    paletteBytes = static_cast<qint64>(paletteSize) * 2;
    qint64 leftToRead = static_cast<qint64>(this->imageBitsSize) - paletteBytes;
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            quint8 firstColor = ((secondByte & 0xF0) >> 4) & 0x0F;
            quint8 secondColor = secondByte & 0x0F;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                result.setPixel(col, height - 1 - row, paletteArray[firstColor]);
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
                quint8 tempColor = firstColor;
                firstColor = secondColor;
                secondColor = tempColor;
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0, 0, 0};
                    size_t currentIndex = 4;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 3)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = ((lowByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[1] = lowByte & 0x0F;
                                    colorIndexes[2] = ((highByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[3] = highByte & 0x0F;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        result.setPixel(col, height - 1 - row, paletteArray[colorIndexes[currentIndex]]);
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readRLE8CompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const
{
    QImage result(width, height, QImage::Format_ARGB32);
    result.fill(0);
    int row = 0;
    int col = 0;
    QScopedArrayPointer<QRgb> paletteArray(new QRgb[256]);
    memset(reinterpret_cast<void *>(paletteArray.data()), 0, sizeof(QRgb) * 256);
    if(paletteSize == 0)
    {
        paletteSize = 256;
    }
    qint64 paletteBytes = 0;
    for(int i = 0; i < paletteSize; i++)
    {
        quint16 palIndex = readUnsignedWord(device);
        if(palIndex >= palette.getPaletteEntriesCount())
        {
            throw std::runtime_error("Invalid color index");
        }
        paletteArray[i] = palette.getPaletteEntryColor(palIndex);
    }
    paletteBytes = static_cast<qint64>(paletteSize) * 2;
    qint64 leftToRead = static_cast<qint64>(this->imageBitsSize) - paletteBytes;
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                result.setPixel(col, height - 1 - row, paletteArray[secondByte]);
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0};
                    size_t currentIndex = 2;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 1)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = lowByte;
                                    colorIndexes[1] = highByte;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        result.setPixel(col, height - 1 - row, paletteArray[colorIndexes[currentIndex]]);
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::loadBitfieldsCompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount) const
{
    QImage result(width, height, QImage::Format_ARGB32);
    quint32 wb = (width * static_cast<quint32>(bitCount) + 31) & 0xFFFFFFE0;
    size_t widthBytes = static_cast<size_t>(wb/8);
    size_t dataSize = widthBytes * static_cast<size_t>(height);
    QScopedArrayPointer<quint8> imageData(new quint8[dataSize]);
    quint32 redMask = readUnsignedDWord(device);
    quint32 redShiftCount = this->calcShiftCount(redMask);
    quint32 redScaleCoef = 256 / ((redMask >> redShiftCount) + 1);
    quint32 greenMask = readUnsignedDWord(device);
    quint32 greenShiftCount = this->calcShiftCount(greenMask);
    quint32 greenScaleCoef = 256 / ((greenMask >> greenShiftCount) + 1);
    quint32 blueMask = readUnsignedDWord(device);
    quint32 blueShiftCount = this->calcShiftCount(blueMask);
    quint32 blueScaleCoef = 256 / ((blueMask >> blueShiftCount) + 1);
    fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
    if(bitCount == 16)
    {
        for (size_t row = 0; row < static_cast<size_t>(height); row++)
        {
            for (size_t col = 0; col < static_cast<size_t>(width); col++)
            {
                quint8 colorLow = imageData[row * widthBytes + col*2];
                quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                quint32 colorValue = static_cast<quint32>(colorLow) + static_cast<quint32>(colorHigh) * 0x100;
                quint32 red = ((colorValue & redMask) >> redShiftCount) * redScaleCoef;
                quint32 green = ((colorValue & greenMask) >> greenShiftCount) * greenScaleCoef;
                quint32 blue = ((colorValue & blueMask) >> blueShiftCount) * blueScaleCoef;
                result.setPixel(col, height - 1 - row, qRgb(red, green, blue));
            }
        }
    }
    else
    {
        if(bitCount == 32)
        {
            for (size_t row = 0; row < static_cast<size_t>(height); row++)
            {
                for (size_t col = 0; col < static_cast<size_t>(width); col++)
                {
                    quint8 color0 = imageData[row * widthBytes + col*4];
                    quint8 color1 = imageData[row * widthBytes + col*4 + 1];
                    quint8 color2 = imageData[row * widthBytes + col*4 + 2];
                    quint8 color3 = imageData[row * widthBytes + col*4 + 3];
                    quint32 colorValue = static_cast<quint32>(color0) + static_cast<quint32>(color1) * 0x100 + static_cast<quint32>(color2) * 0x10000 + static_cast<quint32>(color3) * 0x1000000;
                    quint32 red = ((colorValue & redMask) >> redShiftCount) * redScaleCoef;
                    quint32 green = ((colorValue & greenMask) >> greenShiftCount) * greenScaleCoef;
                    quint32 blue = ((colorValue & blueMask) >> blueShiftCount) * blueScaleCoef;
                    result.setPixel(col, height - 1 - row, qRgb(red, green, blue));
                }
            }
        }
        else
        {
            throw std::runtime_error("Invalid bit count");
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::loadWithPalIndices(const PaletteObject &palette) const
{
    int width = 0;
    int height = 0;
    int bitCount = 0;
    quint32 paletteSize = 0;
    if(this->isInfoHeader)
    {
        width = this->infoHeader.getWidth();
        height = this->infoHeader.getHeight();
        bitCount = this->infoHeader.getBitCount();
        paletteSize = this->infoHeader.getColorsUsed();
    }
    else
    {
        width = this->coreHeader.getWidth();
        height = this->coreHeader.getHeight();
        bitCount = this->coreHeader.getBitCount();
    }
    bool bottomUp = true;
    if(height < 0)
    {
        bottomUp = false;
    }
    QImage result;
    if(this->isInfoHeader)
    {
        //Новый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            switch(this->infoHeader.getCompression())
            {
            case BI_RGB:
                {
                    //Несжатый битмап
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readUncompressedBitmapPalIndices(imageData, width, height, bitCount, bottomUp, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                break;
            case BI_RLE8:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 8)
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readRLE8CompressedBitmapPalIndices(imageData, width, height, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_RLE4:
                if(!bottomUp)
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                if(bitCount == 4)
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->readRLE4CompressedBitmapPalIndices(imageData, width, height, paletteSize, palette);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_BITFIELDS:
                if((bitCount == 16) || (bitCount == 32))
                {
                    QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    QBuffer imageData(&imageDataArray);
                    imageData.open(QIODevice::ReadOnly);
                    result = this->loadBitfieldsCompressedBitmap(imageData, width, height, bitCount);
                    imageData.close();
                    result.setDotsPerMeterX(this->infoHeader.getXPelsPerMeter());
                    result.setDotsPerMeterY(this->infoHeader.getYPelsPerMeter());
                }
                else
                {
                    throw std::runtime_error("Invalid bitmap bit count");
                }
                break;
            case BI_JPEG:
                if(bottomUp)
                {
                    QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    result = QImage::fromData(imageData, "JPEG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            case BI_PNG:
                if(bottomUp)
                {
                    QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
                    result = QImage::fromData(imageData, "PNG");
                }
                else
                {
                    throw std::runtime_error("Compression of top-down bitmaps is not supported");
                }
                break;
            default:
                throw std::runtime_error("Unsupported bitmap compression type");
            }
        }
        else
        {
            //Сжатый битмап, JPEG или PNG
            if(!bottomUp)
            {
                throw std::runtime_error("Compression of top-down bitmaps is not supported");
            }
            QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            switch(this->infoHeader.getCompression())
            {
            case BI_JPEG:
                {
                    result = QImage::fromData(imageData, "JPEG");
                }
                break;
            case BI_PNG:
                {
                    result = QImage::fromData(imageData, "PNG");
                }
                break;
            default:
                throw std::runtime_error("Invalid bitmap compression type");
            }
        }
    }
    else
    {
        //Старый заголовок
        if(bitCount != BI_BITCOUNT_0)
        {
            //Несжатый битмап
            QByteArray imageDataArray(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            QBuffer imageData(&imageDataArray);
            imageData.open(QIODevice::ReadOnly);
            result = this->readUncompressedBitmapPalIndices(imageData, width, height, bitCount, bottomUp, paletteSize, palette);
            imageData.close();

        }
        else
        {
            //Сжатый битмап
            QByteArray imageData(reinterpret_cast<const char *>(this->imageBits.data()), static_cast<int>(this->imageBitsSize));
            result = QImage::fromData(imageData);
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readUncompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, const PaletteObject &palette) const
{
    QImage result(width, height, QImage::Format_ARGB32);
    quint32 wb = (width * static_cast<quint32>(bitCount) + 31) & 0xFFFFFFE0;
    size_t widthBytes = static_cast<size_t>(wb/8);
    size_t dataSize = widthBytes * static_cast<size_t>(height);
    QScopedArrayPointer<quint8> imageData(new quint8[dataSize]);
    switch(bitCount)
    {
    //1 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_1:
        {
            if(palette.getPaletteEntriesCount() < 2)
            {
                throw std::runtime_error("Palette is too small");
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(1));
                        }
                        else
                        {
                            result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(0));
                        }
                    }
                }
            }
            else
            {
                quint8 masks[] = {128, 64, 32, 16, 8, 4, 2, 1};
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        if ((imageData[row * widthBytes + col / 8] & masks[col % 8]) != 0)
                        {
                            result.setPixel(col, row, palette.getPaletteEntryColor(1));
                        }
                        else
                        {
                            result.setPixel(col, row, palette.getPaletteEntryColor(0));
                        }
                    }
                }
            }
        }
        break;
    //4 бита на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_2:
        {
            if(palette.getPaletteEntriesCount() < 16)
            {
                throw std::runtime_error("Palette is too small");
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(colorIndex));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = 0;
                        if ((col & 1) == 0)
                        {
                            colorIndex = imageData[row * widthBytes + col / 2];
                            colorIndex = colorIndex >> 4;
                        }
                        else
                        {
                            colorIndex = imageData[row * widthBytes + col / 2] & 15;
                        }
                        result.setPixel(col, row, palette.getPaletteEntryColor(colorIndex));
                    }
                }
            }
        }
        break;
    //8 бит на пиксел, палитра, RGB, без сжатия
    case BI_BITCOUNT_3:
        {
            if(palette.getPaletteEntriesCount() < 256)
            {
                throw std::runtime_error("Palette is too small");
            }
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(colorIndex));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorIndex = imageData[row * widthBytes + col];
                        result.setPixel(col, row, palette.getPaletteEntryColor(colorIndex));
                    }
                }
            }
        }
        break;
    //16 бит на пиксел, RGB, без сжатия, 5 младших бит - голубой, следующие 5 бит - зеленый, следующие 5 бит - красный, старший бит не используется
    case BI_BITCOUNT_4:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        result.setPixel(col, height - 1 - row, qRgb(red, green, blue));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 colorLow = imageData[row * widthBytes + col*2];
                        quint8 colorHigh = imageData[row * widthBytes + col*2 + 1];
                        quint8 blue = colorLow & 0x1F;
                        quint8 green = ((colorLow & 0xE0 >> 5) & 0x07) + (colorHigh & 0x03) * 8;
                        quint8 red = ((colorHigh & 0x7C) >> 2) & 0x1F;
                        result.setPixel(col, row, qRgb(red, green, blue));
                    }
                }
            }
        }
        break;
    //24 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный
    case BI_BITCOUNT_5:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        result.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 3];
                        quint8 greenIn = imageData[row * widthBytes + col * 3 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 3 + 2];
                        result.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    //32 бита на пиксел, RGB, без сжатия, младший байт - голубой, следующий байт - зеленый, следующий байт - красный, старший байт не используется
    case BI_BITCOUNT_6:
        {
            fillBuffer(device, static_cast<qint64>(dataSize), reinterpret_cast<void *>(imageData.data()), dataSize);
            if(bottomUp)
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        result.setPixel(col, height - 1 - row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
            else
            {
                for (size_t row = 0; row < static_cast<size_t>(height); row++)
                {
                    for (size_t col = 0; col < static_cast<size_t>(width); col++)
                    {
                        quint8 blueIn = imageData[row * widthBytes + col * 4];
                        quint8 greenIn = imageData[row * widthBytes + col * 4 + 1];
                        quint8 redIn = imageData[row * widthBytes + col * 4 + 2];
                        result.setPixel(col, row, qRgb(redIn, greenIn, blueIn));
                    }
                }
            }
        }
        break;
    default:
        throw std::runtime_error("Invalid bitmap bit count");
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readRLE4CompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const
{
    if(palette.getPaletteEntriesCount() < 16)
    {
        throw std::runtime_error("Palette is too small");
    }
    QImage result(width, height, QImage::Format_ARGB32);
    result.fill(0);
    int row = 0;
    int col = 0;
    qint64 leftToRead = static_cast<qint64>(this->imageBitsSize);
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            quint8 firstColor = ((secondByte & 0xF0) >> 4) & 0x0F;
            quint8 secondColor = secondByte & 0x0F;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(firstColor));
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
                quint8 tempColor = firstColor;
                firstColor = secondColor;
                secondColor = tempColor;
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0, 0, 0};
                    size_t currentIndex = 4;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 3)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = ((lowByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[1] = lowByte & 0x0F;
                                    colorIndexes[2] = ((highByte & 0xF0) >> 4) & 0x0F;
                                    colorIndexes[3] = highByte & 0x0F;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(colorIndexes[currentIndex]));
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
    return result;
}

QImage DeviceIndependentBitmapObject::readRLE8CompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const
{
    if(palette.getPaletteEntriesCount() < 256)
    {
        throw std::runtime_error("Palette is too small");
    }
    QImage result(width, height, QImage::Format_ARGB32);
    result.fill(0);
    int row = 0;
    int col = 0;
    qint64 leftToRead = static_cast<qint64>(this->imageBitsSize);
    while((leftToRead > Q_INT64_C(0)) && (row < height))
    {
        quint8 firstByte = readUnsignedByte(device);
        leftToRead--;
        if(firstByte > 0)
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            for(quint8 i = 0; i < firstByte; i++)
            {
                if(row >= height)
                {
                    break;
                }
                result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(secondByte));
                col++;
                if(col >= width)
                {
                    col = 0;
                    row++;
                }
            }
        }
        else
        {
            if(leftToRead <= Q_INT64_C(0))
            {
                break;
            }
            quint8 secondByte = readUnsignedByte(device);
            leftToRead--;
            bool endOfBitmap = false;
            switch(secondByte)
            {
            case 0:
                col = 0;
                row++;
                break;
            case 1:
                endOfBitmap = true;
                break;
            case 2:
                {
                    if(leftToRead > Q_INT64_C(0))
                    {
                        quint8 horizOffset = readUnsignedByte(device);
                        leftToRead--;
                        if(leftToRead > Q_INT64_C(0))
                        {
                            quint8 vertOffset = readUnsignedByte(device);
                            leftToRead--;
                            row += vertOffset;
                            col += horizOffset;
                            if(col >= width)
                            {
                                col = 0;
                                row++;
                            }
                        }
                    }
                }
                break;
            default:
                {
                    quint8 colorIndexes[] = {0, 0};
                    size_t currentIndex = 2;
                    for(quint8 i = 0; i< secondByte; i++)
                    {
                        if(currentIndex > 1)
                        {
                            if(leftToRead > Q_INT64_C(0))
                            {
                                quint8 lowByte = readUnsignedByte(device);
                                leftToRead--;
                                if(leftToRead > Q_INT64_C(0))
                                {
                                    quint8 highByte = readUnsignedByte(device);
                                    leftToRead--;
                                    colorIndexes[0] = lowByte;
                                    colorIndexes[1] = highByte;
                                    currentIndex = 0;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                        result.setPixel(col, height - 1 - row, palette.getPaletteEntryColor(colorIndexes[currentIndex]));
                        col++;
                        if(col >= width)
                        {
                            col = 0;
                            row++;
                        }
                        currentIndex++;
                    }
                }
            }
        }
    }
    return result;
}

quint32 DeviceIndependentBitmapObject::getSizeInWords() const
{
    quint32 sizeInWords = this->size/2;
    if((this->size%2) != 0)
    {
        sizeInWords++;
    }
    return sizeInWords;
}

bool DeviceIndependentBitmapObject::isPaletteRequired() const
{
    if((this->colorUsage == DIB_PAL_COLORS) || (this->colorUsage == DIB_PAL_INDICES))
    {
        return true;
    }
    else
    {
        return false;
    }
}
