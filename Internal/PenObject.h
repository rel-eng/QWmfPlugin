/* Pen object definition.

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

#ifndef PENOBJECT_H
#define PENOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>

enum PenStyle
{
    //Ширина линии не зависит от преобразований координат
    PS_COSMETIC = 0x0000,
    //Закругленные концы
    PS_ENDCAP_ROUND = 0x0000,
    //Закругленные соединения
    PS_JOIN_ROUND = 0x0000,
    //Непрерывная линия
    PS_SOLID = 0x0000,
    //Штриховая линия
    PS_DASH = 0x0001,
    //Пунктирная линия
    PS_DOT = 0x0002,
    //Штрих-пунктирная линия
    PS_DASHDOT = 0x0003,
    //Линия "штрих и две точки"
    PS_DASHDOTDOT = 0x0004,
    //Невидимая линия
    PS_NULL = 0x0005,
    //При рисовании фигуры внутри ограничивающего прямоугольника учитывается ширина линии так чтобы фигура поместилась в ограничивающий прямоугольник
    PS_INSIDEFRAME = 0x0006,
    //Пользовательский стиль
    PS_USERSTYLE = 0x0007,
    //Рисуется только каждый второй пиксел (применимо только для косметического пера)
    PS_ALTERNATE = 0x0008,
    //Квадратный конец, закрывает конечную точку
    PS_ENDCAP_SQUARE = 0x0100,
    //Плоский конец, не завкрывает конечную точку
    PS_ENDCAP_FLAT = 0x0200,
    //Плоские соединения
    PS_JOIN_BEVEL = 0x1000,
    //Заостренные соединения, если размер такого соединения превышает заданный лимит, то рисуется плоское соединение
    PS_JOIN_MITER = 0x2000
};

class PenObject
{
private:
    quint16 penStyle;
    qint16 width;
    QRgb color;
public:
    PenObject();
    PenObject(quint16 penStyle, qint16 width, QRgb color);
    PenObject(QIODevice &device);
    PenObject(const PenObject &rhs);
    virtual ~PenObject();
    PenObject &operator=(const PenObject &rhs);
    quint16 getPenStyle() const;
    qint16 getWidth() const;
    QRgb getColor() const;
};

#endif // PENOBJECT_H
