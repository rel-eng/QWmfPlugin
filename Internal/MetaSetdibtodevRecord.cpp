/* META_SETDIBTODEV record implementation.

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

#include "MetaSetdibtodevRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetdibtodevRecord::MetaSetdibtodevRecord() : MetafileRecord(18, META_SETDIBTODEV), colorUsage(DIB_RGB_COLORS), scanCount(0), startScan(0), yDib(0), xDib(0), height(0), width(0), yDest(0), xDest(0), dib()
{
}

MetaSetdibtodevRecord::MetaSetdibtodevRecord(quint16 colorUsage, quint16 scanCount, quint16 startScan, quint16 yDib, quint16 xDib, quint16 height, quint16 width, quint16 yDest, quint16 xDest, const DeviceIndependentBitmapObject &dib) : MetafileRecord(12 + dib.getSizeInWords(), META_SETDIBTODEV), colorUsage(colorUsage), scanCount(scanCount), startScan(startScan), yDib(yDib), xDib(xDib), height(height), width(width), yDest(yDest), xDest(xDest), dib(dib)
{
}

MetaSetdibtodevRecord::MetaSetdibtodevRecord(QIODevice &device) : MetafileRecord(device), dib()
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETDIBTODEV & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETDIBTODEV record");
    }
    this->colorUsage = readUnsignedWord(device);
    this->scanCount = readUnsignedWord(device);
    this->startScan = readUnsignedWord(device);
    this->yDib = readUnsignedWord(device);
    this->xDib = readUnsignedWord(device);
    this->height = readUnsignedWord(device);
    this->width = readUnsignedWord(device);
    this->yDest = readUnsignedWord(device);
    this->xDest = readUnsignedWord(device);
    this->dib = DeviceIndependentBitmapObject(device, this->colorUsage, this->getRecordSizeInWords() * 2 - 24);
}

MetaSetdibtodevRecord::MetaSetdibtodevRecord(const MetaSetdibtodevRecord &rhs) : MetafileRecord(rhs), colorUsage(rhs.colorUsage), scanCount(rhs.scanCount), startScan(rhs.startScan), yDib(rhs.yDib), xDib(rhs.xDib), height(rhs.height), width(rhs.width), yDest(rhs.yDest), xDest(rhs.xDest), dib(rhs.dib)
{

}

MetaSetdibtodevRecord::~MetaSetdibtodevRecord()
{
}

MetaSetdibtodevRecord & MetaSetdibtodevRecord::operator=(const MetaSetdibtodevRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->colorUsage = rhs.colorUsage;
        this->scanCount = rhs.scanCount;
        this->startScan = rhs.startScan;
        this->yDib = rhs.yDib;
        this->xDib = rhs.xDib;
        this->height = rhs.height;
        this->width = rhs.width;
        this->yDest = rhs.yDest;
        this->xDest = rhs.xDest;
        this->dib = rhs.dib;
    }
    return *this;
}

quint16 MetaSetdibtodevRecord::getColorUsage() const
{
    return this->colorUsage;
}

quint16 MetaSetdibtodevRecord::getScanCount() const
{
    return this->scanCount;
}

quint16 MetaSetdibtodevRecord::getStartScan() const
{
    return this->startScan;
}

QRect MetaSetdibtodevRecord::getSrcRect() const
{
    return QRect(this->xDib, this->yDib, this->width, this->height);
}

QRect MetaSetdibtodevRecord::getDestRect() const
{
    return QRect(this->xDest, this->yDest, this->width, this->height);
}

DeviceIndependentBitmapObject MetaSetdibtodevRecord::getDIB() const
{
    return this->dib;
}
