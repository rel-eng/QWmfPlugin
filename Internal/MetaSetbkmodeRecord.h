/* META_SETBKMODE record definition.

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

#ifndef METASETBKMODERECORD_H
#define METASETBKMODERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum MixMode : quint16
{
    TRANSPARENT = 0x0001,
    OPAQUE = 0x0002
};

class MetaSetbkmodeRecord : public MetafileRecord
{
private:
    quint16 bkMode;
public:
    MetaSetbkmodeRecord();
    MetaSetbkmodeRecord(quint16 bkMode);
    MetaSetbkmodeRecord(QIODevice &device);
    MetaSetbkmodeRecord(const MetaSetbkmodeRecord &rhs);
    virtual ~MetaSetbkmodeRecord();
    MetaSetbkmodeRecord &operator=(const MetaSetbkmodeRecord &rhs);
    quint16 getBkMode() const;
};

#endif // METASETBKMODERECORD_H
