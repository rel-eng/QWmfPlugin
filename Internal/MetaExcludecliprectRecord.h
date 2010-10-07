/* META_EXCLUDECLIPRECT record definition.

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

#ifndef METAEXCLUDECLIPRECTRECORD_H
#define METAEXCLUDECLIPRECTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QRect>

#include "MetafileRecord.h"

class MetaExcludecliprectRecord : public MetafileRecord
{
private:
    qint16 bottom;
    qint16 right;
    qint16 top;
    qint16 left;
public:
    MetaExcludecliprectRecord();
    MetaExcludecliprectRecord(qint16 bottom, qint16 right, qint16 top, qint16 left);
    MetaExcludecliprectRecord(QIODevice &device);
    MetaExcludecliprectRecord(const MetaExcludecliprectRecord &rhs);
    virtual ~MetaExcludecliprectRecord();
    MetaExcludecliprectRecord &operator =(const MetaExcludecliprectRecord &rhs);
    QRect getRect() const;
};

#endif // METAEXCLUDECLIPRECTRECORD_H
