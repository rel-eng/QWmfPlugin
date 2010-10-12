/* META_POLYPOLYGON record definition.

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

#ifndef METAPOLYPOLYGONRECORD_H
#define METAPOLYPOLYGONRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QVector>
#include <QPoint>
#include <QPolygon>

#include "MetafileRecord.h"

class MetaPolypolygonRecord : public MetafileRecord
{
private:
    QVector<QPolygon> polygons;
public:
    MetaPolypolygonRecord();
    MetaPolypolygonRecord(const QVector<QPolygon> &polygons);
    MetaPolypolygonRecord(QIODevice &device);
    MetaPolypolygonRecord(const MetaPolypolygonRecord &rhs);
    virtual ~MetaPolypolygonRecord();
    MetaPolypolygonRecord &operator=(const MetaPolypolygonRecord &rhs);
    int getPolygonCount() const;
    QPolygon getPolygon(int index) const;
};

#endif // METAPOLYPOLYGONRECORD_H
