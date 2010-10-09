/* META_ARC record implementation.

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

#include "MetaArcRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaArcRecord::MetaArcRecord() : MetafileRecord(11, META_ARC), yEndArc(0), xEndArc(0), yStartArc(0), xStartArc(0), bottomRect(0), rightRect(0), topRect(0), leftRect(0)
{
}

MetaArcRecord::MetaArcRecord(qint16 yEndArc, qint16 xEndArc, qint16 yStartArc, qint16 xStartArc, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect) : MetafileRecord(11, META_ARC), yEndArc(yEndArc), xEndArc(xEndArc), yStartArc(yStartArc), xStartArc(xStartArc), bottomRect(bottomRect), rightRect(rightRect), topRect(topRect), leftRect(leftRect)
{
}

MetaArcRecord::MetaArcRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_ARC & 0x00FF))
    {
        throw std::runtime_error("Not a META_ARC record");
    }
    this->yEndArc = readSignedWord(device);
    this->xEndArc = readSignedWord(device);
    this->yStartArc = readSignedWord(device);
    this->xStartArc = readSignedWord(device);
    this->bottomRect = readSignedWord(device);
    this->rightRect = readSignedWord(device);
    this->topRect = readSignedWord(device);
    this->leftRect = readSignedWord(device);
}

MetaArcRecord::MetaArcRecord(const MetaArcRecord &rhs) : MetafileRecord(rhs), yEndArc(rhs.yEndArc), xEndArc(rhs.xEndArc), yStartArc(rhs.yStartArc), xStartArc(rhs.xStartArc), bottomRect(rhs.bottomRect), rightRect(rhs.rightRect), topRect(rhs.topRect), leftRect(rhs.leftRect)
{
}

MetaArcRecord::~MetaArcRecord()
{
}

MetaArcRecord & MetaArcRecord::operator=(const MetaArcRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->yEndArc = rhs.yEndArc;
        this->xEndArc = rhs.xEndArc;
        this->yStartArc = rhs.yStartArc;
        this->xStartArc = rhs.xStartArc;
        this->bottomRect = rhs.bottomRect;
        this->rightRect = rhs.rightRect;
        this->topRect = rhs.topRect;
        this->leftRect = rhs.leftRect;
    }
    return *this;
}

QPoint MetaArcRecord::getEndArc() const
{
    return QPoint(this->xEndArc, this->yEndArc);
}

QPoint MetaArcRecord::getStartArc() const
{
    return QPoint(this->xStartArc, this->yStartArc);
}

QRect MetaArcRecord::getRect() const
{
    return QRect(QPoint(this->leftRect,this->topRect), QPoint(this->rightRect, this->bottomRect));
}
