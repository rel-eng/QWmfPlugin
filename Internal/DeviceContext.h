/* DeviceContext definition.

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

#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

#include <QtGlobal>

#include <cstddef>

#include "ObjectTable.h"
#include "MetaCreatebrushindirectRecord.h"
#include "MetaCreatepatternbrushRecord.h"
#include "MetaCreatefontindirectRecord.h"
#include "MetaCreatepenindirectRecord.h"
#include "MetaCreatepaletteRecord.h"

class DeviceContext
{
private:
    Q_DISABLE_COPY(DeviceContext)
    ObjectTable graphicsObjects;
public:
    DeviceContext(size_t numberOfObjects);
    virtual ~DeviceContext();
    void CreateBrushIndirect(const MetaCreatebrushindirectRecord &record);
    void CreatePatternBrush(const MetaCreatepatternbrushRecord &record);
    void CreateFontIndirect(const MetaCreatefontindirectRecord &record);
    void CreatePenIndirect(const MetaCreatepenindirectRecord &record);
    void CreatePalette(const MetaCreatepaletteRecord &record);
};

#endif // DEVICECONTEXT_H
