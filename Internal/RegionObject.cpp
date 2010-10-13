/* Region object implementation.

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

#include "RegionObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

RegionObject::RegionObject() : nextInChain(0), objectType(0x0006), objectCount(0), regionSize(22), scanCount(0), maxScan(0), boundingRectangle(), scans()
{
}

RegionObject::RegionObject(quint16 scanCount, const QVector<ScanObject> &scans) : nextInChain(0), objectType(0x0006), objectCount(0), regionSize(22), scanCount(scans.count()), maxScan(0), boundingRectangle(), scans(scans)
{
    if(scans.count() > 0xFFFF)
    {
        throw std::runtime_error("Too much scans");
    }
    if(scans.count() > 0)
    {
        quint16 scansLength = 0;
        quint16 maxScanLength = 0;
        int minX;
        int maxX;
        int minY;
        int maxY;
        for(int i = 0; i < scans.count(); i++)
        {
            if(scans.at(i).getScanCount() > 0)
            {
                minX = scans.at(i).getScan(0).first;
                maxX = scans.at(i).getScan(0).second;
                minY = scans.at(i).getTop();
                maxY = scans.at(i).getBottom();
            }
        }
        for(int i = 0; i < scans.count(); i++)
        {
            quint16 currentScanLength = (8 + 4 * static_cast<quint16>(scans.at(i).getScanCount()));
            scansLength += currentScanLength;
            if(currentScanLength > maxScanLength)
            {
                maxScanLength = currentScanLength;
            }
            if(scans.at(i).getScanCount() > 0)
            {
                if(scans.at(i).getTop() < minY)
                {
                    minY = scans.at(i).getTop();
                }
                if(scans.at(i).getBottom() < minY)
                {
                    minY = scans.at(i).getBottom();
                }
                if(scans.at(i).getTop() > maxY)
                {
                    maxY = scans.at(i).getTop();
                }
                if(scans.at(i).getBottom() > maxY)
                {
                    maxY = scans.at(i).getBottom();
                }
                for(int j = 0; j < scans.at(i).getScanCount(); i++)
                {
                    if(scans.at(i).getScan(j).first < minX)
                    {
                        minX = scans.at(i).getScan(j).first;
                    }
                    if(scans.at(i).getScan(j).second < minX)
                    {
                        minX = scans.at(i).getScan(j).second;
                    }
                    if(scans.at(i).getScan(j).first > maxX)
                    {
                        maxX = scans.at(i).getScan(j).first;
                    }
                    if(scans.at(i).getScan(j).second > maxX)
                    {
                        maxX = scans.at(i).getScan(j).second;
                    }
                }
            }
        }
        this->regionSize += scansLength;
        this->maxScan = maxScanLength;
        this->boundingRectangle = RectObject(minX, minY, maxX, maxY);
    }
}

RegionObject::RegionObject(QIODevice &device) : scans()
{
    this->nextInChain = readUnsignedWord(device);
    this->objectType = readSignedWord(device);
    if(this->objectType !=  0x0006)
    {
        throw std::runtime_error("Invalid object type");
    }
    this->objectCount = readUnsignedDWord(device);
    this->regionSize = readUnsignedWord(device);
    this->scanCount = readUnsignedWord(device);
    this->maxScan = readUnsignedWord(device);
    this->boundingRectangle = RectObject(device);
    this->scans = QVector<ScanObject>(this->scanCount);
    for(quint16 i = 0; i < this->scanCount; i++)
    {
        this->scans[i] = ScanObject(device);
    }
}

RegionObject::RegionObject(const RegionObject &rhs) : nextInChain(rhs.nextInChain), objectType(rhs.objectType), objectCount(rhs.objectCount), regionSize(rhs.regionSize), scanCount(rhs.scanCount), maxScan(rhs.maxScan), boundingRectangle(rhs.boundingRectangle), scans(rhs.scans)
{
}

RegionObject::~RegionObject()
{
}

RegionObject & RegionObject::operator=(const RegionObject &rhs)
{
    if (this != &rhs)
    {
        this->nextInChain = rhs.nextInChain;
        this->objectType = rhs.objectType;
        this->objectCount = rhs.objectCount;
        this->regionSize = rhs.regionSize;
        this->scanCount = rhs.scanCount;
        this->maxScan = rhs.maxScan;
        this->boundingRectangle = rhs.boundingRectangle;
        this->scans = rhs.scans;
    }
    return *this;
}

int RegionObject::getScanCount() const
{
    return this->scans.count();
}

QRect RegionObject::getBoundingRectangle() const
{
    return this->boundingRectangle.getRect();
}

ScanObject RegionObject::getScan(int index) const
{
    if((index < 0) || (index >= this->scans.count()))
    {
        throw std::runtime_error("Invalid scan index");
    }
    return this->scans.at(index);
}

quint32 RegionObject::getSizeInWords() const
{
    return (this->regionSize/2) + (this->regionSize%2);
}
