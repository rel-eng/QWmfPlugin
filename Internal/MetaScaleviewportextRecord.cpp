/* META_SCALEVIEWPORTEXT record implementation.

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

#include "MetaScaleviewportextRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaScaleviewportextRecord::MetaScaleviewportextRecord() : MetafileRecord(7, META_SCALEVIEWPORTEXT), yDenom(1), yNum(1), xDenom(1), xNum(1)
{
}

MetaScaleviewportextRecord::MetaScaleviewportextRecord(qint16 yDenom, qint16 yNum, qint16 xDenom, qint16 xNum) : MetafileRecord(7, META_SCALEVIEWPORTEXT), yDenom(yDenom), yNum(yNum), xDenom(xDenom), xNum(xNum)
{
}

MetaScaleviewportextRecord::MetaScaleviewportextRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SCALEVIEWPORTEXT & 0x00FF))
    {
        throw std::runtime_error("Not a META_SCALEVIEWPORTEXT record");
    }
    this->yDenom = readSignedWord(device);
    this->yNum = readSignedWord(device);
    this->xDenom = readSignedWord(device);
    this->xNum = readSignedWord(device);
}

MetaScaleviewportextRecord::MetaScaleviewportextRecord(const MetaScaleviewportextRecord &rhs) : MetafileRecord(rhs), yDenom(rhs.yDenom), yNum(rhs.yNum), xDenom(rhs.xDenom), xNum(rhs.xNum)
{
}

MetaScaleviewportextRecord::~MetaScaleviewportextRecord()
{
}

MetaScaleviewportextRecord & MetaScaleviewportextRecord::operator=(const MetaScaleviewportextRecord &rhs)
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

qint16 MetaScaleviewportextRecord::getYDenom() const
{
    return this->yDenom;
}

qint16 MetaScaleviewportextRecord::getYNum() const
{
    return this->yNum;
}

qint16 MetaScaleviewportextRecord::getXDenom() const
{
    return this->xDenom;
}

qint16 MetaScaleviewportextRecord::getXNum() const
{
    return this->xNum;
}
