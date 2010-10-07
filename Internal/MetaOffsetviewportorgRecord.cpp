/* META_OFFSETVIEWPORTORG record implementation.

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

#include "MetaOffsetviewportorgRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaOffsetviewportorgRecord::MetaOffsetviewportorgRecord() : MetafileRecord(5, META_OFFSETVIEWPORTORG), xOffset(0), yOffset(0)
{
}

MetaOffsetviewportorgRecord::MetaOffsetviewportorgRecord(qint16 xOffset, qint16 yOffset) : MetafileRecord(5, META_OFFSETVIEWPORTORG), xOffset(xOffset), yOffset(yOffset)
{
}

MetaOffsetviewportorgRecord::MetaOffsetviewportorgRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_OFFSETVIEWPORTORG & 0x00FF))
    {
        throw std::runtime_error("Not a META_OFFSETVIEWPORTORG record");
    }
    this->xOffset = readSignedWord(device);
    this->yOffset = readSignedWord(device);
}

MetaOffsetviewportorgRecord::MetaOffsetviewportorgRecord(const MetaOffsetviewportorgRecord &rhs) : MetafileRecord(rhs), xOffset(rhs.xOffset), yOffset(rhs.yOffset)
{
}

MetaOffsetviewportorgRecord::~MetaOffsetviewportorgRecord()
{
}

MetaOffsetviewportorgRecord & MetaOffsetviewportorgRecord::operator=(const MetaOffsetviewportorgRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->xOffset = rhs.xOffset;
        this->yOffset = rhs.yOffset;
    }
    return *this;
}

qint16 MetaOffsetviewportorgRecord::getXOffset() const
{
    return this->xOffset;
}

qint16 MetaOffsetviewportorgRecord::getYOffset() const
{
    return this->yOffset;
}
