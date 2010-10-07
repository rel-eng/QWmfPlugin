/* META_SCALEWINDOWEXT record definition.

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

#ifndef METASCALEWINDOWEXTRECORD_H
#define METASCALEWINDOWEXTRECORD_H

#include <QtPlugin>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaScalewindowextRecord : public MetafileRecord
{
private:
    //Знаменатель масштабного коэффициента для оси ординат
    qint16 yDenom;
    //Числитель масштабного коэффициента для оси ординат
    qint16 yNum;
    //Знаменатель масштабного коэффициента для оси абсцисс
    qint16 xDenom;
    //Числитель масштабного коэффициента для оси абсцисс
    qint16 xNum;
public:
    MetaScalewindowextRecord();
    MetaScalewindowextRecord(qint16 yDenom, qint16 yNum, qint16 xDenom, qint16 xNum);
    MetaScalewindowextRecord(QIODevice &device);
    MetaScalewindowextRecord(const MetaScalewindowextRecord &rhs);
    virtual ~MetaScalewindowextRecord();
    MetaScalewindowextRecord &operator=(const MetaScalewindowextRecord &rhs);
    qint16 getYDenom() const;
    qint16 getYNum() const;
    qint16 getXDenom() const;
    qint16 getXNum() const;
};

#endif // METASCALEWINDOWEXTRECORD_H
