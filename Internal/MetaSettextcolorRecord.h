/* META_SETTEXTCOLOR record definition.

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

#ifndef METASETTEXTCOLORRECORD_H
#define METASETTEXTCOLORRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>

#include "MetafileRecord.h"

class MetaSettextcolorRecord : public MetafileRecord
{
private:
    QRgb color;
public:
    MetaSettextcolorRecord();
    MetaSettextcolorRecord(QRgb color);
    MetaSettextcolorRecord(QIODevice &device);
    MetaSettextcolorRecord(const MetaSettextcolorRecord &rhs);
    virtual ~MetaSettextcolorRecord();
    MetaSettextcolorRecord &operator=(const MetaSettextcolorRecord &rhs);
    QRgb getColor() const;
};

#endif // METASETTEXTCOLORRECORD_H
