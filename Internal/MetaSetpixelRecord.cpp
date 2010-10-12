/* META_SETPIXEL record implementation.

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

#include "MetaSetpixelRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetpixelRecord::MetaSetpixelRecord() : MetafileRecord(7, META_SETPIXEL), color(qRgb(0, 0, 0)), y(0), x(0)
{
}

MetaSetpixelRecord::MetaSetpixelRecord(QRgb color, qint16 y, qint16 x) : MetafileRecord(7, META_SETPIXEL), color(color), y(y), x(x)
{
}

MetaSetpixelRecord::MetaSetpixelRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETPIXEL & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETPIXEL record");
    }
    this->color = readRGBDword(device);
    this->y = readSignedWord(device);
    this->x = readSignedWord(device);
}

MetaSetpixelRecord::MetaSetpixelRecord(const MetaSetpixelRecord &rhs) : MetafileRecord(rhs), color(rhs.color), y(rhs.y), x(rhs.x)
{
}

MetaSetpixelRecord::~MetaSetpixelRecord()
{
}

MetaSetpixelRecord & MetaSetpixelRecord::operator=(const MetaSetpixelRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->color = rhs.color;
        this->y = rhs.y;
        this->x = rhs.x;
    }
    return *this;
}

QRgb MetaSetpixelRecord::getColor() const
{
    return this->color;
}

QPoint MetaSetpixelRecord::getPoint() const
{
    return QPoint(this->x, this->y);
}
