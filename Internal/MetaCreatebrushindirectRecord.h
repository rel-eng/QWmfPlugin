/* META_CREATEBRUSHINDIRECT record definition.

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

#ifndef METACREATEBRUSHINDIRECTRECORD_H
#define METACREATEBRUSHINDIRECTRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"
#include "LogBrushObject.h"

class MetaCreatebrushindirectRecord : public MetafileRecord
{
private:
    LogBrushObject brush;
public:
    MetaCreatebrushindirectRecord();
    MetaCreatebrushindirectRecord(const LogBrushObject &brush);
    MetaCreatebrushindirectRecord(QIODevice &device);
    MetaCreatebrushindirectRecord(const MetaCreatebrushindirectRecord &rhs);
    virtual ~MetaCreatebrushindirectRecord();
    MetaCreatebrushindirectRecord &operator=(const MetaCreatebrushindirectRecord &rhs);
    LogBrushObject getBrush() const;
};

#endif // METACREATEBRUSHINDIRECTRECORD_H
