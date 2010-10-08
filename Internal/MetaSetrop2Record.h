/* META_SETROP2 record definition.

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

#ifndef METASETROP2RECORD_H
#define METASETROP2RECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum BinaryRasterOperation : quint16
{
    //Всегда ноль
    R2_BLACK = 0x0001,
    //Логическое или цвета пера и цвета экрана, а затем отрицание
    R2_NOTMERGEPEN = 0x0002,
    //Отрицание цвета пера, а затем логическое и с цветом экрана
    R2_MASKNOTPEN = 0x0003,
    //Отрицание цвета пера
    R2_NOTCOPYPEN = 0x0004,
    //Отрицание цвета экрана, а затем логическое и с цветом пера
    R2_MASKPENNOT = 0x0005,
    //Отрицание цвета экрана
    R2_NOT = 0x0006,
    //Исключающее или цвета экрана и цвета пера
    R2_XORPEN = 0x0007,
    //Логическое и цвета пера и цвета экрана, а затем отрицание
    R2_NOTMASKPEN = 0x0008,
    //Логическое и цвета пера и цвета экрана
    R2_MASKPEN = 0x0009,
    //Исключающее или цвета пера и цвета экрана, а затем отрицание
    R2_NOTXORPEN = 0x000A,
    //Цвет не меняется
    R2_NOP = 0x000B,
    //Отрицание цвета пера, а затем логическое или с цветом экрана
    R2_MERGENOTPEN = 0x000C,
    //Цвет пера
    R2_COPYPEN = 0x000D,
    //Отрицание цвета экрана, а затем логическое или с цветом пера
    R2_MERGEPENNOT = 0x000E,
    //Логическое или цвета пера и цвета экрана
    R2_MERGEPEN = 0x000F,
    //Всегда единица
    R2_WHITE = 0x0010
};

class MetaSetrop2Record : public MetafileRecord
{
private:
    quint16 drawMode;
public:
    MetaSetrop2Record();
    MetaSetrop2Record(quint16 drawMode);
    MetaSetrop2Record(QIODevice &device);
    MetaSetrop2Record(const MetaSetrop2Record &rhs);
    virtual ~MetaSetrop2Record();
    MetaSetrop2Record &operator=(const MetaSetrop2Record &rhs);
    quint16 getDrawMode() const;
};

#endif // METASETROP2RECORD_H
