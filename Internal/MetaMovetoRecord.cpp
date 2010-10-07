/* META_MOVETO record implementation.

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

#include "MetaMovetoRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaMovetoRecord::MetaMovetoRecord() : MetafileRecord(5, META_MOVETO), x(0), y(0)
{
}

MetaMovetoRecord::MetaMovetoRecord(qint16 x, qint16 y) : MetafileRecord(5, META_MOVETO), x(x), y(y)
{
}

MetaMovetoRecord::MetaMovetoRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_MOVETO & 0x00FF))
    {
        throw std::runtime_error("Not a META_MOVETO record");
    }
    this->x = readSignedWord(device);
    this->y = readSignedWord(device);
}

MetaMovetoRecord::MetaMovetoRecord(const MetaMovetoRecord &rhs) : MetafileRecord(rhs), x(rhs.x), y(rhs.y)
{
}

MetaMovetoRecord::~MetaMovetoRecord()
{
}

MetaMovetoRecord & MetaMovetoRecord::operator=(const MetaMovetoRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->x = rhs.x;
        this->y = rhs.y;
    }
    return *this;
}

QPoint MetaMovetoRecord::getPoint() const
{
    return QPoint(this->x, this->y);
}
