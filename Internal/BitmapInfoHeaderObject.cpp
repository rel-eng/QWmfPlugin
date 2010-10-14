/* BitmapInfoHeader object implementation.

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

#include "BitmapInfoHeaderObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

BitmapInfoHeaderObject::BitmapInfoHeaderObject() : headerSize(40), width(0), height(0), planes(1), bitCount(BI_BITCOUNT_5), compression(BI_RGB), imageSize(0), xPelsPerMeter(0), yPelsPerMeter(0), colorsUsed(0), colorsImportant(0)
{
}

BitmapInfoHeaderObject::BitmapInfoHeaderObject(qint32 width, qint32 height, quint16 bitCount, quint32 compression, quint32 imageSize, qint32 xPelsPerMeter, qint32 yPelsPerMeter, quint32 colorsUsed, quint32 colorsImportant) : headerSize(40), width(width), height(height), planes(1), bitCount(bitCount), compression(compression), imageSize(imageSize), xPelsPerMeter(xPelsPerMeter), yPelsPerMeter(yPelsPerMeter), colorsUsed(colorsUsed), colorsImportant(colorsImportant)
{
}

BitmapInfoHeaderObject::BitmapInfoHeaderObject(QIODevice &device)
{
    this->headerSize = readUnsignedDWord(device);
    if(this->headerSize != 40)
    {
        throw std::runtime_error("Invalid bitmap info header size");
    }
    this->width = readSignedDWord(device);
    if(this->width <= 0)
    {
        throw std::runtime_error("Invalid bitmap width");
    }
    this->height = readSignedDWord(device);
    if(this->height == 0)
    {
        throw std::runtime_error("Invalid bitmap height");
    }
    this->planes = readUnsignedWord(device);
    if(this->planes != 1)
    {
        throw std::runtime_error("Invalid bitmap planes count");
    }
    this->bitCount = readUnsignedWord(device);
    this->compression = readUnsignedDWord(device);
    this->imageSize = readUnsignedDWord(device);
    this->xPelsPerMeter = readSignedDWord(device);
    this->yPelsPerMeter = readSignedDWord(device);
    this->colorsUsed = readUnsignedDWord(device);
    this->colorsImportant = readUnsignedDWord(device);
}

BitmapInfoHeaderObject::BitmapInfoHeaderObject(const BitmapInfoHeaderObject &rhs) : headerSize(rhs.headerSize), width(rhs.width), height(rhs.height), planes(rhs.planes), bitCount(rhs.bitCount), compression(rhs.compression), imageSize(rhs.imageSize), xPelsPerMeter(rhs.xPelsPerMeter), yPelsPerMeter(rhs.yPelsPerMeter), colorsUsed(rhs.colorsUsed), colorsImportant(rhs.colorsImportant)
{
}

BitmapInfoHeaderObject::~BitmapInfoHeaderObject()
{
}

BitmapInfoHeaderObject & BitmapInfoHeaderObject::operator=(const BitmapInfoHeaderObject &rhs)
{
    if (this != &rhs)
    {
        this->headerSize = rhs.headerSize;
        this->width = rhs.width;
        this->height = rhs.height;
        this->planes = rhs.planes;
        this->bitCount = rhs.bitCount;
        this->compression = rhs.compression;
        this->imageSize = rhs.imageSize;
        this->xPelsPerMeter = rhs.xPelsPerMeter;
        this->yPelsPerMeter = rhs.yPelsPerMeter;
        this->colorsUsed = rhs.colorsUsed;
        this->colorsImportant = rhs.colorsImportant;
    }
    return *this;
}

qint32 BitmapInfoHeaderObject::getWidth() const
{
    return this->width;
}

qint32 BitmapInfoHeaderObject::getHeight() const
{
    return this->height;
}

quint16 BitmapInfoHeaderObject::getBitCount() const
{
    return this->bitCount;
}

quint32 BitmapInfoHeaderObject::getCompression() const
{
    return this->compression;
}

quint32 BitmapInfoHeaderObject::getImageSize() const
{
    return this->imageSize;
}

qint32 BitmapInfoHeaderObject::getXPelsPerMeter() const
{
    return this->xPelsPerMeter;
}

qint32 BitmapInfoHeaderObject::getYPelsPerMeter() const
{
    return this->yPelsPerMeter;
}

quint32 BitmapInfoHeaderObject::getColorsUsed() const
{
    return this->colorsUsed;
}

quint32 BitmapInfoHeaderObject::getColorsImportant() const
{
    return this->colorsImportant;
}
