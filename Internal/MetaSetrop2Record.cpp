/* META_SETROP2 record implementation.

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

#include "MetaSetrop2Record.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetrop2Record::MetaSetrop2Record() : MetafileRecord(4, META_SETROP2), drawMode(R2_COPYPEN)
{
}

MetaSetrop2Record::MetaSetrop2Record(quint16 drawMode) : MetafileRecord(4, META_SETROP2), drawMode(drawMode)
{
}

MetaSetrop2Record::MetaSetrop2Record(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETROP2 & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETROP2 record");
    }
    this->drawMode = readUnsignedWord(device);
    //Опциональное 16-битное зарезервированное значение не считываем
    bool isValidMode = false;
    switch(this->drawMode)
    {
    case R2_BLACK:
        isValidMode = true;
        break;
    case R2_NOTMERGEPEN:
        isValidMode = true;
        break;
    case R2_MASKNOTPEN:
        isValidMode = true;
        break;
    case R2_NOTCOPYPEN:
        isValidMode = true;
        break;
    case R2_MASKPENNOT:
        isValidMode = true;
        break;
    case R2_NOT:
        isValidMode = true;
        break;
    case R2_XORPEN:
        isValidMode = true;
        break;
    case R2_NOTMASKPEN:
        isValidMode = true;
        break;
    case R2_MASKPEN:
        isValidMode = true;
        break;
    case R2_NOTXORPEN:
        isValidMode = true;
        break;
    case R2_NOP:
        isValidMode = true;
        break;
    case R2_MERGENOTPEN:
        isValidMode = true;
        break;
    case R2_COPYPEN:
        isValidMode = true;
        break;
    case R2_MERGEPENNOT:
        isValidMode = true;
        break;
    case R2_MERGEPEN:
        isValidMode = true;
        break;
    case R2_WHITE:
        isValidMode = true;
        break;
    default:
        isValidMode = false;
    }
    if(!isValidMode)
    {
        throw std::runtime_error("Invalid draw mode");
    }
}

MetaSetrop2Record::MetaSetrop2Record(const MetaSetrop2Record &rhs) : MetafileRecord(rhs), drawMode(rhs.drawMode)
{
}

MetaSetrop2Record::~MetaSetrop2Record()
{
}

MetaSetrop2Record & MetaSetrop2Record::operator=(const MetaSetrop2Record &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->drawMode = rhs.drawMode;
    }
    return *this;
}

quint16 MetaSetrop2Record::getDrawMode() const
{
    return this->drawMode;
}
