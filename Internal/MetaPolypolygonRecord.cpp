/* META_POLYPOLYGON record implementation.

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

#include "MetaPolypolygonRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaPolypolygonRecord::MetaPolypolygonRecord() : MetafileRecord(4, META_POLYPOLYGON), polygons()
{
}

MetaPolypolygonRecord::MetaPolypolygonRecord(const QVector<QPolygon> &polygons) : MetafileRecord(4, META_POLYPOLYGON), polygons(polygons)
{
    quint32 sz = 4 + polygons.count();
    for(int i = 0; i < polygons.count(); i++)
    {
        sz += 2 * polygons.at(i).count();
    }
    this->setRecordSizeInWords(sz);
}

MetaPolypolygonRecord::MetaPolypolygonRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_POLYPOLYGON & 0x00FF))
    {
        throw std::runtime_error("Not a META_POLYPOLYGON record");
    }
    quint16 polygonsCount = readUnsignedWord(device);
    this->polygons = QVector<QPolygon>(polygonsCount);
    QVector<quint16> pointsCount(polygonsCount);
    for(quint16 i = 0; i < polygonsCount; i++)
    {
        pointsCount[i] = readUnsignedWord(device);
    }
    for(quint16 i = 0; i < polygonsCount; i++)
    {
        QVector<QPoint> poly(pointsCount.at(i));
        for(quint16 j = 0; j < pointsCount.at(i); j++)
        {
            poly[j] = readPointShort(device);
        }
        this->polygons[i] = QPolygon(poly);
    }
}

MetaPolypolygonRecord::MetaPolypolygonRecord(const MetaPolypolygonRecord &rhs) : MetafileRecord(rhs), polygons(rhs.polygons)
{
}

MetaPolypolygonRecord::~MetaPolypolygonRecord()
{
}

MetaPolypolygonRecord & MetaPolypolygonRecord::operator=(const MetaPolypolygonRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->polygons = rhs.polygons;
    }
    return *this;
}

int MetaPolypolygonRecord::getPolygonCount() const
{
    return this->polygons.count();
}

QPolygon MetaPolypolygonRecord::getPolygon(int index) const
{
    if((index < 0) || (index >= this->polygons.count()))
    {
        throw std::runtime_error("Invalid polygon index");
    }
    return this->polygons.at(index);
}
