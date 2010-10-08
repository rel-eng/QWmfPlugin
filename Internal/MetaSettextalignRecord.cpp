/* META_SETTEXTALIGN record implementation.

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

#include "MetaSettextalignRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSettextalignRecord::MetaSettextalignRecord() : MetafileRecord(4, META_SETTEXTALIGN), textAlignmentMode(TA_NOUPDATECP_TOP_LEFT)
{
}

MetaSettextalignRecord::MetaSettextalignRecord(quint16 textAlignmentMode) : MetafileRecord(4, META_SETTEXTALIGN), textAlignmentMode(textAlignmentMode)
{
}

MetaSettextalignRecord::MetaSettextalignRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETTEXTALIGN & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETTEXTALIGN record");
    }
    this->textAlignmentMode = readUnsignedWord(device);
    //Опциональное 16-битное зарезервированное значение не считываем
}

MetaSettextalignRecord::MetaSettextalignRecord(const MetaSettextalignRecord &rhs) : MetafileRecord(rhs), textAlignmentMode(rhs.textAlignmentMode)
{
}

MetaSettextalignRecord::~MetaSettextalignRecord()
{
}

MetaSettextalignRecord & MetaSettextalignRecord::operator=(const MetaSettextalignRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->textAlignmentMode = rhs.textAlignmentMode;
    }
    return *this;
}

quint16 MetaSettextalignRecord::getTextAlignmentMode() const
{
    return this->textAlignmentMode;
}
