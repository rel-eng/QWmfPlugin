/* META_ESCAPE record implementation.

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

#include "MetaEscapeRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaEscapeRecord::MetaEscapeRecord() : MetafileRecord(5, META_ESCAPE), escapeFunction(FLUSHOUT), byteCount(0)
{
}

MetaEscapeRecord::MetaEscapeRecord(quint16 escapeFunction, quint16 byteCount) : MetafileRecord(5, META_ESCAPE), escapeFunction(escapeFunction), byteCount(byteCount)
{
}

MetaEscapeRecord::MetaEscapeRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_ESCAPE & 0x00FF))
    {
        throw std::runtime_error("Not a META_ESCAPE record");
    }
    this->escapeFunction = readUnsignedWord(device);
    this->byteCount = readUnsignedWord(device);
}

MetaEscapeRecord::MetaEscapeRecord(const MetaEscapeRecord &rhs) : MetafileRecord(rhs), escapeFunction(rhs.escapeFunction), byteCount(rhs.byteCount)
{
}

MetaEscapeRecord::~MetaEscapeRecord()
{
}

MetaEscapeRecord & MetaEscapeRecord::operator=(const MetaEscapeRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->escapeFunction = rhs.escapeFunction;
        this->byteCount = rhs.byteCount;
    }
    return *this;
}

quint16 MetaEscapeRecord::getEscapeFunction() const
{
    return this->escapeFunction;
}

quint16 MetaEscapeRecord::getByteCount() const
{
    return this->byteCount;
}
