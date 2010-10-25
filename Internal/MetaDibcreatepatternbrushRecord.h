/* META_DIBCREATEPATTERNBRUSH record definition.

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

#ifndef METADIBCREATEPATTERNBRUSHRECORD_H
#define METADIBCREATEPATTERNBRUSHRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QImage>

#include "MetafileRecord.h"
#include "LogBrushObject.h"
#include "DeviceIndependentBitmapObject.h"
#include "Bitmap16Object.h"
#include "PaletteObject.h"

class MetaDibcreatepatternbrushRecord : MetafileRecord
{
private:
    quint16 style;
    quint16 colorUsage;
    DeviceIndependentBitmapObject dib;
    Bitmap16Object bitmap;
    bool isDib;
public:
    MetaDibcreatepatternbrushRecord();
    MetaDibcreatepatternbrushRecord(quint16 style, quint16 colorUsage, const DeviceIndependentBitmapObject &dib);
    MetaDibcreatepatternbrushRecord(quint16 style, quint16 colorUsage, const Bitmap16Object &bitmap);
    MetaDibcreatepatternbrushRecord(QIODevice &device);
    MetaDibcreatepatternbrushRecord(const MetaDibcreatepatternbrushRecord &rhs);
    virtual ~MetaDibcreatepatternbrushRecord();
    MetaDibcreatepatternbrushRecord &operator=(const MetaDibcreatepatternbrushRecord &rhs);
    quint16 getStyle() const;
    quint16 getColorUsage() const;
    QImage getImage() const;
    QImage getImage(const PaletteObject &palette) const;
};

#endif // METADIBCREATEPATTERNBRUSHRECORD_H
