/* LogBrush object definition.

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

#ifndef LOGBRUSHOBJECT_H
#define LOGBRUSHOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>

enum BrushStyle : quint16
{
    //Одноцветная сплошная кисть
    BS_SOLID = 0x0000,
    //Кисть отсутствует
    BS_NULL = 0x0001,
    //Штриховка
    BS_HATCHED = 0x0002,
    //Шаблон
    BS_PATTERN = 0x0003,
    //Не поддерживается
    BS_INDEXED = 0x0004,
    //Шаблон в виде независимого от устройства битмапа
    BS_DIBPATTERN = 0x0005,
    //Шаблон в виде независимого от устройства битмапа
    BS_DIBPATTERNPT = 0x0006,
    //Не поддерживается
    BS_PATTERN8X8 = 0x0007,
    //Не поддерживается
    BS_DIBPATTERN8X8 = 0x0008,
    //Не поддерживается
    BS_MONOPATTERN = 0x0009
};

enum HatchStyle : quint16
{
    //Горизонтальная штриховка
    HS_HORIZONTAL = 0x0000,
    //Вертикальная штриховка
    HS_VERTICAL = 0x0001,
    //Диагональная штриховка, сверху вниз, слева направо, по углом 45 градусов
    HS_FDIAGONAL = 0x0002,
    //Диагональная штриховка, снизу вверх, слева направо, по углом 45 градусов
    HS_BDIAGONAL = 0x0003,
    //Горизонтальная и вертикальная штриховки вместе
    HS_CROSS = 0x0004,
    //Диагональные штриховки, сверху вниз и снизу вверх, слева направо, по углом 45 градусов
    HS_DIAGCROSS = 0x0005
};

class LogBrushObject
{
private:
    quint16 brushStyle;
    QRgb color;
    quint16 brushHatch;
public:
    LogBrushObject();
    LogBrushObject(quint16 brushStyle, QRgb color, quint16 brushHatch);
    LogBrushObject(QIODevice &device);
    LogBrushObject(const LogBrushObject &rhs);
    virtual ~LogBrushObject();
    LogBrushObject &operator=(const LogBrushObject &rhs);
    quint16 getBrushStyle() const;
    QRgb getColor() const;
    quint16 getBrushHatch() const;
};

#endif // LOGBRUSHOBJECT_H
