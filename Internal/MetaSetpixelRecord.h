/* META_SETPIXEL record definition.

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

#ifndef METASETPIXELRECORD_H
#define METASETPIXELRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>
#include <QPoint>

#include "MetafileRecord.h"

class MetaSetpixelRecord : public MetafileRecord
{
private:
    QRgb color;
    qint16 y;
    qint16 x;
public:
    MetaSetpixelRecord();
    MetaSetpixelRecord(QRgb color, qint16 y, qint16 x);
    MetaSetpixelRecord(QIODevice &device);
    MetaSetpixelRecord(const MetaSetpixelRecord &rhs);
    virtual ~MetaSetpixelRecord();
    MetaSetpixelRecord &operator=(const MetaSetpixelRecord &rhs);
    QRgb getColor() const;
    QPoint getPoint() const;
};

#endif // METASETPIXELRECORD_H
