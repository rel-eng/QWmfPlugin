/* META_OFFSETCLIPRGN record implementation.

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

#include "MetaOffsetcliprgnRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaOffsetcliprgnRecord::MetaOffsetcliprgnRecord() : MetafileRecord(5, META_OFFSETCLIPRGN), yOffset(0), xOffset(0)
{
}

MetaOffsetcliprgnRecord::MetaOffsetcliprgnRecord(qint16 yOffset, qint16 xOffset) : MetafileRecord(5, META_OFFSETCLIPRGN), yOffset(yOffset), xOffset(xOffset)
{
}

MetaOffsetcliprgnRecord::MetaOffsetcliprgnRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_OFFSETCLIPRGN & 0x00FF))
    {
        throw std::runtime_error("Not a META_OFFSETCLIPRGN record");
    }
    this->yOffset = readSignedWord(device);
    this->xOffset = readSignedWord(device);
}

MetaOffsetcliprgnRecord::MetaOffsetcliprgnRecord(const MetaOffsetcliprgnRecord &rhs) : MetafileRecord(rhs), yOffset(rhs.yOffset), xOffset(rhs.xOffset)
{
}

MetaOffsetcliprgnRecord::~MetaOffsetcliprgnRecord()
{
}

MetaOffsetcliprgnRecord & MetaOffsetcliprgnRecord::operator=(const MetaOffsetcliprgnRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->yOffset = rhs.yOffset;
        this->xOffset = rhs.xOffset;
    }
    return *this;
}

qint16 MetaOffsetcliprgnRecord::getXOffset() const
{
    return this->xOffset;
}

qint16 MetaOffsetcliprgnRecord::getYOffset() const
{
    return this->yOffset;
}
