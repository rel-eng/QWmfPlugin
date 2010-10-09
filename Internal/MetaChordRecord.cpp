/* META_CHORD record implementation.

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

#include "MetaChordRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaChordRecord::MetaChordRecord() : MetafileRecord(11, META_CHORD), yRadial2(0), xRadial2(0), yRadial1(0), xRadial1(0), bottomRect(0), rightRect(0), topRect(0), leftRect(0)
{
}

MetaChordRecord::MetaChordRecord(qint16 yRadial2, qint16 xRadial2, qint16 yRadial1, qint16 xRadial1, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect) : MetafileRecord(11, META_CHORD), yRadial2(yRadial2), xRadial2(xRadial2), yRadial1(yRadial1), xRadial1(xRadial1), bottomRect(bottomRect), rightRect(rightRect), topRect(topRect), leftRect(leftRect)
{
}

MetaChordRecord::MetaChordRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_CHORD & 0x00FF))
    {
        throw std::runtime_error("Not a META_CHORD record");
    }
    this->yRadial2 = readSignedWord(device);
    this->xRadial2 = readSignedWord(device);
    this->yRadial1 = readSignedWord(device);
    this->xRadial1 = readSignedWord(device);
    this->bottomRect = readSignedWord(device);
    this->rightRect = readSignedWord(device);
    this->topRect = readSignedWord(device);
    this->leftRect = readSignedWord(device);
}

MetaChordRecord::MetaChordRecord(const MetaChordRecord &rhs) : MetafileRecord(rhs), yRadial2(rhs.yRadial2), xRadial2(rhs.xRadial2), yRadial1(rhs.yRadial1), xRadial1(rhs.xRadial1), bottomRect(rhs.bottomRect), rightRect(rhs.rightRect), topRect(rhs.topRect), leftRect(rhs.leftRect)
{
}

MetaChordRecord::~MetaChordRecord()
{
}

MetaChordRecord & MetaChordRecord::operator=(const MetaChordRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->yRadial2 = rhs.yRadial2;
        this->xRadial2 = rhs.xRadial2;
        this->yRadial1 = rhs.yRadial1;
        this->xRadial1 = rhs.xRadial1;
        this->bottomRect = rhs.bottomRect;
        this->rightRect = rhs.rightRect;
        this->topRect = rhs.topRect;
        this->leftRect = rhs.leftRect;
    }
    return *this;
}

qint16 MetaChordRecord::getYRadial2() const
{
    return this->yRadial2;
}

qint16 MetaChordRecord::getXRadial2() const
{
    return this->xRadial2;
}

qint16 MetaChordRecord::getYRadial1() const
{
    return this->yRadial1;
}

qint16 MetaChordRecord::getXRadial1() const
{
    return this->xRadial1;
}

qint16 MetaChordRecord::getBottomRect() const
{
    return this->bottomRect;
}

qint16 MetaChordRecord::getRightRect() const
{
    return this->rightRect;
}

qint16 MetaChordRecord::getTopRect() const
{
    return this->topRect;
}

qint16 MetaChordRecord::getLeftRect() const
{
    return this->leftRect;
}
