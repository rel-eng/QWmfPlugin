/* META_ANIMATEPALETTE record definition.

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

#ifndef METAANIMATEPALETTERECORD_H
#define METAANIMATEPALETTERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"
#include "PaletteObject.h"

class MetaAnimatepaletteRecord : public MetafileRecord
{
private:
    PaletteObject palette;
public:
    MetaAnimatepaletteRecord();
    MetaAnimatepaletteRecord(const PaletteObject &palette);
    MetaAnimatepaletteRecord(QIODevice &device);
    MetaAnimatepaletteRecord(const MetaAnimatepaletteRecord &rhs);
    virtual ~MetaAnimatepaletteRecord();
    MetaAnimatepaletteRecord &operator=(const MetaAnimatepaletteRecord &rhs);
    PaletteObject getPalette() const;
};

#endif // METAANIMATEPALETTERECORD_H
