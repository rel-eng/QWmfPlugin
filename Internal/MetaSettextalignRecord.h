/* META_SETTEXTALIGN record definition.

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

#ifndef METASETTEXTALIGNRECORD_H
#define METASETTEXTALIGNRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum HorizontalTextAlignmentMode : quint16
{
    //Позиция рисования не обновляется после вывода текста, точка отсчета должна быть указана при выводе текста, точка отсчета в левом верхнем углу ограничивающего прямоугольника
    TA_NOUPDATECP_TOP_LEFT = 0x0000,
    //Позиция рисования обновляется после вывода текста и используется в качестве точки отсчета
    TA_UPDATECP = 0x0001,
    //Точка отсчета на правой грани ограничивающего прямоугольника
    TA_RIGHT = 0x0002,
    //Точка отсчета выравнена по горизонтали с центром ограничивающего прямоугольника
    TA_CENTER = 0x0006,
    //Точка отсчета на нижней грани ограничивающего прямоугольника
    TA_BOTTOM = 0x0008,
    //Точка отсчета на базовой линии текста
    TA_BASELINE = 0x0018,
    //Текст выводится справа налево
    TA_RTLREADING = 0x0100
};

enum VerticalTextAlignmentMode : quint16
{
    //Точка отсчета в правом верхнем углу ограничивающего прямоугольника
    VTA_TOP_RIGHT = 0x0000,
    //Точка отсчета на нижней грани ограничивающего прямоугольника
    VTA_BOTTOM = 0x0002,
    //Точка отсчета выравнена по горизонтали с центром ограничивающего прямоугольника
    VTA_CENTER = 0x0006,
    //Точка отсчета на левой грани ограничивающего прямоугольника
    VTA_LEFT = 0x0008,
    //Точка отсчета на базовой линии текста
    VTA_BASELINE = 0x0018
};

class MetaSettextalignRecord : public MetafileRecord
{
private:
    quint16 textAlignmentMode;
public:
    MetaSettextalignRecord();
    MetaSettextalignRecord(quint16 textAlignmentMode);
    MetaSettextalignRecord(QIODevice &device);
    MetaSettextalignRecord(const MetaSettextalignRecord &rhs);
    virtual ~MetaSettextalignRecord();
    MetaSettextalignRecord &operator=(const MetaSettextalignRecord &rhs);
    quint16 getTextAlignmentMode() const;
};

#endif // METASETTEXTALIGNRECORD_H
