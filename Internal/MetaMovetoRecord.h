/* META_MOVETO record definition.

   Copyright (C) 2010 rel-eng

   This file is part of QWinHelp.

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

#ifndef METAMOVETORECORD_H
#define METAMOVETORECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QPoint>

#include "MetafileRecord.h"

class MetaMovetoRecord : public MetafileRecord
{
private:
    qint16 x;
    qint16 y;
 public:
    MetaMovetoRecord();
    MetaMovetoRecord(qint16 x, qint16 y);
    MetaMovetoRecord(QIODevice &device);
    MetaMovetoRecord(const MetaMovetoRecord &rhs);
    virtual ~MetaMovetoRecord();
    MetaMovetoRecord &operator=(const MetaMovetoRecord &rhs);
    QPoint getPoint() const;
};

#endif // METAMOVETORECORD_H
