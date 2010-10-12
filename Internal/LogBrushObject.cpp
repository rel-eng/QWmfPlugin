/* LogBrush object implementation.

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

#include "LogBrushObject.h"

#include "Utils/IOUtils.h"

LogBrushObject::LogBrushObject() : brushStyle(BS_NULL), color(qRgb(0, 0, 0)), brushHatch(HS_HORIZONTAL)
{
}

LogBrushObject::LogBrushObject(quint16 brushStyle, QRgb color, quint16 brushHatch) : brushStyle(brushStyle), color(color), brushHatch(brushHatch)
{
}

LogBrushObject::LogBrushObject(QIODevice &device)
{
    this->brushStyle = readUnsignedWord(device);
    this->color = readRGBDword(device);
    this->brushHatch = readUnsignedWord(device);
}

LogBrushObject::LogBrushObject(const LogBrushObject &rhs) : brushStyle(rhs.brushStyle), color(rhs.color), brushHatch(rhs.brushHatch)
{
}

LogBrushObject::~LogBrushObject()
{
}

LogBrushObject & LogBrushObject::operator=(const LogBrushObject &rhs)
{
    if (this != &rhs)
    {
        this->brushStyle = rhs.brushStyle;
        this->color = rhs.color;
        this->brushHatch = rhs.brushHatch;
    }
    return *this;
}

quint16 LogBrushObject::getBrushStyle() const
{
    return this->brushStyle;
}

QRgb LogBrushObject::getColor() const
{
    return this->color;
}

quint16 LogBrushObject::getBrushHatch() const
{
    return this->brushHatch;
}
