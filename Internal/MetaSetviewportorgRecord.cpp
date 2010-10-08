/* META_SETVIEWPORTORG record implementation.

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

#include "MetaSetviewportorgRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetviewportorgRecord::MetaSetviewportorgRecord() : MetafileRecord(5, META_SETVIEWPORTORG), y(0), x(0)
{
}

MetaSetviewportorgRecord::MetaSetviewportorgRecord(qint16 y, qint16 x) : MetafileRecord(5, META_SETVIEWPORTORG), y(y), x(x)
{
}

MetaSetviewportorgRecord::MetaSetviewportorgRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETVIEWPORTORG & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETVIEWPORTORG record");
    }
    this->y = readSignedWord(device);
    this->x = readSignedWord(device);
}

MetaSetviewportorgRecord::MetaSetviewportorgRecord(const MetaSetviewportorgRecord &rhs) : MetafileRecord(rhs), y(rhs.y), x(rhs.x)
{
}

MetaSetviewportorgRecord::~MetaSetviewportorgRecord()
{
}

MetaSetviewportorgRecord & MetaSetviewportorgRecord::operator=(const MetaSetviewportorgRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->y = rhs.y;
        this->x = rhs.x;
    }
    return *this;
}

QPoint MetaSetviewportorgRecord::getPoint() const
{
    return QPoint(this->x, this->y);
}
