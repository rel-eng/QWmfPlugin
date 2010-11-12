/* META_STRETCHDIB record implementation.

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

#include "MetaStretchdibRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaStretchdibRecord::MetaStretchdibRecord() : MetafileRecord(20, META_STRETCHDIB), rasterOperation(SRCCOPY), colorUsage(DIB_RGB_COLORS), srcHeight(0), srcWidth(0), ySrc(0), xSrc(0), destHeight(0), destWidth(0), yDest(0), xDest(0), dib()
{
}

MetaStretchdibRecord::MetaStretchdibRecord(quint32 rasterOperation, quint16 colorUsage, qint16 srcHeight, qint16 srcWidth, qint16 ySrc, qint16 xSrc, qint16 destHeight, qint16 destWidth, qint16 yDest, qint16 xDest, const DeviceIndependentBitmapObject &dib) : MetafileRecord(14 + dib.getSizeInWords(), META_STRETCHDIB), rasterOperation(rasterOperation), colorUsage(colorUsage), srcHeight(srcHeight), srcWidth(srcWidth), ySrc(ySrc), xSrc(xSrc), destHeight(destHeight), destWidth(destWidth), yDest(yDest), xDest(xDest), dib(dib)
{
}

MetaStretchdibRecord::MetaStretchdibRecord(QIODevice &device) : MetafileRecord(device), dib()
{
    if((this->getRecordFunction() & 0x00FF) != (META_STRETCHDIB & 0x00FF))
    {
        throw std::runtime_error("Not a META_STRETCHDIB record");
    }
    this->rasterOperation = readUnsignedDWord(device);
    this->colorUsage = readUnsignedWord(device);
    this->srcHeight = readSignedWord(device);
    this->srcWidth = readSignedWord(device);
    this->ySrc = readSignedWord(device);
    this->xSrc = readSignedWord(device);
    this->destHeight = readSignedWord(device);
    this->destWidth = readSignedWord(device);
    this->yDest = readSignedWord(device);
    this->xDest = readSignedWord(device);
    this->dib = DeviceIndependentBitmapObject(device, this->colorUsage, this->getRecordSizeInWords() * 2 - 28);
}

MetaStretchdibRecord::MetaStretchdibRecord(const MetaStretchdibRecord &rhs) : MetafileRecord(rhs), rasterOperation(rhs.rasterOperation), colorUsage(colorUsage), srcHeight(rhs.srcHeight), srcWidth(rhs.srcWidth), ySrc(rhs.ySrc), xSrc(rhs.xSrc), destHeight(rhs.destHeight), destWidth(rhs.destWidth), yDest(rhs.yDest), xDest(rhs.xDest), dib(rhs.dib)
{
}

MetaStretchdibRecord::~MetaStretchdibRecord()
{
}

MetaStretchdibRecord & MetaStretchdibRecord::operator=(const MetaStretchdibRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->rasterOperation = rhs.rasterOperation;
        this->colorUsage = rhs.colorUsage;
        this->srcHeight = rhs.srcHeight;
        this->srcWidth = rhs.srcWidth;
        this->ySrc = rhs.ySrc;
        this->xSrc = rhs.xSrc;
        this->destHeight = rhs.destHeight;
        this->destWidth = rhs.destWidth;
        this->yDest = rhs.yDest;
        this->xDest = rhs.xDest;
        this->dib = rhs.dib;
    }
    return *this;
}

quint32 MetaStretchdibRecord::getRasterOperation() const
{
    return this->rasterOperation;
}

QRect MetaStretchdibRecord::getSrcRect() const
{
    return QRect(this->xSrc, this->ySrc, this->srcWidth, this->srcHeight);
}

QRect MetaStretchdibRecord::getDestRect() const
{
    return QRect(this->xDest, this->yDest, this->destWidth, this->destHeight);
}

DeviceIndependentBitmapObject MetaStretchdibRecord::getDib() const
{
    return this->dib;
}
