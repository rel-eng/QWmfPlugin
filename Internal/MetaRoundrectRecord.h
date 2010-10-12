/* META_ROUNDRECT record definition.

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

#ifndef METAROUNDRECTRECORD_H
#define METAROUNDRECTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"

class MetaRoundrectRecord : public MetafileRecord
{
private:
    qint16 height;
    qint16 width;
    qint16 bottomRect;
    qint16 rightRect;
    qint16 topRect;
    qint16 leftRect;
public:
    MetaRoundrectRecord();
    MetaRoundrectRecord(qint16 height, qint16 width, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect);
    MetaRoundrectRecord(QIODevice &device);
    MetaRoundrectRecord(const MetaRoundrectRecord &rhs);
    virtual ~MetaRoundrectRecord();
    MetaRoundrectRecord &operator=(const MetaRoundrectRecord &rhs);
    qint16 getHeight() const;
    qint16 getWidth() const;
    QRect getRect() const;
};

#endif // METAROUNDRECTRECORD_H
