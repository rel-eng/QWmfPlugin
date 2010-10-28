/* META_BITBLT record implementation.

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

#include "MetaBitbltRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaBitbltRecord::MetaBitbltRecord() : MetafileRecord(16, META_BITBLT), rasterOperation(SRCCOPY), ySrc(0), xSrc(0), height(0), width(0), yDest(0), xDest(0), target()
{
}

MetaBitbltRecord::MetaBitbltRecord(quint32 rasterOperation, qint16 ySrc, qint16 xSrc, qint16 height, qint16 width, qint16 yDest, qint16 xDest, const Bitmap16Object &target) : MetafileRecord(11 + target.getSizeInWords(), META_BITBLT), rasterOperation(rasterOperation), ySrc(ySrc), xSrc(xSrc), height(height), width(width), yDest(yDest), xDest(xDest), target(target)
{
}

MetaBitbltRecord::MetaBitbltRecord(QIODevice &device) : MetafileRecord(device), target()
{
    if((this->getRecordFunction() & 0x00FF) != (META_BITBLT & 0x00FF))
    {
        throw std::runtime_error("Not a META_BITBLT record");
    }
    bool hasBitmap = false;
    if(this->getRecordSizeInWords() != ((this->getRecordFunction() >> 8)+3))
    {
        hasBitmap = true;
    }
    this->rasterOperation = readUnsignedDWord(device);
    this->ySrc = readSignedWord(device);
    this->xSrc = readSignedWord(device);
    if(!hasBitmap)
    {
        //Зарезервированное поле
        readUnsignedWord(device);
    }
    this->height = readSignedWord(device);
    this->width = readSignedWord(device);
    this->yDest = readSignedWord(device);
    this->xDest = readSignedWord(device);
    if(hasBitmap)
    {
        this->target = Bitmap16Object(device);
    }
}

MetaBitbltRecord::MetaBitbltRecord(const MetaBitbltRecord &rhs) : MetafileRecord(rhs), rasterOperation(rhs.rasterOperation), ySrc(rhs.ySrc), xSrc(rhs.xSrc), height(rhs.height), width(rhs.width), yDest(rhs.yDest), xDest(rhs.xDest), target(rhs.target)
{
}

MetaBitbltRecord::~MetaBitbltRecord()
{
}

MetaBitbltRecord & MetaBitbltRecord::operator=(const MetaBitbltRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->rasterOperation = rhs.rasterOperation;
        this->ySrc = rhs.ySrc;
        this->xSrc = rhs.xSrc;
        this->height = rhs.height;
        this->width = rhs.width;
        this->yDest = rhs.yDest;
        this->xDest = rhs.xDest;
        this->target = rhs.target;
    }
    return *this;
}

quint32 MetaBitbltRecord::getRasterOperation() const
{
    return this->rasterOperation;
}

QRect MetaBitbltRecord::getSrcRect() const
{
    return QRect(this->xSrc, this->ySrc, this->width, this->height);
}

QRect MetaBitbltRecord::getDestRect() const
{
    return QRect(this->xDest, this->yDest, this->width, this->height);
}

Bitmap16Object MetaBitbltRecord::getTarget() const
{
    return this->target;
}
