/* META_SETVIEWPORTEXT record definition.

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

#ifndef METASETVIEWPORTEXTRECORD_H
#define METASETVIEWPORTEXTRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaSetviewportextRecord : public MetafileRecord
{
private:
    //Ось ординат
    qint16 y;
    //Ось абсцисс
    qint16 x;
public:
    MetaSetviewportextRecord();
    MetaSetviewportextRecord(qint16 y, qint16 x);
    MetaSetviewportextRecord(QIODevice &device);
    MetaSetviewportextRecord(const MetaSetviewportextRecord &rhs);
    virtual ~MetaSetviewportextRecord();
    MetaSetviewportextRecord &operator=(const MetaSetviewportextRecord &rhs);
    qint16 getY() const;
    qint16 getX() const;
};

#endif // METASETVIEWPORTEXTRECORD_H
