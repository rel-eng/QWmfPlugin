/* GraphicsObjectPen implementation.

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

#include "GraphicsObjectPen.h"

#include <stdexcept>

GraphicsObjectPen::GraphicsObjectPen() : GraphicsObject(PEN_GRAPHICS_OBJECT), isValidPen(false), record()
{
}

GraphicsObjectPen::GraphicsObjectPen(const MetaCreatepenindirectRecord &record) : GraphicsObject(PEN_GRAPHICS_OBJECT), isValidPen(true), record(record)
{
}

GraphicsObjectPen::GraphicsObjectPen(const GraphicsObjectPen &rhs) : GraphicsObject(rhs), isValidPen(rhs.isValidPen), record(rhs.record)
{
}

GraphicsObjectPen::~GraphicsObjectPen()
{
}

GraphicsObjectPen & GraphicsObjectPen::operator=(const GraphicsObjectPen &rhs)
{
    if (this != &rhs)
    {
        GraphicsObject::operator =(rhs);
        this->isValidPen = rhs.isValidPen;
        this->record = rhs.record;
    }
    return *this;
}

bool GraphicsObjectPen::isValid() const
{
    return this->isValidPen;
}

QPen GraphicsObjectPen::getPen(qreal pixelInUnitHor) const
{
    if(!this->isValidPen)
    {
        throw std::runtime_error("Invalid pen graphics object");
    }
    QPen result;
    result.setWidthF(pixelInUnitHor * static_cast<qreal>(this->record.getPen().getWidth()));
    result.setColor(QColor(this->record.getPen().getColor()));
    quint16 style = this->record.getPen().getPenStyle();
    if((style & 0x00FF) == PS_COSMETIC)
    {
        result.setCosmetic(true);
    }
    else
    {
        result.setCosmetic(false);
    }
    switch((style & 0x00FF))
    {
    case PS_SOLID:
        result.setStyle(Qt::SolidLine);
        break;
    case PS_DASH:
        result.setStyle(Qt::DashLine);
        break;
    case PS_DOT:
        result.setStyle(Qt::DotLine);
        break;
    case PS_DASHDOT:
        result.setStyle(Qt::DashDotLine);
        break;
    case PS_DASHDOTDOT:
        result.setStyle(Qt::DashDotDotLine);
        break;
    case PS_NULL:
        result.setStyle(Qt::NoPen);
        break;
    case PS_INSIDEFRAME:
        //Не используем
        result.setStyle(Qt::SolidLine);
        break;
    case PS_USERSTYLE:
        //Не используем
        result.setStyle(Qt::SolidLine);
        break;
    case PS_ALTERNATE:
        //Не используем
        result.setStyle(Qt::DotLine);
        break;
    default:
        result.setStyle(Qt::SolidLine);
    }
    switch((style & 0x0F00))
    {
    case PS_ENDCAP_ROUND:
        result.setCapStyle(Qt::RoundCap);
        break;
    case PS_ENDCAP_SQUARE:
        result.setCapStyle(Qt::SquareCap);
        break;
    case PS_ENDCAP_FLAT:
        result.setCapStyle(Qt::FlatCap);
        break;
    default:
        result.setCapStyle(Qt::RoundCap);
    }
    switch((style & 0xF000))
    {
    case PS_JOIN_ROUND:
        result.setJoinStyle(Qt::RoundJoin);
        break;
    case PS_JOIN_BEVEL:
        result.setJoinStyle(Qt::BevelJoin);
        break;
    case PS_JOIN_MITER:
        result.setJoinStyle(Qt::MiterJoin);
        break;
    default:
        result.setJoinStyle(Qt::RoundJoin);
    }
    return result;
}
