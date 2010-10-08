/* META_SETSTRETCHBLTMODE record definition.

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

#ifndef METASETSTRETCHBLTMODERECORD_H
#define METASETSTRETCHBLTMODERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum StretchMode : quint16
{
    //Логическое и между уничтожаемыми и существующими значениями цвета пиксела
    BLACKONWHITE = 0x0001,
    //Логическое или между уничтожаемыми и существующими значениями цвета пиксела
    WHITEONBLACK = 0x0002,
    //Уничтожаемые строки пикселов просто удаляются
    COLORONCOLOR = 0x0003,
    //Отображает пикселы источника в блоки пикселов назначения
    HALFTONE = 0x0004
};

class MetaSetstretchbltmodeRecord : public MetafileRecord
{
private:
    quint16 stretchMode;
public:
    MetaSetstretchbltmodeRecord();
    MetaSetstretchbltmodeRecord(quint16 stretchMode);
    MetaSetstretchbltmodeRecord(QIODevice &device);
    MetaSetstretchbltmodeRecord(const MetaSetstretchbltmodeRecord &rhs);
    virtual ~MetaSetstretchbltmodeRecord();
    MetaSetstretchbltmodeRecord &operator=(const MetaSetstretchbltmodeRecord &rhs);
    quint16 getStretchMode() const;
};

#endif // METASETSTRETCHBLTMODERECORD_H
