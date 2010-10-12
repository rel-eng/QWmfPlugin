/* META_CREATEBRUSHINDIRECT record implementation.

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

#include "MetaCreatebrushindirectRecord.h"

#include <stdexcept>

MetaCreatebrushindirectRecord::MetaCreatebrushindirectRecord() : MetafileRecord(7, META_CREATEBRUSHINDIRECT), brush()
{
}

MetaCreatebrushindirectRecord::MetaCreatebrushindirectRecord(const LogBrushObject &brush) : MetafileRecord(7, META_CREATEBRUSHINDIRECT), brush(brush)
{
}

MetaCreatebrushindirectRecord::MetaCreatebrushindirectRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_CREATEBRUSHINDIRECT & 0x00FF))
    {
        throw std::runtime_error("Not a META_CREATEBRUSHINDIRECT record");
    }
    this->brush = LogBrushObject(device);
}

MetaCreatebrushindirectRecord::MetaCreatebrushindirectRecord(const MetaCreatebrushindirectRecord &rhs) : MetafileRecord(rhs), brush(rhs.brush)
{
}

MetaCreatebrushindirectRecord::~MetaCreatebrushindirectRecord()
{
}

MetaCreatebrushindirectRecord & MetaCreatebrushindirectRecord::operator=(const MetaCreatebrushindirectRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->brush = rhs.brush;
    }
    return *this;
}

LogBrushObject MetaCreatebrushindirectRecord::getBrush() const
{
    return this->brush;
}
