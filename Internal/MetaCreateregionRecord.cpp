/* META_CREATEREGION record implementation.

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

#include "MetaCreateregionRecord.h"

#include <stdexcept>

MetaCreateregionRecord::MetaCreateregionRecord() : MetafileRecord(14, META_CREATEREGION), region()
{
}

MetaCreateregionRecord::MetaCreateregionRecord(const RegionObject &region) : MetafileRecord(3 + region.getSizeInWords(), META_CREATEREGION), region(region)
{
}

MetaCreateregionRecord::MetaCreateregionRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_CREATEREGION & 0x00FF))
    {
        throw std::runtime_error("META_CREATEREGION record");
    }
    this->region = RegionObject(device);
}

MetaCreateregionRecord::MetaCreateregionRecord(const MetaCreateregionRecord &rhs) : MetafileRecord(rhs), region(rhs.region)
{
}

MetaCreateregionRecord::~MetaCreateregionRecord()
{
}

MetaCreateregionRecord & MetaCreateregionRecord::operator=(const MetaCreateregionRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->region = rhs.region;
    }
    return *this;
}

RegionObject MetaCreateregionRecord::getRegion() const
{
    return this->region;
}
