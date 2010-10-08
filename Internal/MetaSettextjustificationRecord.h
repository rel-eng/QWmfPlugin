/* META_SETTEXTJUSTIFICATION record definition.

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

#ifndef METASETTEXTJUSTIFICATIONRECORD_H
#define METASETTEXTJUSTIFICATIONRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaSettextjustificationRecord : public MetafileRecord
{
private:
    //Количество пробелов в строке
    quint16 breakCount;
    //Общея длина добавленного к строке интервала в логических единицах
    quint16 breakExtra;
public:
    MetaSettextjustificationRecord();
    MetaSettextjustificationRecord(quint16 breakCount, quint16 breakExtra);
    MetaSettextjustificationRecord(QIODevice &device);
    MetaSettextjustificationRecord(const MetaSettextjustificationRecord &rhs);
    virtual ~MetaSettextjustificationRecord();
    MetaSettextjustificationRecord &operator=(const MetaSettextjustificationRecord &rhs);
    quint16 getBreakCount() const;
    quint16 getBreakExtra() const;
};

#endif // METASETTEXTJUSTIFICATIONRECORD_H
