/* META_SETMAPMODE record definition.

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

#ifndef METASETMAPMODERECORD_H
#define METASETMAPMODERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum MapMode : quint16
{
    //Одна логическая единица эквивалентна одному пикселу, ось абсцисс направлена вправо, ось ординат направлена вниз
    MM_TEXT = 0x0001,
    //Одна логическая единица эквивалентна 0.1 миллиметра, ось абсцисс направлена вправо, ось ординат направлена вверх
    MM_LOMETRIC = 0x0002,
    //Одна логическая единица эквивалентна 0.01 миллиметра, ось абсцисс направлена вправо, ось ординат направлена вверх
    MM_HIMETRIC = 0x0003,
    //Одна логическая единица эквивалентна 0.01 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    MM_LOENGLISH = 0x0004,
    //Одна логическая единица эквивалентна 0.001 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    MM_HIENGLISH = 0x0005,
    //Одна логическая единица эквивалентна 1/1440 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    MM_TWIPS = 0x0006,
    //Произвольные, но равные друг другу масштабные коэффициенты для осей абсцисс и ординат, задаются посредством команд META_SETWINDOWEXT и META_SETVIEWPORTEXT, необходимо обеспечивать равенство масштабных коэффициентов при любых преобразованиях
    MM_ISOTROPIC = 0x0007,
    //Произвольные масштабные коэффициенты для осей абсцисс и ординат
    MM_ANISOTROPIC = 0x0008
};

class MetaSetmapmodeRecord : public MetafileRecord
{
private:
    quint16 mapMode;
public:
    MetaSetmapmodeRecord();
    MetaSetmapmodeRecord(quint16 mapMode);
    MetaSetmapmodeRecord(QIODevice &device);
    MetaSetmapmodeRecord(const MetaSetmapmodeRecord &rhs);
    virtual ~MetaSetmapmodeRecord();
    MetaSetmapmodeRecord &operator=(const MetaSetmapmodeRecord &rhs);
    quint16 getMapMode() const;
};

#endif // METASETMAPMODERECORD_H
