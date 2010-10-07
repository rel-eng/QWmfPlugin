/* META_SETLAYOUT record definition.

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

#ifndef METASETLAYOUTRECORD_H
#define METASETLAYOUTRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum Layout : quint16
{
    //Слева направо
    LAYOUT_LTR = 0x0000,
    //Справа налево, режим отображения следует изменить на MM_ISOTROPIC
    LAYOUT_RTL = 0x0001,
    //Отключает отражение битмапов для команд META_BITBLT и META_STRETCHBLT в режиме справа налево
    LAYOUT_BITMAPORIENTATIONPRESERVED = 0x0008
};

class MetaSetlayoutRecord : public MetafileRecord
{
private:
    quint16 layout;
public:
    MetaSetlayoutRecord();
    MetaSetlayoutRecord(quint16 layout);
    MetaSetlayoutRecord(QIODevice &device);
    MetaSetlayoutRecord(const MetaSetlayoutRecord &rhs);
    virtual ~MetaSetlayoutRecord();
    MetaSetlayoutRecord &operator=(const MetaSetlayoutRecord &rhs);
    quint16 getLayout() const;
};

#endif // METASETLAYOUTRECORD_H
