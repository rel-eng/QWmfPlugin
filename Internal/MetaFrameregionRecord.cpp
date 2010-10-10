/* META_FRAMEREGION record implementation.

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

#include "MetaFrameregionRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaFrameregionRecord::MetaFrameregionRecord() : MetafileRecord(7, META_FRAMEREGION), region(0), brush(0), height(0), width(0)
{
}

MetaFrameregionRecord::MetaFrameregionRecord(quint16 region, quint16 brush, qint16 height, qint16 width) : MetafileRecord(7, META_FRAMEREGION), region(region), brush(brush), height(height), width(width)
{
}

MetaFrameregionRecord::MetaFrameregionRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_FRAMEREGION & 0x00FF))
    {
        throw std::runtime_error("Not a META_FRAMEREGION record");
    }
    this->region = readUnsignedWord(device);
    this->brush = readUnsignedWord(device);
    this->height = readSignedWord(device);
    this->width = readSignedWord(device);
}

MetaFrameregionRecord::MetaFrameregionRecord(const MetaFrameregionRecord &rhs) : MetafileRecord(rhs), region(rhs.region), brush(rhs.brush), height(rhs.height), width(rhs.width)
{
}

MetaFrameregionRecord::~MetaFrameregionRecord()
{
}

MetaFrameregionRecord & MetaFrameregionRecord::operator=(const MetaFrameregionRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->region = rhs.region;
        this->brush = rhs.brush;
        this->height = rhs.height;
        this->width = rhs.width;
    }
    return *this;
}

quint16 MetaFrameregionRecord::getRegion() const
{
    return this->region;
}

quint16 MetaFrameregionRecord::getBrush() const
{
    return this->brush;
}

qint16 MetaFrameregionRecord::getHeight() const
{
    return this->height;
}

qint16 MetaFrameregionRecord::getWidth() const
{
    return this->width;
}
