/* META_OFFSETWINDOWORG record implementation.

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

#include "MetaOffsetwindoworgRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaOffsetwindoworgRecord::MetaOffsetwindoworgRecord() : MetafileRecord(5, META_OFFSETWINDOWORG), yOffset(0), xOffset(0)
{
}

MetaOffsetwindoworgRecord::MetaOffsetwindoworgRecord(qint16 xOffset, qint16 yOffset) : MetafileRecord(5, META_OFFSETWINDOWORG), yOffset(yOffset), xOffset(xOffset)
{
}

MetaOffsetwindoworgRecord::MetaOffsetwindoworgRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_OFFSETWINDOWORG & 0x00FF))
    {
        throw std::runtime_error("Not a META_OFFSETWINDOWORG record");
    }
    this->yOffset = readSignedWord(device);
    this->xOffset = readSignedWord(device);
}

MetaOffsetwindoworgRecord::MetaOffsetwindoworgRecord(const MetaOffsetwindoworgRecord &rhs) : MetafileRecord(rhs), yOffset(rhs.yOffset), xOffset(rhs.xOffset)
{
}

MetaOffsetwindoworgRecord::~MetaOffsetwindoworgRecord()
{
}

MetaOffsetwindoworgRecord & MetaOffsetwindoworgRecord::operator=(const MetaOffsetwindoworgRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->yOffset = rhs.yOffset;
        this->xOffset = rhs.xOffset;
    }
    return *this;
}

qint16 MetaOffsetwindoworgRecord::getXOffset() const
{
    return this->xOffset;
}

qint16 MetaOffsetwindoworgRecord::getYOffset() const
{
    return this->yOffset;
}
