/* META_ANIMATEPALETTE record implementation.

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

#include "MetaAnimatepaletteRecord.h"

#include <stdexcept>

MetaAnimatepaletteRecord::MetaAnimatepaletteRecord() : MetafileRecord(5, META_ANIMATEPALETTE), palette()
{
}

MetaAnimatepaletteRecord::MetaAnimatepaletteRecord(const PaletteObject &palette) : MetafileRecord(5 + 2 * palette.getPaletteEntriesCount(), META_ANIMATEPALETTE), palette(palette)
{
}

MetaAnimatepaletteRecord::MetaAnimatepaletteRecord(QIODevice &device) : MetafileRecord(device), palette()
{
    if((this->getRecordFunction() & 0x00FF) != (META_ANIMATEPALETTE & 0x00FF))
    {
        throw std::runtime_error("Not a META_ANIMATEPALETTE record");
    }
    this->palette = PaletteObject(device);
}

MetaAnimatepaletteRecord::MetaAnimatepaletteRecord(const MetaAnimatepaletteRecord &rhs) : MetafileRecord(rhs), palette(rhs.palette)
{
}

MetaAnimatepaletteRecord::~MetaAnimatepaletteRecord()
{
}

MetaAnimatepaletteRecord & MetaAnimatepaletteRecord::operator=(const MetaAnimatepaletteRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->palette = rhs.palette;
    }
    return *this;
}

PaletteObject MetaAnimatepaletteRecord::getPalette() const
{
    return this->palette;
}
