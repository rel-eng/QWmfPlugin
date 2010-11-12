/* META_STRETCHBLT record implementation.

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

#include "MetaStretchbltRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaStretchbltRecord::MetaStretchbltRecord() : MetafileRecord(18, META_STRETCHBLT), rasterOperation(SRCCOPY), srcHeight(0), srcWidth(0), ySrc(0), xSrc(0), destHeight(0), destWidth(0), yDest(0), xDest(0), target()
{
}

MetaStretchbltRecord::MetaStretchbltRecord(quint32 rasterOperation, qint16 srcHeight, qint16 srcWidth, qint16 ySrc, qint16 xSrc, qint16 destHeight, qint16 destWidth, qint16 yDest, qint16 xDest, const Bitmap16Object &target) : MetafileRecord(13 + target.getSizeInWords(), META_STRETCHBLT), rasterOperation(rasterOperation), srcHeight(srcHeight), srcWidth(srcWidth), ySrc(ySrc), xSrc(xSrc), destHeight(destHeight), destWidth(destWidth), yDest(yDest), xDest(xDest), target(target)
{
}

MetaStretchbltRecord::MetaStretchbltRecord(QIODevice &device) : MetafileRecord(device), target()
{
    if((this->getRecordFunction() & 0x00FF) != (META_STRETCHBLT & 0x00FF))
    {
        throw std::runtime_error("Not a META_STRETCHBLT record");
    }
    bool hasBitmap = false;
    if(this->getRecordSizeInWords() != ((this->getRecordFunction() >> 8)+3))
    {
        hasBitmap = true;
    }
    this->rasterOperation = readUnsignedDWord(device);
    this->srcHeight = readSignedWord(device);
    this->srcWidth = readSignedWord(device);
    this->ySrc = readSignedWord(device);
    this->xSrc = readSignedWord(device);
    if(!hasBitmap)
    {
        //Зарезервированное поле
        readUnsignedWord(device);
    }
    this->destHeight = readSignedWord(device);
    this->destWidth = readSignedWord(device);
    this->yDest = readSignedWord(device);
    this->xDest = readSignedWord(device);
    if(hasBitmap)
    {
        this->target = Bitmap16Object(device);
    }
}

MetaStretchbltRecord::MetaStretchbltRecord(const MetaStretchbltRecord &rhs) : MetafileRecord(rhs), rasterOperation(rhs.rasterOperation), srcHeight(rhs.srcHeight), srcWidth(rhs.srcWidth), ySrc(rhs.ySrc), xSrc(rhs.xSrc), destHeight(rhs.destHeight), destWidth(rhs.destWidth), yDest(rhs.yDest), xDest(rhs.xDest), target(rhs.target)
{
}

MetaStretchbltRecord::~MetaStretchbltRecord()
{
}

MetaStretchbltRecord & MetaStretchbltRecord::operator=(const MetaStretchbltRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->rasterOperation = rhs.rasterOperation;
        this->srcHeight = rhs.srcHeight;
        this->srcWidth = rhs.srcWidth;
        this->ySrc = rhs.ySrc;
        this->xSrc = rhs.xSrc;
        this->destHeight = rhs.destHeight;
        this->destWidth = rhs.destWidth;
        this->yDest = rhs.yDest;
        this->xDest = rhs.xDest;
        this->target = rhs.target;
    }
    return *this;
}

quint32 MetaStretchbltRecord::getRasterOperation() const
{
    return this->rasterOperation;
}

QRect MetaStretchbltRecord::getSrcRect() const
{
    return QRect(this->xSrc, this->ySrc, this->srcWidth, this->srcHeight);
}

QRect MetaStretchbltRecord::getDestRect() const
{
    return QRect(this->xDest, this->yDest, this->destWidth, this->destHeight);
}

Bitmap16Object MetaStretchbltRecord::getTarget() const
{
    return this->target;
}
