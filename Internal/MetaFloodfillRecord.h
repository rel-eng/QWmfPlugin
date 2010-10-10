/* META_FLOODFILL record definition.

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

#ifndef METAFLOODFILLRECORD_H
#define METAFLOODFILLRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>
#include <QPoint>

#include "MetafileRecord.h"

class MetaFloodfillRecord : public MetafileRecord
{
private:
    QRgb color;
    qint16 yStart;
    qint16 xStart;
public:
    MetaFloodfillRecord();
    MetaFloodfillRecord(QRgb color, qint16 yStart, qint16 xStart);
    MetaFloodfillRecord(QIODevice &device);
    MetaFloodfillRecord(const MetaFloodfillRecord &rhs);
    virtual ~MetaFloodfillRecord();
    MetaFloodfillRecord &operator=(const MetaFloodfillRecord &rhs);
    QRgb getColor() const;
    QPoint getStart() const;
};

#endif // METAFLOODFILLRECORD_H
