/* META_EXTFLOODFILL record implementation.

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

#include "MetaExtfloodfillRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaExtfloodfillRecord::MetaExtfloodfillRecord() : MetafileRecord(8, META_EXTFLOODFILL), mode(0), color(qRgb(255,255,255)), y(0), x(0)
{
}

MetaExtfloodfillRecord::MetaExtfloodfillRecord(quint16 mode, QRgb color, qint16 y, qint16 x) : MetafileRecord(8, META_EXTFLOODFILL), mode(mode), color(color), y(y), x(x)
{
}

MetaExtfloodfillRecord::MetaExtfloodfillRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_EXTFLOODFILL & 0x00FF))
    {
        throw std::runtime_error("Not a META_EXTFLOODFILL record");
    }
    this->mode = readUnsignedWord(device);
    this->color = readRGBDword(device);
    this->y = readSignedWord(device);
    this->x = readSignedWord(device);
}

MetaExtfloodfillRecord::MetaExtfloodfillRecord(const MetaExtfloodfillRecord &rhs) : MetafileRecord(rhs), mode(rhs.mode), color(rhs.color), y(rhs.y), x(rhs.x)
{
}

MetaExtfloodfillRecord::~MetaExtfloodfillRecord()
{
}

MetaExtfloodfillRecord & MetaExtfloodfillRecord::operator=(const MetaExtfloodfillRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->mode = rhs.mode;
        this->color = rhs.color;
        this->y = rhs.y;
        this->x = rhs.x;
    }
    return *this;
}

QPoint MetaExtfloodfillRecord::getPoint() const
{
    return QPoint(this->x, this->y);
}
