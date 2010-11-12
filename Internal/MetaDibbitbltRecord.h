/* META_DIBBITBLT record definition.

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

#ifndef METADIBBITBLTRECORD_H
#define METADIBBITBLTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"
#include "DeviceIndependentBitmapObject.h"
#include "TernaryRasterOperation.h"

class MetaDibbitbltRecord : public MetafileRecord
{
private:
    quint32 rasterOperation;
    qint16 ySrc;
    qint16 xSrc;
    qint16 height;
    qint16 width;
    qint16 yDest;
    qint16 xDest;
    DeviceIndependentBitmapObject target;
public:
    MetaDibbitbltRecord();
    MetaDibbitbltRecord(quint32 rasterOperation, qint16 ySrc, qint16 xSrc, qint16 height, qint16 width, qint16 yDest, qint16 xDest, const DeviceIndependentBitmapObject &target);
    MetaDibbitbltRecord(QIODevice &device);
    MetaDibbitbltRecord(const MetaDibbitbltRecord &rhs);
    virtual ~MetaDibbitbltRecord();
    MetaDibbitbltRecord &operator=(const MetaDibbitbltRecord &rhs);
    quint32 getRasterOperation() const;
    QRect getSrcRect() const;
    QRect getDestRect() const;
    DeviceIndependentBitmapObject getTarget() const;
};

#endif // METADIBBITBLTRECORD_H
