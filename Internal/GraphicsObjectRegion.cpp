/* GraphicsObjectRegion implementation.

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

#include "GraphicsObjectRegion.h"

#include <stdexcept>

GraphicsObjectRegion::GraphicsObjectRegion() : GraphicsObject(REGION_GRAPHICS_OBJECT), isValidRegion(false), record()
{
}

GraphicsObjectRegion::GraphicsObjectRegion(const MetaCreateregionRecord &record) : GraphicsObject(REGION_GRAPHICS_OBJECT), isValidRegion(true), record(record)
{
}

GraphicsObjectRegion::GraphicsObjectRegion(const GraphicsObjectRegion &rhs) : GraphicsObject(rhs), isValidRegion(rhs.isValidRegion), record(rhs.record)
{
}

GraphicsObjectRegion::~GraphicsObjectRegion()
{
}

GraphicsObjectRegion & GraphicsObjectRegion::operator=(const GraphicsObjectRegion &rhs)
{
    if (this != &rhs)
    {
        GraphicsObject::operator =(rhs);
        this->isValidRegion = rhs.isValidRegion;
        this->record = rhs.record;
    }
    return *this;
}

bool GraphicsObjectRegion::isValid() const
{
    return this->isValidRegion;
}

QRegion GraphicsObjectRegion::getRegion(qreal pixelInUnitHor, qreal pixelInUnitVert) const
{
    if(!this->isValidRegion)
    {
        throw std::runtime_error("Invalid region graphics object");
    }
    QRegion result;
    RegionObject region = this->record.getRegion();
    for(int i = 0; i < region.getScanCount(); i++)
    {
        ScanObject scan = region.getScan(i);
        qreal scanHeightInUnits = static_cast<qreal>(scan.getBottom() - scan.getTop())/static_cast<qreal>(scan.getScanCount());
        qreal scanTopInUnits = static_cast<qreal>(scan.getTop());
        for(int j = 0; j < scan.getScanCount(); j++)
        {
            qreal scanBottomInUnits = scanTopInUnits + scanHeightInUnits;
            qreal scanLeftInUnits = static_cast<qreal>(scan.getScan(j).first);
            qreal scanRightInUnits = static_cast<qreal>(scan.getScan(j).second);
            result += QRect(QPoint(qRound(scanLeftInUnits * pixelInUnitHor), qRound(scanTopInUnits * pixelInUnitVert)),QPoint(qRound(scanRightInUnits * pixelInUnitHor), qRound(scanBottomInUnits * pixelInUnitVert)));
            scanTopInUnits = scanBottomInUnits;
        }
    }
    return result;
}
