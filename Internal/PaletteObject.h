/* Palette object definition.

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

#ifndef PALETTEOBJECT_H
#define PALETTEOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QScopedArrayPointer>
#include <QColor>
#include <QList>
#include <QPair>

enum PaletteEntryFlag : quint8
{
    //Запись используется для анимирования палитры
    //Не влияет на резултирующее изображение?
    PC_RESERVED = 0x01,
    //Младшее 16-битное слово записи является индексом аппаратной палитры
    //Откуда взять эту аппаратную палитру?
    PC_EXPLICIT = 0x02,
    //Цвет помещается в неиспользуемую запись системной палитры вместо установления соответсвия с уже имеющимся цветом в системной палитре
    //Не влияет на результирующее изображение?
    PC_NONCOLLAPSE = 0x04
};

class PaletteObject
{
private:
    //Смещение в палитре, если используется вместе с META_SETPALENTRIES и META_ANIMATEPALETTE, если же используется вместе с META_CREATEPALETTE, то всегда 0x0300
    quint16 start;
    //Количество записей в палитре
    quint16 numberOfEntries;
    //Color values of palette entries
    //Значения цвета записей палитры
    QScopedArrayPointer<QRgb> colorEntries;
    //Значения флагов записей палитры, ноль либо PaletteEntryFlag
    //Не влияют на результирующее изображение?
    QScopedArrayPointer<quint8> flagEntries;
public:
    PaletteObject();
    PaletteObject(quint16 start, QList<QPair<QRgb, quint8> > entries);
    PaletteObject(QIODevice &device);
    PaletteObject(const PaletteObject &rhs);
    virtual ~PaletteObject();
    PaletteObject &operator=(const PaletteObject &rhs);
    quint16 getPaletteStart() const;
    quint16 getPaletteEntriesCount() const;
    QRgb getPaletteEntryColor(quint16 index) const;
    quint8 getPaletteEntryFlag(quint16 index) const;
};

#endif // PALETTEOBJECT_H
