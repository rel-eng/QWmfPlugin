/* META_OFFSETWINDOWORG record definition.

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

#ifndef METAOFFSETWINDOWORGRECORD_H
#define METAOFFSETWINDOWORGRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaOffsetwindoworgRecord : public MetafileRecord
{
private:
    qint16 yOffset;
    qint16 xOffset;
public:
    MetaOffsetwindoworgRecord();
    MetaOffsetwindoworgRecord(qint16 yOffset, qint16 xOffset);
    MetaOffsetwindoworgRecord(QIODevice &device);
    MetaOffsetwindoworgRecord(const MetaOffsetwindoworgRecord &rhs);
    virtual ~MetaOffsetwindoworgRecord();
    MetaOffsetwindoworgRecord &operator=(const MetaOffsetwindoworgRecord &rhs);
    qint16 getXOffset() const;
    qint16 getYOffset() const;
};

#endif // METAOFFSETWINDOWORGRECORD_H
