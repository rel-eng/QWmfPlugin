/* META_INVERTREGION record implementation.

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

#include "MetaInvertregionRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaInvertregionRecord::MetaInvertregionRecord() : MetafileRecord(4, META_INVERTREGION), region(0)
{
}

MetaInvertregionRecord::MetaInvertregionRecord(quint16 region) : MetafileRecord(4, META_INVERTREGION), region(region)
{
}

MetaInvertregionRecord::MetaInvertregionRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_INVERTREGION & 0x00FF))
    {
        throw std::runtime_error("Not a META_INVERTREGION record");
    }
    this->region = readUnsignedWord(device);
}

MetaInvertregionRecord::MetaInvertregionRecord(const MetaInvertregionRecord &rhs) : MetafileRecord(rhs), region(rhs.region)
{
}

MetaInvertregionRecord::~MetaInvertregionRecord()
{
}

MetaInvertregionRecord & MetaInvertregionRecord::operator=(const MetaInvertregionRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->region = rhs.region;
    }
    return *this;
}

quint16 MetaInvertregionRecord::getRegion() const
{
    return this->region;
}
