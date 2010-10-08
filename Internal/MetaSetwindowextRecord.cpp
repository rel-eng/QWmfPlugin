/* META_SETWINDOWEXT record implementation.

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

#include "MetaSetwindowextRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetwindowextRecord::MetaSetwindowextRecord() : MetafileRecord(5, META_SETWINDOWEXT), y(1), x(1)
{
}

MetaSetwindowextRecord::MetaSetwindowextRecord(qint16 y, qint16 x) : MetafileRecord(5, META_SETWINDOWEXT), y(y), x(x)
{
}

MetaSetwindowextRecord::MetaSetwindowextRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETWINDOWEXT & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETWINDOWEXT record");
    }
    this->y = readSignedWord(device);
    this->x = readSignedWord(device);
}

MetaSetwindowextRecord::MetaSetwindowextRecord(const MetaSetwindowextRecord &rhs) : MetafileRecord(rhs), y(rhs.y), x(rhs.x)
{
}

MetaSetwindowextRecord::~MetaSetwindowextRecord()
{
}

MetaSetwindowextRecord & MetaSetwindowextRecord::operator=(const MetaSetwindowextRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->y = rhs.y;
        this->x = rhs.x;
    }
    return *this;
}

qint16 MetaSetwindowextRecord::getY() const
{
    return this->y;
}

qint16 MetaSetwindowextRecord::getX() const
{
    return this->x;
}
