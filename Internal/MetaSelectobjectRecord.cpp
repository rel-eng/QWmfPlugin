/* META_SELECTOBJECT record implementation.

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

#include "MetaSelectobjectRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSelectobjectRecord::MetaSelectobjectRecord() : MetafileRecord(4, META_SELECTOBJECT), objectIndex(0)
{
}

MetaSelectobjectRecord::MetaSelectobjectRecord(quint16 objectIndex) : MetafileRecord(4, META_SELECTOBJECT), objectIndex(objectIndex)
{
}

MetaSelectobjectRecord::MetaSelectobjectRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SELECTOBJECT & 0x00FF))
    {
        throw std::runtime_error("Not a META_SELECTOBJECT record");
    }
    this->objectIndex = readUnsignedWord(device);
}

MetaSelectobjectRecord::MetaSelectobjectRecord(const MetaSelectobjectRecord &rhs) : MetafileRecord(rhs), objectIndex(rhs.objectIndex)
{
}

MetaSelectobjectRecord::~MetaSelectobjectRecord()
{
}

MetaSelectobjectRecord & MetaSelectobjectRecord::operator=(const MetaSelectobjectRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->objectIndex = rhs.objectIndex;
    }
    return *this;
}

quint16 MetaSelectobjectRecord::getObjectIndex() const
{
    return this->objectIndex;
}
