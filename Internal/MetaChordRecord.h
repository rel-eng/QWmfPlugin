/* META_CHORD record definition.

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

#ifndef METACHORDRECORD_H
#define METACHORDRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaChordRecord : public MetafileRecord
{
private:
    qint16 yRadial2;
    qint16 xRadial2;
    qint16 yRadial1;
    qint16 xRadial1;
    qint16 bottomRect;
    qint16 rightRect;
    qint16 topRect;
    qint16 leftRect;
public:
    MetaChordRecord();
    MetaChordRecord(qint16 yRadial2, qint16 xRadial2, qint16 yRadial1, qint16 xRadial1, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect);
    MetaChordRecord(QIODevice &device);
    MetaChordRecord(const MetaChordRecord &rhs);
    virtual ~MetaChordRecord();
    MetaChordRecord &operator=(const MetaChordRecord &rhs);
    qint16 getYRadial2() const;
    qint16 getXRadial2() const;
    qint16 getYRadial1() const;
    qint16 getXRadial1() const;
    qint16 getBottomRect() const;
    qint16 getRightRect() const;
    qint16 getTopRect() const;
    qint16 getLeftRect() const;
};

#endif // METACHORDRECORD_H
