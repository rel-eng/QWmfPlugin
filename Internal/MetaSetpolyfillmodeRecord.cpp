/* META_SETPOLYFILLMODE record implementation.

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

#include "MetaSetpolyfillmodeRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetpolyfillmodeRecord::MetaSetpolyfillmodeRecord() : MetafileRecord(4, META_SETPOLYFILLMODE), polyFillMode(ALTERNATE)
{
}

MetaSetpolyfillmodeRecord::MetaSetpolyfillmodeRecord(quint16 polyFillMode) : MetafileRecord(4, META_SETPOLYFILLMODE), polyFillMode(polyFillMode)
{
}

MetaSetpolyfillmodeRecord::MetaSetpolyfillmodeRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETPOLYFILLMODE & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETPOLYFILLMODE record");
    }
    this->polyFillMode = readUnsignedWord(device);
    //Опциональное зарезервированное 16-битное значение на считываем
    if((this->polyFillMode != ALTERNATE) && (this->polyFillMode != WINDING))
    {
        throw std::runtime_error("Invalidd polygon fill mode");
    }
}

MetaSetpolyfillmodeRecord::MetaSetpolyfillmodeRecord(const MetaSetpolyfillmodeRecord &rhs) : MetafileRecord(rhs), polyFillMode(rhs.polyFillMode)
{
}

MetaSetpolyfillmodeRecord::~MetaSetpolyfillmodeRecord()
{
}

MetaSetpolyfillmodeRecord & MetaSetpolyfillmodeRecord::operator=(const MetaSetpolyfillmodeRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->polyFillMode = rhs.polyFillMode;
    }
    return *this;
}

quint16 MetaSetpolyfillmodeRecord::getPolyFillMode() const
{
    return this->polyFillMode;
}
