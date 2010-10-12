/* META_POLYGON record implementation.

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

#include "MetaPolygonRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaPolygonRecord::MetaPolygonRecord() : MetafileRecord(4, META_POLYGON), numberOfPoints(0), points()
{
}

MetaPolygonRecord::MetaPolygonRecord(const QVector<QPoint> &points) : MetafileRecord(4 + 2 * points.count(), META_POLYGON), numberOfPoints(points.count()), points(points)
{
    if(points.count() > 0xFFFF)
    {
        throw std::runtime_error("Too much points in polygon");
    }
}

MetaPolygonRecord::MetaPolygonRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_POLYGON & 0x00FF))
    {
        throw std::runtime_error("Not a META_POLYGON record");
    }
    this->numberOfPoints = readUnsignedWord(device);
    if(numberOfPoints > 0)
    {
        this->points = QVector<QPoint>(this->numberOfPoints);
        for(quint16 i = 0; i < this->numberOfPoints; i++)
        {
            this->points[i] = readPointShort(device);
        }
    }
}

MetaPolygonRecord::MetaPolygonRecord(const MetaPolygonRecord &rhs) : MetafileRecord(rhs), numberOfPoints(rhs.numberOfPoints), points(rhs.points)
{
}

MetaPolygonRecord::~MetaPolygonRecord()
{
}

MetaPolygonRecord & MetaPolygonRecord::operator=(const MetaPolygonRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->numberOfPoints = rhs.numberOfPoints;
        this->points = rhs.points;
    }
    return *this;
}

QPolygon MetaPolygonRecord::getPoints() const
{
    return QPolygon(this->points);
}
