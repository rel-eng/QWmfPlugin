/* META_EXTTEXTOUT record definition.

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

#ifndef METAEXTTEXTOUTRECORD_H
#define METAEXTTEXTOUTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QString>
#include <QTextCodec>
#include <QScopedArrayPointer>
#include <QPoint>
#include <QRect>
#include <QList>

#include "MetafileRecord.h"
#include "RectObject.h"

enum ExtTextOutOptions : quint16
{
    //Прямоугольник заливается цветом фона
    ETO_OPAQUE = 0x0002,
    //При выводе текста должно выполняться отсечение в соответствии с заданным прямоугольником
    ETO_CLIPPED = 0x0004,
    //Задан массив, описывающий размещение символов в строке
    ETO_GLYPH_INDEX = 0x0010,
    //Текст справа налево
    ETO_RTLREADING = 0x0080,
    //Вывод чисел в соответствии с настройками локализации
    ETO_NUMERICS_LOCAL = 0x0400,
    //Вывод чисел с использованием арабских цифр
    ETO_NUMERICS_LATIN = 0x0800,
    //Задано не только только горизонтальное, но и вертикальное размещение символов в строке
    ETO_PDY = 0x2000
};

class MetaExttextoutRecord : public MetafileRecord
{
private:
    qint16 y;
    qint16 x;
    quint16 stringLength;
    quint16 fwOpts;
    RectObject rectangle;
    QByteArray textString;
    QScopedArrayPointer<qint16> dX;
    bool rectanglePresent;
    bool dXpresent;
public:
    MetaExttextoutRecord();
    MetaExttextoutRecord(qint16 x, qint16 y, quint16 fwOpts, RectObject rectangle, const QByteArray &textString, const QList<qint16> &dX, bool rectanglePresent, bool dXpresent);
    MetaExttextoutRecord(QIODevice &device);
    MetaExttextoutRecord(const MetaExttextoutRecord &rhs);
    virtual ~MetaExttextoutRecord();
    MetaExttextoutRecord &operator=(const MetaExttextoutRecord &rhs);
    QPoint getPoint() const;
    quint16 getFWOpts() const;
    bool isRectanglePresent() const;
    QRect getRect() const;
    QString getString(QTextCodec *codec) const;
    bool isDXPresent() const;
    qint16 getDX(int index) const;
};

#endif // METAEXTTEXTOUTRECORD_H
