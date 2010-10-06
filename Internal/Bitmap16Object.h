/* Bitmap16 object definition.

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

#ifndef BITMAP16OBJECT_H
#define BITMAP16OBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QScopedArrayPointer>
#include <QImage>

#include <cstddef>

#include "PaletteObject.h"

class Bitmap16Object
{
private:
    //Тип битмапа
    //Всегда ноль?
    //Можно игнорировать?
    quint16 type;
    //Ширина в пикселах
    //Беззнаковая?
    quint16 width;
    //Высота в строках
    //Беззнаковая?
    quint16 height;
    //Количество байт в строке
    //Всегда четная?
    quint16 widthBytes;
    //Количество цветовых плоскостей, всегда 0x01
    quint8 planes;
    //Количество бит на пиксел
    //Каковы возможные значения? Как минимум 1, 4, 8, 24.
    quint8 bitsPerPixel;
    //Битмап
    //Строки идут сверху вниз или снизу вверх?
    QScopedArrayPointer<quint8> imageBits;
    //Размер битмапа в байтах
    size_t imageBitsLength;
public:
    Bitmap16Object();
    Bitmap16Object(quint16 width, quint16 height, quint8 bitsPerPixel, QScopedArrayPointer<quint8> imageBits, size_t imageBitsLength);
    Bitmap16Object(QIODevice &device);
    Bitmap16Object(const Bitmap16Object &rhs);
    virtual ~Bitmap16Object();
    Bitmap16Object &operator=(const Bitmap16Object &rhs);
    quint16 getWidth() const;
    quint16 getHeight() const;
    quint8 getBitsPerPixel() const;
    QImage getImage();
    QImage getImage(const PaletteObject &palette);
};

#endif // BITMAP16OBJECT_H
