/* META_SELECTPALETTE record implementation.

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

#include "MetaSelectpaletteRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSelectpaletteRecord::MetaSelectpaletteRecord() : MetafileRecord(4, META_SELECTPALETTE), paletteIndex(0)
{
}

MetaSelectpaletteRecord::MetaSelectpaletteRecord(quint16 paletteIndex) : MetafileRecord(4, META_SELECTPALETTE), paletteIndex(paletteIndex)
{
}

MetaSelectpaletteRecord::MetaSelectpaletteRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SELECTPALETTE & 0x00FF))
    {
        throw std::runtime_error("Not a META_SELECTPALETTE record");
    }
    this->paletteIndex = readUnsignedWord(device);
}

MetaSelectpaletteRecord::MetaSelectpaletteRecord(const MetaSelectpaletteRecord &rhs) : MetafileRecord(rhs), paletteIndex(rhs.paletteIndex)
{
}

MetaSelectpaletteRecord::~MetaSelectpaletteRecord()
{
}

MetaSelectpaletteRecord & MetaSelectpaletteRecord::operator=(const MetaSelectpaletteRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->paletteIndex = rhs.paletteIndex;
    }
    return *this;
}

quint16 MetaSelectpaletteRecord::getPaletteIndex() const
{
    return this->paletteIndex;
}
