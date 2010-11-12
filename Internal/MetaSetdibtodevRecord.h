/* META_SETDIBTODEV record definition.

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

#ifndef METASETDIBTODEVRECORD_H
#define METASETDIBTODEVRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"
#include "DeviceIndependentBitmapObject.h"

class MetaSetdibtodevRecord : public MetafileRecord
{
private:
    quint16 colorUsage;
    quint16 scanCount;
    quint16 startScan;
    quint16 yDib;
    quint16 xDib;
    quint16 height;
    quint16 width;
    quint16 yDest;
    quint16 xDest;
    DeviceIndependentBitmapObject dib;
public:
    MetaSetdibtodevRecord();
    MetaSetdibtodevRecord(quint16 colorUsage, quint16 scanCount, quint16 startScan, quint16 yDib, quint16 xDib, quint16 height, quint16 width, quint16 yDest, quint16 xDest, const DeviceIndependentBitmapObject &dib);
    MetaSetdibtodevRecord(QIODevice &device);
    MetaSetdibtodevRecord(const MetaSetdibtodevRecord &rhs);
    virtual ~MetaSetdibtodevRecord();
    MetaSetdibtodevRecord &operator=(const MetaSetdibtodevRecord &rhs);
    quint16 getColorUsage() const;
    quint16 getScanCount() const;
    quint16 getStartScan() const;
    QRect getSrcRect() const;
    QRect getDestRect() const;
    DeviceIndependentBitmapObject getDIB() const;
};

#endif // METASETDIBTODEVRECORD_H
