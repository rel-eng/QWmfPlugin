/* META_STRETCHBLT record definition.

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

#ifndef METASTRETCHBLTRECORD_H
#define METASTRETCHBLTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"
#include "Bitmap16Object.h"
#include "TernaryRasterOperation.h"

class MetaStretchbltRecord : public MetafileRecord
{
private:
    quint32 rasterOperation;
    qint16 srcHeight;
    qint16 srcWidth;
    qint16 ySrc;
    qint16 xSrc;
    qint16 destHeight;
    qint16 destWidth;
    qint16 yDest;
    qint16 xDest;
    Bitmap16Object target;
public:
    MetaStretchbltRecord();
    MetaStretchbltRecord(quint32 rasterOperation, qint16 srcHeight, qint16 srcWidth, qint16 ySrc, qint16 xSrc, qint16 destHeight, qint16 destWidth, qint16 yDest, qint16 xDest, const Bitmap16Object &target);
    MetaStretchbltRecord(QIODevice &device);
    MetaStretchbltRecord(const MetaStretchbltRecord &rhs);
    virtual ~MetaStretchbltRecord();
    MetaStretchbltRecord &operator=(const MetaStretchbltRecord &rhs);
    quint32 getRasterOperation() const;
    QRect getSrcRect() const;
    QRect getDestRect() const;
    Bitmap16Object getTarget() const;
};

#endif // METASTRETCHBLTRECORD_H
