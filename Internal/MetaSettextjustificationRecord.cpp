/* META_SETTEXTJUSTIFICATION record implementation.

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

#include "MetaSettextjustificationRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSettextjustificationRecord::MetaSettextjustificationRecord() : MetafileRecord(5, META_SETTEXTJUSTIFICATION), breakCount(0), breakExtra(0)
{
}

MetaSettextjustificationRecord::MetaSettextjustificationRecord(quint16 breakCount, quint16 breakExtra) : MetafileRecord(5, META_SETTEXTJUSTIFICATION), breakCount(breakCount), breakExtra(breakExtra)
{
}

MetaSettextjustificationRecord::MetaSettextjustificationRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETTEXTJUSTIFICATION & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETTEXTJUSTIFICATION record");
    }
    this->breakCount = readUnsignedWord(device);
    this->breakExtra = readUnsignedWord(device);
}

MetaSettextjustificationRecord::MetaSettextjustificationRecord(const MetaSettextjustificationRecord &rhs) : MetafileRecord(rhs), breakCount(rhs.breakCount), breakExtra(rhs.breakExtra)
{
}

MetaSettextjustificationRecord::~MetaSettextjustificationRecord()
{
}

MetaSettextjustificationRecord & MetaSettextjustificationRecord::operator=(const MetaSettextjustificationRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->breakCount = rhs.breakCount;
        this->breakExtra = rhs.breakExtra;
    }
    return *this;
}

quint16 MetaSettextjustificationRecord::getBreakCount() const
{
    return this->breakCount;
}

quint16 MetaSettextjustificationRecord::getBreakExtra() const
{
    return this->breakExtra;
}
