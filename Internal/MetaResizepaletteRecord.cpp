/* META_RESIZEPALETTE record implementation.

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

#include "MetaResizepaletteRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaResizepaletteRecord::MetaResizepaletteRecord() : MetafileRecord(4, META_RESIZEPALETTE), numberOfEntries(0)
{
}

MetaResizepaletteRecord::MetaResizepaletteRecord(quint16 nemberOfEntries) : MetafileRecord(4, META_RESIZEPALETTE), numberOfEntries(numberOfEntries)
{
}

MetaResizepaletteRecord::MetaResizepaletteRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_RESIZEPALETTE & 0x00FF))
    {
        throw std::runtime_error("Not a META_RESIZEPALETTE record");
    }
    this->numberOfEntries = readUnsignedWord(device);
}

MetaResizepaletteRecord::MetaResizepaletteRecord(const MetaResizepaletteRecord &rhs) : MetafileRecord(rhs), numberOfEntries(rhs.numberOfEntries)
{
}

MetaResizepaletteRecord::~MetaResizepaletteRecord()
{
}

MetaResizepaletteRecord & MetaResizepaletteRecord::operator=(const MetaResizepaletteRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->numberOfEntries = rhs.numberOfEntries;
    }
    return *this;
}

quint16 MetaResizepaletteRecord::getNumberOfEntries()
{
    return this->numberOfEntries;
}
