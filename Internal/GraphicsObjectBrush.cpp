/* GraphicsObjectBrush implementation.

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

#include "GraphicsObjectBrush.h"

#include <stdexcept>

GraphicsObjectBrush::GraphicsObjectBrush() : GraphicsObject(BRUSH_GRAPHICS_OBJECT), brushType(EMPTY_BRUSH), indirectBrush(), patternBrush()
{
}

GraphicsObjectBrush::GraphicsObjectBrush(const MetaCreatebrushindirectRecord &record) : GraphicsObject(BRUSH_GRAPHICS_OBJECT), brushType(INDIRECT_BRUSH), indirectBrush(record), patternBrush()
{
}

GraphicsObjectBrush::GraphicsObjectBrush(const MetaCreatepatternbrushRecord &record) : GraphicsObject(BRUSH_GRAPHICS_OBJECT), brushType(PATTERN_BRUSH), indirectBrush(), patternBrush(record)
{
}

GraphicsObjectBrush::GraphicsObjectBrush(const GraphicsObjectBrush &rhs) : GraphicsObject(rhs), brushType(rhs.brushType), indirectBrush(rhs.indirectBrush), patternBrush(rhs.patternBrush)
{
}

GraphicsObjectBrush::~GraphicsObjectBrush()
{
}

GraphicsObjectBrush & GraphicsObjectBrush::operator=(const GraphicsObjectBrush &rhs)
{
    if (this != &rhs)
    {
        GraphicsObject::operator =(rhs);
        this->brushType = rhs.brushType;
        this->indirectBrush = rhs.indirectBrush;
        this->patternBrush = rhs.patternBrush;
    }
    return *this;
}

bool GraphicsObjectBrush::isPaletteRequired() const
{
    if(this->brushType == PATTERN_BRUSH)
    {
        return this->patternBrush.isPaletteRequired();
    }
    else
    {
        if(this->brushType == INDIRECT_BRUSH)
        {
            return false;
        }
        else
        {
            throw std::runtime_error("Brush is empty");
        }
    }
}

QBrush GraphicsObjectBrush::getBrush() const
{
    if(this->brushType == PATTERN_BRUSH)
    {
        if(this->patternBrush.isPaletteRequired())
        {
            throw std::runtime_error("Brush requires palette");
        }
        QBrush result(Qt::TexturePattern);
        result.setTextureImage(this->patternBrush.getPattern());
        return result;
    }
    else
    {
        if(this->brushType == INDIRECT_BRUSH)
        {
            switch(this->indirectBrush.getBrush().getBrushStyle())
            {
            case BS_SOLID:
                return QBrush(QColor(this->indirectBrush.getBrush().getColor()));
                break;
            case BS_NULL:
                return QBrush(Qt::NoBrush);
                break;
            case BS_HATCHED:
                switch(this->indirectBrush.getBrush().getBrushHatch())
                {
                case HS_HORIZONTAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::HorPattern);
                    break;
                case HS_VERTICAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::VerPattern);
                    break;
                case HS_FDIAGONAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::FDiagPattern);
                    break;
                case HS_BDIAGONAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::BDiagPattern);
                    break;
                case HS_CROSS:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::CrossPattern);
                    break;
                case HS_DIAGCROSS:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::DiagCrossPattern);
                    break;
                default:
                    throw std::runtime_error("Unknown brush hatch");
                }
                break;
            case BS_PATTERN:
                return QBrush(QColor(0,0,0));
                break;
            case BS_INDEXED:
                return QBrush(Qt::NoBrush);
                break;
            case BS_DIBPATTERN:
                return QBrush(QColor(0,0,0));
                break;
            case BS_DIBPATTERNPT:
                return QBrush(QColor(0,0,0));
                break;
            case BS_PATTERN8X8:
                return QBrush(Qt::NoBrush);
                break;
            case BS_DIBPATTERN8X8:
                return QBrush(Qt::NoBrush);
                break;
            case BS_MONOPATTERN:
                return QBrush(Qt::NoBrush);
                break;
            default:
                throw std::runtime_error("Unknown brush style");
            }
        }
        else
        {
            throw std::runtime_error("Brush is empty");
        }
    }
}

QBrush GraphicsObjectBrush::getBrush(const PaletteObject &palette) const
{
    if(this->brushType == PATTERN_BRUSH)
    {
        QBrush result(Qt::TexturePattern);
        if(this->patternBrush.isPaletteRequired())
        {
            throw std::runtime_error("Brush requires palette");
        }
        result.setTextureImage(this->patternBrush.getPattern(palette));
        return result;
    }
    else
    {
        if(this->brushType == INDIRECT_BRUSH)
        {
            switch(this->indirectBrush.getBrush().getBrushStyle())
            {
            case BS_SOLID:
                return QBrush(QColor(this->indirectBrush.getBrush().getColor()));
                break;
            case BS_NULL:
                return QBrush(Qt::NoBrush);
                break;
            case BS_HATCHED:
                switch(this->indirectBrush.getBrush().getBrushHatch())
                {
                case HS_HORIZONTAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::HorPattern);
                    break;
                case HS_VERTICAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::VerPattern);
                    break;
                case HS_FDIAGONAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::FDiagPattern);
                    break;
                case HS_BDIAGONAL:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::BDiagPattern);
                    break;
                case HS_CROSS:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::CrossPattern);
                    break;
                case HS_DIAGCROSS:
                    return QBrush(QColor(this->indirectBrush.getBrush().getColor()), Qt::DiagCrossPattern);
                    break;
                default:
                    throw std::runtime_error("Unknown brush hatch");
                }
                break;
            case BS_PATTERN:
                return QBrush(QColor(0,0,0));
                break;
            case BS_INDEXED:
                return QBrush(Qt::NoBrush);
                break;
            case BS_DIBPATTERN:
                return QBrush(QColor(0,0,0));
                break;
            case BS_DIBPATTERNPT:
                return QBrush(QColor(0,0,0));
                break;
            case BS_PATTERN8X8:
                return QBrush(Qt::NoBrush);
                break;
            case BS_DIBPATTERN8X8:
                return QBrush(Qt::NoBrush);
                break;
            case BS_MONOPATTERN:
                return QBrush(Qt::NoBrush);
                break;
            default:
                throw std::runtime_error("Unknown brush style");
            }
        }
        else
        {
            throw std::runtime_error("Brush is empty");
        }
    }
}
