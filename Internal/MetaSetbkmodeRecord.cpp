/* META_SETBKMODE record implementation.

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

#include "MetaSetbkmodeRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetbkmodeRecord::MetaSetbkmodeRecord() : MetafileRecord(4, META_SETBKMODE), bkMode(TRANSPARENT)
{
}

MetaSetbkmodeRecord::MetaSetbkmodeRecord(quint16 bkMode) : MetafileRecord(4, META_SETBKMODE), bkMode(bkMode)
{
}

MetaSetbkmodeRecord::MetaSetbkmodeRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETBKMODE & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETBKMODE record");
    }
    this->bkMode = readUnsignedWord(device);
    //Опциональное зарезервированное 16-битное поле не считываем
    if((this->bkMode != TRANSPARENT) && (this->bkMode != OPAQUE))
    {
        throw std::runtime_error("Invalid background mix mode");
    }
}

MetaSetbkmodeRecord::MetaSetbkmodeRecord(const MetaSetbkmodeRecord &rhs) : MetafileRecord(rhs), bkMode(rhs.bkMode)
{
}

MetaSetbkmodeRecord::~MetaSetbkmodeRecord()
{
}

MetaSetbkmodeRecord & MetaSetbkmodeRecord::operator=(const MetaSetbkmodeRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->bkMode = rhs.bkMode;
    }
    return *this;
}

quint16 MetaSetbkmodeRecord::getBkMode() const
{
    return this->bkMode;
}
