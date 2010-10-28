/* META_BITBLT record definition.

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

#ifndef METABITBLTRECORD_H
#define METABITBLTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"
#include "Bitmap16Object.h"
#include "TernaryRasterOperation.h"

class MetaBitbltRecord : public MetafileRecord
{
private:
    quint32 rasterOperation;
    qint16 ySrc;
    qint16 xSrc;
    qint16 height;
    qint16 width;
    qint16 yDest;
    qint16 xDest;
    Bitmap16Object target;
public:
    MetaBitbltRecord();
    MetaBitbltRecord(quint32 rasterOperation, qint16 ySrc, qint16 xSrc, qint16 height, qint16 width, qint16 yDest, qint16 xDest, const Bitmap16Object &target);
    MetaBitbltRecord(QIODevice &device);
    MetaBitbltRecord(const MetaBitbltRecord &rhs);
    virtual ~MetaBitbltRecord();
    MetaBitbltRecord &operator=(const MetaBitbltRecord &rhs);
    quint32 getRasterOperation() const;
    QRect getSrcRect() const;
    QRect getDestRect() const;
    Bitmap16Object getTarget() const;
};

#endif // METABITBLTRECORD_H
