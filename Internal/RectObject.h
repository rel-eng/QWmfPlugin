/* Rect object definition.

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

#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

class RectObject
{
private:
    qint16 left;
    qint16 top;
    qint16 right;
    qint16 bottom;
public:
    RectObject();
    RectObject(qint16 left, qint16 top, qint16 right, qint16 bottom);
    RectObject(QIODevice &device);
    RectObject(const RectObject &rhs);
    virtual ~RectObject();
    RectObject &operator=(const RectObject &rhs);
    QRect getRect() const;
};

#endif // RECTOBJECT_H
