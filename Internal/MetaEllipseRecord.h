/* META_ELLIPSE record definition.

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

#ifndef METAELLIPSERECORD_H
#define METAELLIPSERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaEllipseRecord : public MetafileRecord
{
private:
    qint16 bottomRect;
    qint16 rightRect;
    qint16 topRect;
    qint16 leftRect;
public:
    MetaEllipseRecord();
    MetaEllipseRecord(qint16 bottomRect, qint16 rightRect, qint16 topRect, qint16 leftRect);
    MetaEllipseRecord(QIODevice &device);
    MetaEllipseRecord(const MetaEllipseRecord &rhs);
    virtual ~MetaEllipseRecord();
    MetaEllipseRecord &operator=(const MetaEllipseRecord &rhs);
    qint16 getBottomRect() const;
    qint16 getRightRect() const;
    qint16 getTopRect() const;
    qint16 getLeftRect() const;
};

#endif // METAELLIPSERECORD_H
