/* META_CREATEPENINDIRECT record implementation.

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

#include "MetaCreatepenindirectRecord.h"

#include <stdexcept>

MetaCreatepenindirectRecord::MetaCreatepenindirectRecord() : MetafileRecord(8, META_CREATEPENINDIRECT), pen()
{
}

MetaCreatepenindirectRecord::MetaCreatepenindirectRecord(const PenObject &pen) : MetafileRecord(8, META_CREATEPENINDIRECT), pen(pen)
{
}

MetaCreatepenindirectRecord::MetaCreatepenindirectRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_CREATEPENINDIRECT & 0x00FF))
    {
        throw std::runtime_error("META_CREATEPENINDIRECT record");
    }
    this->pen = PenObject(device);
}

MetaCreatepenindirectRecord::MetaCreatepenindirectRecord(const MetaCreatepenindirectRecord &rhs) : MetafileRecord(rhs), pen(rhs.pen)
{
}

MetaCreatepenindirectRecord::~MetaCreatepenindirectRecord()
{
}

MetaCreatepenindirectRecord & MetaCreatepenindirectRecord::operator=(const MetaCreatepenindirectRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->pen = rhs.pen;
    }
    return *this;
}

PenObject MetaCreatepenindirectRecord::getPen() const
{
    return this->pen;
}
