/* META_PATBLT record implementation.

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

#include "MetaPatbltRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaPatbltRecord::MetaPatbltRecord() : MetafileRecord(9, META_PATBLT), rasterOperation(PATCOPY), height(0), width(0), yLeft(0), xLeft(0)
{
}

MetaPatbltRecord::MetaPatbltRecord(quint32 rasterOperation, qint16 height, qint16 width, qint16 yLeft, qint16 xLeft) : MetafileRecord(9, META_PATBLT), rasterOperation(rasterOperation), height(height), width(width), yLeft(yLeft), xLeft(xLeft)
{
}

MetaPatbltRecord::MetaPatbltRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_PATBLT & 0x00FF))
    {
        throw std::runtime_error("Not a META_PATBLT record");
    }
    this->rasterOperation = readUnsignedDWord(device);
    this->height = readSignedWord(device);
    this->width = readSignedWord(device);
    this->yLeft = readSignedWord(device);
    this->xLeft = readSignedWord(device);
}

MetaPatbltRecord::MetaPatbltRecord(const MetaPatbltRecord &rhs) : MetafileRecord(rhs), rasterOperation(rhs.rasterOperation), height(rhs.height), width(rhs.width), yLeft(rhs.yLeft), xLeft(rhs.xLeft)
{
}

MetaPatbltRecord::~MetaPatbltRecord()
{
}

MetaPatbltRecord & MetaPatbltRecord::operator=(const MetaPatbltRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->rasterOperation = rhs.rasterOperation;
        this->height = rhs.height;
        this->width = rhs.width;
        this->yLeft = rhs.yLeft;
        this->xLeft = rhs.xLeft;
    }
    return *this;
}

quint32 MetaPatbltRecord::getRasterOperation() const
{
    return this->rasterOperation;
}

QRect MetaPatbltRecord::getRect() const
{
    return QRect(this->xLeft, this->yLeft, this->width, this->height);
}
