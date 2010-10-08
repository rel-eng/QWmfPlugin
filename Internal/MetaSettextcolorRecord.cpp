/* META_SETTEXTCOLOR record implementation.

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

#include "MetaSettextcolorRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSettextcolorRecord::MetaSettextcolorRecord() : MetafileRecord(5, META_SETTEXTCOLOR), color(qRgb(0,0,0))
{
}

MetaSettextcolorRecord::MetaSettextcolorRecord(QRgb color) : MetafileRecord(5, META_SETTEXTCOLOR), color(color)
{
}

MetaSettextcolorRecord::MetaSettextcolorRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETTEXTCOLOR & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETTEXTCOLOR record");
    }
    this->color = readRGBDword(device);
}

MetaSettextcolorRecord::MetaSettextcolorRecord(const MetaSettextcolorRecord &rhs) : MetafileRecord(rhs), color(rhs.color)
{
}

MetaSettextcolorRecord::~MetaSettextcolorRecord()
{
}

MetaSettextcolorRecord & MetaSettextcolorRecord::operator=(const MetaSettextcolorRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->color = rhs.color;
    }
    return *this;
}

QRgb MetaSettextcolorRecord::getColor() const
{
    return this->color;
}
