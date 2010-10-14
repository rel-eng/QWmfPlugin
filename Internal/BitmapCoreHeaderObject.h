/* BitmapCoreHeader object definition.

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

#ifndef BITMAPCOREHEADEROBJECT_H
#define BITMAPCOREHEADEROBJECT_H

#include <QtGlobal>
#include <QIODevice>

enum BitCount : quint16
{
    //Неизвестно (используется формат PNG или JPEG)
    BI_BITCOUNT_0 = 0x0000,
    //1 бит на пиксел, 2 цвета
    BI_BITCOUNT_1 = 0x0001,
    //4 бита на пиксел, 16 цветов
    BI_BITCOUNT_2 = 0x0004,
    //8 бит на пиксел, 256 цветов
    BI_BITCOUNT_3 = 0x0008,
    //16 бит на пиксел, 2^16 цветов
    BI_BITCOUNT_4 = 0x0010,
    //24 бита на пиксел, 2^24 цветов
    BI_BITCOUNT_5 = 0x0018,
    //32 бита на пиксел, 2^24 цветов
    BI_BITCOUNT_6 = 0x0020
};

class BitmapCoreHeaderObject
{
private:
    //Размер заголовка в байтах, всегда равен 12
    quint32 headerSize;
    //Ширина в пикселах
    quint16 width;
    //Высота в пикселах
    quint16 height;
    //Количество цветовых плоскостей, всегда 0x0001
    quint16 planes;
    //Количество бит на пиксел
    quint16 bitCount;
public:
    BitmapCoreHeaderObject();
    BitmapCoreHeaderObject(quint16 width, quint16 height, quint16 bitCount);
    BitmapCoreHeaderObject(QIODevice &device);
    BitmapCoreHeaderObject(const BitmapCoreHeaderObject &rhs);
    virtual ~BitmapCoreHeaderObject();
    BitmapCoreHeaderObject &operator=(const BitmapCoreHeaderObject &rhs);
    quint16 getWidth() const;
    quint16 getHeight() const;
    quint16 getBitCount() const;
};

#endif // BITMAPCOREHEADEROBJECT_H
