/* META_ROUNDRECT record implementation.

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

#include "MetaRoundrectRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaRoundrectRecord::MetaRoundrectRecord() : MetafileRecord(9, META_ROUNDRECT), height(0), width(0), bottomRect(0), rightRect(0), topRect(0), leftRect(0)
{
}

MetaRoundrectRecord::MetaRoundrectRecord(qint16 height, qint16 width, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect) : MetafileRecord(9, META_ROUNDRECT), height(height), width(width), bottomRect(bottomRect), rightRect(rightRect), topRect(topRect), leftRect(leftRect)
{
}

MetaRoundrectRecord::MetaRoundrectRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_ROUNDRECT & 0x00FF))
    {
        throw std::runtime_error("Not a META_ROUNDRECT record");
    }
    this->height = readSignedWord(device);
    this->width = readSignedWord(device);
    this->bottomRect = readSignedWord(device);
    this->rightRect = readSignedWord(device);
    this->topRect = readSignedWord(device);
    this->leftRect = readSignedWord(device);
}

MetaRoundrectRecord::MetaRoundrectRecord(const MetaRoundrectRecord &rhs) : MetafileRecord(rhs), height(rhs.height), width(rhs.width), bottomRect(rhs.bottomRect), rightRect(rhs.rightRect), topRect(rhs.topRect), leftRect(rhs.leftRect)
{
}

MetaRoundrectRecord::~MetaRoundrectRecord()
{
}

MetaRoundrectRecord & MetaRoundrectRecord::operator=(const MetaRoundrectRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->height = rhs.height;
        this->width = rhs.width;
        this->bottomRect = rhs.bottomRect;
        this->rightRect = rhs.rightRect;
        this->topRect = rhs.topRect;
        this->leftRect = rhs.leftRect;
    }
    return *this;
}

qint16 MetaRoundrectRecord::getHeight() const
{
    return this->height;
}

qint16 MetaRoundrectRecord::getWidth() const
{
    return this->width;
}

QRect MetaRoundrectRecord::getRect() const
{
    return QRect(QPoint(this->leftRect,this->topRect), QPoint(this->rightRect, this->bottomRect));
}
