/* META_POLYGON record definition.

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

#ifndef METAPOLYGONRECORD_H
#define METAPOLYGONRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QVector>
#include <QPoint>
#include <QPolygon>

#include "MetafileRecord.h"

class MetaPolygonRecord : public MetafileRecord
{
private:
    quint16 numberOfPoints;
    QVector<QPoint> points;
public:
    MetaPolygonRecord();
    MetaPolygonRecord(const QVector<QPoint> &points);
    MetaPolygonRecord(QIODevice &device);
    MetaPolygonRecord(const MetaPolygonRecord &rhs);
    virtual ~MetaPolygonRecord();
    MetaPolygonRecord &operator=(const MetaPolygonRecord &rhs);
    QPolygon getPoints() const;
};

#endif // METAPOLYGONRECORD_H
