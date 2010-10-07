/* META_SETMAPMODE record implementation.

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

#include "MetaSetmapmodeRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetmapmodeRecord::MetaSetmapmodeRecord() : MetafileRecord(4, META_SETMAPMODE), mapMode(MM_TEXT)
{
}

MetaSetmapmodeRecord::MetaSetmapmodeRecord(quint16 mapMode) : MetafileRecord(4, META_SETMAPMODE), mapMode(mapMode)
{
}

MetaSetmapmodeRecord::MetaSetmapmodeRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETMAPMODE & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETMAPMODE record");
    }
    this->mapMode = readUnsignedWord(device);
    bool validMapMode = false;
    switch(this->mapMode)
    {
    case MM_TEXT:
        validMapMode = true;
        break;
    case MM_LOMETRIC:
        validMapMode = true;
        break;
    case MM_HIMETRIC:
        validMapMode = true;
        break;
    case MM_LOENGLISH:
        validMapMode = true;
        break;
    case MM_HIENGLISH:
        validMapMode = true;
        break;
    case MM_TWIPS:
        validMapMode = true;
        break;
    case MM_ISOTROPIC:
        validMapMode = true;
        break;
    case MM_ANISOTROPIC:
        validMapMode = true;
        break;
    deafult:
        validMapMode = false;
    }
    if(!validMapMode)
    {
        throw std::runtime_error("Invalid map mode");
    }
}

MetaSetmapmodeRecord::MetaSetmapmodeRecord(const MetaSetmapmodeRecord &rhs) : MetafileRecord(rhs), mapMode(rhs.mapMode)
{
}

MetaSetmapmodeRecord::~MetaSetmapmodeRecord()
{
}

MetaSetmapmodeRecord & MetaSetmapmodeRecord::operator=(const MetaSetmapmodeRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->mapMode = rhs.mapMode;
    }
    return *this;
}

quint16 MetaSetmapmodeRecord::getMapMode() const
{
    return this->mapMode;
}
