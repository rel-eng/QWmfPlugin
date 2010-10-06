/* META_PLACEABLE record definition.

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

#ifndef METAPLACEABLERECORD_H
#define METAPLACEABLERECORD_H

#include <QtGlobal>
#include <QIODevice>

class MetaPlaceableRecord
{
private:
    //Всегда 0x9AC6CDD7
    quint32 key;
    //Всегда 0
    quint16 HWmf;
    //Абсцисса левого верхнего угла изображения (в логических единицах измерения)
    quint16 left;
    //Ордината левого верхнего угла изображения (в логических единицах измерения)
    quint16 top;
    //Абсцисса правого нижнего угла изображения (в логических единицах измерения)
    quint16 right;
    //Ордината правого нижнего угла изображения (в логических единицах измерения)
    quint16 bottom;
    //Количество логических единиц измерения на дюйм
    quint16 tpi;
    //Всегда 0
    quint32 reserved;
    //Контрольная сумма предыдущих 10 16-битных целых чисел (XOR)
    quint16 checksum;
public:
    MetaPlaceableRecord();
    MetaPlaceableRecord(quint16 left, quint16 top, quint16 right, quint16 bottom, quint16 tpi);
    MetaPlaceableRecord(QIODevice &device);
    MetaPlaceableRecord(const MetaPlaceableRecord &rhs);
    virtual ~MetaPlaceableRecord();
    MetaPlaceableRecord &operator=(const MetaPlaceableRecord &rhs);
    quint16 getLeft() const;
    quint16 getTop() const;
    quint16 getRight() const;
    quint16 getBottom() const;
    quint16 getTpi() const;
};

#endif // METAPLACEABLERECORD_H
