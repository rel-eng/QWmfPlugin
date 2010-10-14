/* BitmapCoreHeader object implementation.

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

#include "BitmapCoreHeaderObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

BitmapCoreHeaderObject::BitmapCoreHeaderObject() : headerSize(12), width(0), height(0), planes(1), bitCount(BI_BITCOUNT_5)
{
}

BitmapCoreHeaderObject::BitmapCoreHeaderObject(quint16 width, quint16 height, quint16 bitCount) : headerSize(12), width(width), height(height), planes(1), bitCount(bitCount)
{
}

BitmapCoreHeaderObject::BitmapCoreHeaderObject(QIODevice &device)
{
    this->headerSize = readUnsignedDWord(device);
    if(this->headerSize != 12)
    {
        throw std::runtime_error("Invalid bitmap core header size");
    }
    this->width = readUnsignedWord(device);
    this->height = readUnsignedWord(device);
    this->planes = readUnsignedWord(device);
    if(this->planes != 1)
    {
        throw std::runtime_error("Invalid bitmap planes count");
    }
    this->bitCount = readUnsignedWord(device);
}

BitmapCoreHeaderObject::BitmapCoreHeaderObject(const BitmapCoreHeaderObject &rhs) : headerSize(rhs.headerSize), width(rhs.width), height(rhs.width), planes(rhs.planes), bitCount(rhs.bitCount)
{
}

BitmapCoreHeaderObject::~BitmapCoreHeaderObject()
{
}

BitmapCoreHeaderObject & BitmapCoreHeaderObject::operator=(const BitmapCoreHeaderObject &rhs)
{
    if (this != &rhs)
    {
        this->headerSize = rhs.headerSize;
        this->width = rhs.width;
        this->height = rhs.height;
        this->planes = rhs.planes;
        this->bitCount = rhs.bitCount;
    }
    return *this;
}

quint16 BitmapCoreHeaderObject::getWidth() const
{
    return this->width;
}

quint16 BitmapCoreHeaderObject::getHeight() const
{
    return this->height;
}

quint16 BitmapCoreHeaderObject::getBitCount() const
{
    return this->bitCount;
}
