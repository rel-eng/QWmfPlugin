/* META_FILLREGION record implementation.

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

#include "MetaFillregionRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaFillregionRecord::MetaFillregionRecord() : MetafileRecord(5, META_FILLREGION), region(0), brush(0)
{
}

MetaFillregionRecord::MetaFillregionRecord(quint16 region, quint16 brush) : MetafileRecord(5, META_FILLREGION), region(region), brush(brush)
{
}

MetaFillregionRecord::MetaFillregionRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_FILLREGION & 0x00FF))
    {
        throw std::runtime_error("Not a META_FILLREGION record");
    }
    this->region = readUnsignedWord(device);
    this->brush = readUnsignedWord(device);
}

MetaFillregionRecord::MetaFillregionRecord(const MetaFillregionRecord &rhs) : MetafileRecord(rhs), region(rhs.region), brush(rhs.brush)
{
}

MetaFillregionRecord::~MetaFillregionRecord()
{
}

MetaFillregionRecord & MetaFillregionRecord::operator=(const MetaFillregionRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->region = rhs.region;
        this->brush = rhs.brush;
    }
    return *this;
}

quint16 MetaFillregionRecord::getRegion() const
{
    return this->region;
}

quint16 MetaFillregionRecord::getBrush() const
{
    return this->brush;
}
