/* Pen object implementation.

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

#include "PenObject.h"

#include "Utils/IOUtils.h"

PenObject::PenObject() : penStyle(PS_SOLID), width(0), color(qRgb(0, 0, 0))
{
}

PenObject::PenObject(quint16 penStyle, qint16 width, QRgb color) : penStyle(penStyle), width(width), color(color)
{
}

PenObject::PenObject(QIODevice &device)
{
    this->penStyle = readUnsignedWord(device);
    this->width = readSignedWord(device);
    //Считываем неиспользуемое 16-битное слово
    readSignedWord(device);
    this->color = readRGBDword(device);
}

PenObject::PenObject(const PenObject &rhs) : penStyle(rhs.penStyle), width(rhs.width), color(rhs.color)
{
}

PenObject::~PenObject()
{
}

PenObject & PenObject::operator=(const PenObject &rhs)
{
    if (this != &rhs)
    {
        this->penStyle = rhs.penStyle;
        this->width = rhs.width;
        this->color = rhs.color;
    }
    return *this;
}

quint16 PenObject::getPenStyle() const
{
    return this->penStyle;
}

qint16 PenObject::getWidth() const
{
    return this->width;
}

QRgb PenObject::getColor() const
{
    return this->color;
}
