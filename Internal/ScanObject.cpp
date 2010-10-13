/* Scan object implementation.

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

#include "ScanObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

ScanObject::ScanObject() : scanCount(0), top(0), bottom(0), scans()
{
}

ScanObject::ScanObject(const QVector<QPair<quint16, quint16> > &scans, quint16 top, quint16 bottom) : scanCount(scans.count() * 2), top(top), bottom(bottom), scans(scans)
{
    if((2 * scans.count()) > 0xFFFF)
    {
        throw std::runtime_error("Too much scans");
    }
}

ScanObject::ScanObject(QIODevice &device) : scanCount(0), top(0), bottom(0), scans(scans)
{
    this->scanCount = readUnsignedWord(device);
    if((this->scanCount % 2) != 0)
    {
        throw std::runtime_error("Invalid scan count");
    }
    int linesCount = scanCount / 2;
    this->top = readUnsignedWord(device);
    this->bottom = readUnsignedWord(device);
    if(linesCount > 0)
    {
        //Строки идут сверху вниз или снизу вверх?
        this->scans = QVector<QPair<quint16, quint16> >(linesCount);
        for(int i = 0; i < linesCount; i++)
        {
            quint16 left = readUnsignedWord(device);
            quint16 right = readUnsignedWord(device);
            this->scans[i] = QPair<quint16, quint16>(left, right);
        }
    }
    quint16 scanCount2 = readUnsignedWord(device);
    if(this->scanCount != scanCount2)
    {
        throw std::runtime_error("Invalid scan count");
    }
}

ScanObject::ScanObject(const ScanObject &rhs) : scanCount(rhs.scanCount), top(rhs.top), bottom(rhs.bottom), scans(rhs.scans)
{
}

ScanObject::~ScanObject()
{
}

ScanObject & ScanObject::operator=(const ScanObject &rhs)
{
    if (this != &rhs)
    {
        this->scanCount = rhs.scanCount;
        this->top = rhs.top;
        this->bottom = rhs.bottom;
        this->scans = rhs.scans;
    }
    return *this;
}

int ScanObject::getScanCount() const
{
    return this->scans.count();
}

QPair<quint16, quint16> ScanObject::getScan(int index) const
{
    if((index < 0) || (index >= this->scans.count()))
    {
        throw std::runtime_error("Invalid scan index");
    }
    return this->scans.at(index);
}

quint16 ScanObject::getTop() const
{
    return this->top;
}

quint16 ScanObject::getBottom() const
{
    return this->bottom;
}
