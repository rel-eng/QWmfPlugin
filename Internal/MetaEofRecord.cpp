/* META_EOF record implementation.

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

#include "MetaEofRecord.h"

#include <stdexcept>

MetaEofRecord::MetaEofRecord() : MetafileRecord(3, META_EOF)
{
}

MetaEofRecord::MetaEofRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_EOF & 0x00FF))
    {
        throw std::runtime_error("Not a META_EOF record");
    }
}

MetaEofRecord::MetaEofRecord(const MetaEofRecord &rhs) : MetafileRecord(rhs)
{
}

MetaEofRecord::~MetaEofRecord()
{
}

MetaEofRecord & MetaEofRecord::operator=(const MetaEofRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
    }
    return *this;
}
