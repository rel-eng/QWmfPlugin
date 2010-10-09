/* Rect object implementation.

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

#include "RectObject.h"

#include "Utils/IOUtils.h"

RectObject::RectObject() : left(0), top(0), right(0), bottom(0)
{
}

RectObject::RectObject(qint16 left, qint16 top, qint16 right, qint16 bottom) : left(left), top(top), right(right), bottom(bottom)
{
}

RectObject::RectObject(QIODevice &device)
{
    this->left = readSignedWord(device);
    this->top = readSignedWord(device);
    this->right = readSignedWord(device);
    this->bottom = readSignedWord(device);
}

RectObject::RectObject(const RectObject &rhs) : left(rhs.left), top(rhs.top), right(rhs.right), bottom(rhs.bottom)
{
}

RectObject::~RectObject()
{
}

RectObject & RectObject::operator=(const RectObject &rhs)
{
    if (this != &rhs)
    {
        this->left = rhs.left;
        this->top = rhs.top;
        this->right = rhs.right;
        this->bottom = rhs.bottom;
    }
    return *this;
}

QRect RectObject::getRect() const
{
    return QRect(QPoint(left, top), QPoint(right, bottom));
}
