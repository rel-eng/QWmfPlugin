/* META_SETSTRETCHBLTMODE record implementation.

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

#include "MetaSetstretchbltmodeRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetstretchbltmodeRecord::MetaSetstretchbltmodeRecord() : MetafileRecord(4, META_SETSTRETCHBLTMODE), stretchMode(HALFTONE)
{
}

MetaSetstretchbltmodeRecord::MetaSetstretchbltmodeRecord(quint16 stretchMode) : MetafileRecord(4, META_SETSTRETCHBLTMODE), stretchMode(stretchMode)
{
}

MetaSetstretchbltmodeRecord::MetaSetstretchbltmodeRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETSTRETCHBLTMODE & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETSTRETCHBLTMODE record");
    }
    this->stretchMode = readUnsignedWord(device);
    //Опциональное 16-битное зарезервированное значение не считываем
    if((this->stretchMode != BLACKONWHITE) && (this->stretchMode != WHITEONBLACK) && (this->stretchMode != COLORONCOLOR) && (this->stretchMode != HALFTONE))
    {
        throw std::runtime_error("Invalid stretch mode");
    }
}

MetaSetstretchbltmodeRecord::MetaSetstretchbltmodeRecord(const MetaSetstretchbltmodeRecord &rhs) : MetafileRecord(rhs), stretchMode(rhs.stretchMode)
{
}

MetaSetstretchbltmodeRecord::~MetaSetstretchbltmodeRecord()
{
}

MetaSetstretchbltmodeRecord & MetaSetstretchbltmodeRecord::operator=(const MetaSetstretchbltmodeRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->stretchMode = rhs.stretchMode;
    }
    return *this;
}

quint16 MetaSetstretchbltmodeRecord::getStretchMode() const
{
    return this->stretchMode;
}
