/* META_SETTEXTCHAREXTRA record implementation.

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

#include "MetaSettextcharextraRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSettextcharextraRecord::MetaSettextcharextraRecord() : MetafileRecord(4, META_SETTEXTCHAREXTRA), charExtra(0)
{
}

MetaSettextcharextraRecord::MetaSettextcharextraRecord(quint16 charExtra) : MetafileRecord(4, META_SETTEXTCHAREXTRA), charExtra(charExtra)
{
}

MetaSettextcharextraRecord::MetaSettextcharextraRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETTEXTCHAREXTRA & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETTEXTCHAREXTRA record");
    }
    this->charExtra = readUnsignedWord(device);
}

MetaSettextcharextraRecord::MetaSettextcharextraRecord(const MetaSettextcharextraRecord &rhs) : MetafileRecord(rhs), charExtra(rhs.charExtra)
{
}

MetaSettextcharextraRecord::~MetaSettextcharextraRecord()
{
}

MetaSettextcharextraRecord & MetaSettextcharextraRecord::operator=(const MetaSettextcharextraRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->charExtra = rhs.charExtra;
    }
    return *this;
}

quint16 MetaSettextcharextraRecord::getCharExtra() const
{
    return this->charExtra;
}
