/* META_POLYLINE record implementation.

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

#include "MetaPolylineRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaPolylineRecord::MetaPolylineRecord() : MetafileRecord(4, META_POLYLINE), numberOfPoints(0), points()
{
}

MetaPolylineRecord::MetaPolylineRecord(const QVector<QPoint> &points) : MetafileRecord(4 + 2 * points.count(), META_POLYLINE), numberOfPoints(points.count()), points(points)
{
    if(points.count() > 0xFFFF)
    {
        throw std::runtime_error("Too much points in polyline");
    }
}

MetaPolylineRecord::MetaPolylineRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_POLYLINE & 0x00FF))
    {
        throw std::runtime_error("Not a META_POLYLINE record");
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

MetaPolylineRecord::MetaPolylineRecord(const MetaPolylineRecord &rhs) : MetafileRecord(rhs), numberOfPoints(rhs.numberOfPoints), points(rhs.points)
{
}

MetaPolylineRecord::~MetaPolylineRecord()
{
}

MetaPolylineRecord & MetaPolylineRecord::operator=(const MetaPolylineRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->numberOfPoints = rhs.numberOfPoints;
        this->points = rhs.points;
    }
    return *this;
}

QPolygon MetaPolylineRecord::getPoints() const
{
    return QPolygon(this->points);
}
