/* META_ARC record definition.

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

#ifndef METAARCRECORD_H
#define METAARCRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaArcRecord : public MetafileRecord
{
private:
    qint16 yEndArc;
    qint16 xEndArc;
    qint16 yStartArc;
    qint16 xStartArc;
    qint16 bottomRect;
    qint16 rightRect;
    qint16 topRect;
    qint16 leftRect;
public:
    MetaArcRecord();
    MetaArcRecord(qint16 yEndArc, qint16 xEndArc, qint16 yStartArc, qint16 xStartArc, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect);
    MetaArcRecord(QIODevice &device);
    MetaArcRecord(const MetaArcRecord &rhs);
    virtual ~MetaArcRecord();
    MetaArcRecord &operator=(const MetaArcRecord &rhs);
    qint16 getYEndArc() const;
    qint16 getXEndArc() const;
    qint16 getYStartArc() const;
    qint16 getXStartArc() const;
    qint16 getBottomRect() const;
    qint16 getRightRect() const;
    qint16 getTopRect() const;
    qint16 getLeftRect() const;
};

#endif // METAARCRECORD_H
