/* META_PLACEABLE record implementation.

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

#include "MetaPlaceableRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaPlaceableRecord::MetaPlaceableRecord() : key(0x9AC6CDD7), HWmf(0), left(0), top(0), right(0), bottom(0), tpi(1440), reserved(0), checksum(0x52B1)
{
}

MetaPlaceableRecord::MetaPlaceableRecord(quint16 left, quint16 top, quint16 right, quint16 bottom, quint16 tpi) : key(0x9AC6CDD7), HWmf(0), left(left), top(top), right(right), bottom(bottom), tpi(tpi), reserved(0), checksum(0xCDD7 ^ 0x9AC^ left ^ top ^right ^ bottom ^ tpi)
{
}

MetaPlaceableRecord::MetaPlaceableRecord(QIODevice &device)
{
    this->key = readUnsignedDWord(device);
    if(this->key != 0x9AC6CDD7)
    {
        throw std::runtime_error("Invalid WMF key value");
    }
    this->HWmf = readUnsignedWord(device);
    if(this->HWmf != 0)
    {
        throw std::runtime_error("HWmf is non-zero");
    }
    this->left = readUnsignedWord(device);
    this->top = readUnsignedWord(device);
    this->right = readUnsignedWord(device);
    this->bottom = readUnsignedWord(device);
    this->tpi = readUnsignedWord(device);
    this->reserved = readUnsignedDWord(device);
    if(this->reserved != 0)
    {
        throw std::runtime_error("Reserved is non-zero");
    }
    this->checksum = readUnsignedWord(device);
    if(this->checksum != (0xCDD7 ^ 0x9AC6 ^ this->left ^ this->top ^ this->right ^ this->bottom ^ this->tpi))
    {
        throw std::runtime_error("Invalid checksum");
    }
}

MetaPlaceableRecord::MetaPlaceableRecord(const MetaPlaceableRecord &rhs) : key(rhs.key), HWmf(rhs.HWmf), left(rhs.left), top(rhs.top), right(rhs.right), bottom(rhs.bottom), tpi(rhs.tpi), reserved(0), checksum(rhs.checksum)
{
}

MetaPlaceableRecord::~MetaPlaceableRecord()
{
}

MetaPlaceableRecord & MetaPlaceableRecord::operator=(const MetaPlaceableRecord &rhs)
{
    if (this != &rhs)
    {
        this->key = rhs.key;
        this->HWmf = rhs.HWmf;
        this->left = rhs.left;
        this->top = rhs.top;
        this->right = rhs.right;
        this->bottom = rhs.bottom;
        this->tpi = rhs.tpi;
        this->reserved = rhs.reserved;
        this->checksum = rhs.checksum;
    }
    return *this;
}

quint16 MetaPlaceableRecord::getLeft() const
{
    return this->left;
}

quint16 MetaPlaceableRecord::getTop() const
{
    return this->top;
}

quint16 MetaPlaceableRecord::getRight() const
{
    return this->right;
}

quint16 MetaPlaceableRecord::getBottom() const
{
    return this->bottom;
}

quint16 MetaPlaceableRecord::getTpi() const
{
    return this->tpi;
}
