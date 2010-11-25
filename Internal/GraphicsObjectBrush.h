/* GraphicsObjectBrush definition.

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

#ifndef GRAPHICSOBJECTBRUSH_H
#define GRAPHICSOBJECTBRUSH_H

#include <QtGlobal>
#include <QBrush>

#include "GraphicsObject.h"
#include "MetaCreatebrushindirectRecord.h"
#include "MetaCreatepatternbrushRecord.h"
#include "MetaDibcreatepatternbrushRecord.h"
#include "PaletteObject.h"

class GraphicsObjectBrush : public GraphicsObject
{
private:
    enum BrushType
    {
        EMPTY_BRUSH,
        INDIRECT_BRUSH,
        PATTERN_BRUSH,
        DIB_PATTERN_BRUSH
    };
    BrushType brushType;
    MetaCreatebrushindirectRecord indirectBrush;
    MetaCreatepatternbrushRecord patternBrush;
    MetaDibcreatepatternbrushRecord dibPatternBrush;
public:
    GraphicsObjectBrush();
    GraphicsObjectBrush(const MetaCreatebrushindirectRecord &record);
    GraphicsObjectBrush(const MetaCreatepatternbrushRecord &record);
    GraphicsObjectBrush(const MetaDibcreatepatternbrushRecord &record);
    GraphicsObjectBrush(const GraphicsObjectBrush &rhs);
    virtual ~GraphicsObjectBrush();
    GraphicsObjectBrush &operator=(const GraphicsObjectBrush &rhs);
    bool isPaletteRequired() const;
    QBrush getBrush() const;
    QBrush getBrush(const PaletteObject &palette) const;
};

#endif // GRAPHICSOBJECTBRUSH_H
