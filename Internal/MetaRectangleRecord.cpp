/* META_RECTANGLE record implementation.

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

#include "MetaRectangleRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaRectangleRecord::MetaRectangleRecord() : MetafileRecord(7, META_RECTANGLE), bottomRect(0), rightRect(0), topRect(0), leftRect(0)
{
}

MetaRectangleRecord::MetaRectangleRecord(qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect) : MetafileRecord(7, META_RECTANGLE), bottomRect(bottomRect), rightRect(rightRect), topRect(topRect), leftRect(leftRect)
{
}

MetaRectangleRecord::MetaRectangleRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_RECTANGLE & 0x00FF))
    {
        throw std::runtime_error("Not a META_RECTANGLE record");
    }
    this->bottomRect = readSignedWord(device);
    this->rightRect = readSignedWord(device);
    this->topRect = readSignedWord(device);
    this->leftRect = readSignedWord(device);
}

MetaRectangleRecord::MetaRectangleRecord(const MetaRectangleRecord &rhs) : MetafileRecord(rhs), bottomRect(rhs.bottomRect), rightRect(rhs.rightRect), topRect(rhs.topRect), leftRect(rhs.leftRect)
{
}

MetaRectangleRecord::~MetaRectangleRecord()
{
}

MetaRectangleRecord & MetaRectangleRecord::operator=(const MetaRectangleRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->bottomRect = rhs.bottomRect;
        this->rightRect = rhs.rightRect;
        this->topRect = rhs.topRect;
        this->leftRect = rhs.leftRect;
    }
    return *this;
}

QRect MetaRectangleRecord::getRect() const
{
    return QRect(QPoint(this->leftRect,this->topRect), QPoint(this->rightRect, this->bottomRect));
}
