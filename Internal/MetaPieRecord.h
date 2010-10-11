/* META_PIE record definition.

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

#ifndef METAPIERECORD_H
#define METAPIERECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QPoint>
#include <QRect>

#include "MetafileRecord.h"

class MetaPieRecord : public MetafileRecord
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
    MetaPieRecord();
    MetaPieRecord(qint16 yRadial2, qint16 xRadial2, qint16 yRadial1, qint16 xRadial1, qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect);
    MetaPieRecord(QIODevice &device);
    MetaPieRecord(const MetaPieRecord &rhs);
    virtual ~MetaPieRecord();
    MetaPieRecord &operator=(const MetaPieRecord &rhs);
    QPoint getRadial2() const;
    QPoint getRadial1() const;
    QRect getRect() const;
};

#endif // METAPIERECORD_H
