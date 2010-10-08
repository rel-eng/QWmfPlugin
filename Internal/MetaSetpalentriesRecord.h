/* META_SETPALENTRIES record definition.

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

#ifndef METASETPALENTRIESRECORD_H
#define METASETPALENTRIESRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"
#include "PaletteObject.h"

class MetaSetpalentriesRecord : public MetafileRecord
{
private:
    PaletteObject palette;
public:
    MetaSetpalentriesRecord();
    MetaSetpalentriesRecord(const PaletteObject &palette);
    MetaSetpalentriesRecord(QIODevice &device);
    MetaSetpalentriesRecord(const MetaSetpalentriesRecord &rhs);
    virtual ~MetaSetpalentriesRecord();
    MetaSetpalentriesRecord &operator=(const MetaSetpalentriesRecord &rhs);
    PaletteObject getPalette() const;
};

#endif // METASETPALENTRIESRECORD_H
