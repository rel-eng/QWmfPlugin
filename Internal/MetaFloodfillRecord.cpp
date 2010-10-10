/* META_FLOODFILL record implementation.

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

#include "MetaFloodfillRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaFloodfillRecord::MetaFloodfillRecord() : MetafileRecord(7, META_FLOODFILL), color(qRgb(255,255,255)), yStart(0), xStart(0)
{
}

MetaFloodfillRecord::MetaFloodfillRecord(QRgb color, qint16 yStart, qint16 xStart) : MetafileRecord(7, META_FLOODFILL), color(color), yStart(yStart), xStart(xStart)
{
}

MetaFloodfillRecord::MetaFloodfillRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_FLOODFILL & 0x00FF))
    {
        throw std::runtime_error("Not a META_FLOODFILL record");
    }
    this->color = readRGBDword(device);
    this->yStart = readSignedWord(device);
    this->xStart = readSignedWord(device);
}

MetaFloodfillRecord::MetaFloodfillRecord(const MetaFloodfillRecord &rhs) : MetafileRecord(rhs), color(rhs.color), yStart(rhs.yStart), xStart(rhs.xStart)
{
}

MetaFloodfillRecord::~MetaFloodfillRecord()
{
}

MetaFloodfillRecord & MetaFloodfillRecord::operator=(const MetaFloodfillRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->color = rhs.color;
        this->yStart = rhs.yStart;
        this->xStart = rhs.xStart;
    }
    return *this;
}

QRgb MetaFloodfillRecord::getColor() const
{
    return this->color;
}

QPoint MetaFloodfillRecord::getStart() const
{
    return QPoint(this->xStart, this->yStart);
}
