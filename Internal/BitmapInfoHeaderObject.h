/* BitmapInfoHeader object definition.

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

#ifndef BITMAPINFOHEADEROBJECT_H
#define BITMAPINFOHEADEROBJECT_H

#include <QtGlobal>
#include <QIODevice>

#include "BitmapCoreHeaderObject.h"

enum Compression : quint32
{
    //Несжатый битмап, RGB
    BI_RGB = 0x00000000,
    //Сжатие RLE, RGB, 8 бит на пиксел
    BI_RLE8 = 0x00000001,
    //Сжатие RLE, RGB, 4 бита на пиксел
    BI_RLE4 = 0x00000002,
    //Несжатый битмап, RGB, используются маски цветовых компонентов, 16 или 32 бита на пиксел
    BI_BITFIELDS = 0x00000003,
    //Формат JPEG
    BI_JPEG = 0x00000004,
    //Формат PNG
    BI_PNG = 0x00000005,
    //Несжатый битмап, CMYK
    BI_CMYK = 0x0000000B,
    //Сжатие RLE, CMYK, 8 бит на пиксел
    BI_CMYKRLE8 = 0x0000000C,
    //Сжатие RLE, CMYK, 4 бита на пиксел
    BI_CMYKRLE4 = 0x0000000D
};

class BitmapInfoHeaderObject
{
private:
    //Размер заголовка в байтах, всегда 40
    quint32 headerSize;
    //Ширина битмапа в пикселах, должна быть положительной
    qint32 width;
    //Высота битмапа в пикселах, не должна равняться нулю
    //Положительная высота - строки следуют снизу вверх, начало координат в нижнем левом углу, поддерживается сжатие
    //Отрицательная высота - строки следуют сверху вниз, начало координат в верхнем левом углу, не поддерживается сжатие
    qint32 height;
    //Количество цветовых плоскостей, всегда 0x0001
    quint16 planes;
    //Количество бит на пиксел
    quint16 bitCount;
    //Тип сжатия
    quint32 compression;
    //Размер изображения в байтах
    //Для несжатых изображений - игнорируется
    quint32 imageSize;
    //Горизонтальное разрешение, пикселей на метр
    qint32 xPelsPerMeter;
    //Вертикальное разрешение, пикселей на метр
    qint32 yPelsPerMeter;
    //Количество используемых записей в таблице цветов
    //Если равно нулю, то используются все цвета
    //Для менее чем 16 бит на пиксел задает количество цветов изображения
    //Для 16 и более бит на пиксел задает оптимальный размер системной палитры
    quint32 colorsUsed;
    //Количество цветов, требуемых для отображения битмапа
    //Если равно нулю, то требуются все цвета
    quint32 colorsImportant;
public:
    BitmapInfoHeaderObject();
    BitmapInfoHeaderObject(qint32 width, qint32 height, quint16 bitCount, quint32 compression, quint32 imageSize, qint32 xPelsPerMeter, qint32 yPelsPerMeter, quint32 colorsUsed, quint32 colorsImportant);
    BitmapInfoHeaderObject(QIODevice &device);
    BitmapInfoHeaderObject(const BitmapInfoHeaderObject &rhs);
    virtual ~BitmapInfoHeaderObject();
    BitmapInfoHeaderObject &operator=(const BitmapInfoHeaderObject &rhs);
    qint32 getWidth() const;
    qint32 getHeight() const;
    quint16 getBitCount() const;
    quint32 getCompression() const;
    quint32 getImageSize() const;
    qint32 getXPelsPerMeter() const;
    qint32 getYPelsPerMeter() const;
    quint32 getColorsUsed() const;
    quint32 getColorsImportant() const;
};

#endif // BITMAPINFOHEADEROBJECT_H
