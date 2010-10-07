/* META_SCALEWINDOWEXT record implementation.

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

#include "MetaScalewindowextRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaScalewindowextRecord::MetaScalewindowextRecord() : MetafileRecord(7, META_SCALEWINDOWEXT), yDenom(1), yNum(1), xDenom(1), xNum(1)
{
}

MetaScalewindowextRecord::MetaScalewindowextRecord(qint16 yDenom, qint16 yNum, qint16 xDenom, qint16 xNum) : MetafileRecord(7, META_SCALEWINDOWEXT), yDenom(yDenom), yNum(yNum), xDenom(xDenom), xNum(xNum)
{
}

MetaScalewindowextRecord::MetaScalewindowextRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SCALEWINDOWEXT & 0x00FF))
    {
        throw std::runtime_error("Not a META_SCALEWINDOWEXT record");
    }
    this->yDenom = readSignedWord(device);
    this->yNum = readSignedWord(device);
    this->xDenom = readSignedWord(device);
    this->xNum = readSignedWord(device);
}

MetaScalewindowextRecord::MetaScalewindowextRecord(const MetaScalewindowextRecord &rhs) : MetafileRecord(rhs), yDenom(rhs.yDenom), yNum(rhs.yNum), xDenom(rhs.xDenom), xNum(rhs.xNum)
{
}

MetaScalewindowextRecord::~MetaScalewindowextRecord()
{
}

MetaScalewindowextRecord & MetaScalewindowextRecord::operator=(const MetaScalewindowextRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->yDenom = rhs.yDenom;
        this->yNum = rhs.yNum;
        this->xDenom = rhs.xDenom;
        this->xNum = rhs.xNum;
    }
    return *this;
}

qint16 MetaScalewindowextRecord::getYDenom() const
{
    return this->yDenom;
}

qint16 MetaScalewindowextRecord::getYNum() const
{
    return this->yNum;
}

qint16 MetaScalewindowextRecord::getXDenom() const
{
    return this->xDenom;
}

qint16 MetaScalewindowextRecord::getXNum() const
{
    return this->xNum;
}
