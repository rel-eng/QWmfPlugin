/* GraphicsObject definition.

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

#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

enum GraphicsObjectType
{
    EMPTY_GRAPHICS_OBJECT,
    BRUSH_GRAPHICS_OBJECT,
    FONT_GRAPHICS_OBJECT,
    PALETTE_GRAPHICS_OBJECT,
    PEN_GRAPHICS_OBJECT,
    REGION_GRAPHICS_OBJECT
};

class GraphicsObject
{
private:
    GraphicsObjectType type;
protected:
    GraphicsObject();
    GraphicsObject(GraphicsObjectType type);
    GraphicsObject(const GraphicsObject &rhs);
    GraphicsObject &operator=(const GraphicsObject &rhs);
public:
    virtual ~GraphicsObject();
    GraphicsObjectType getType() const;
};

#endif // GRAPHICSOBJECT_H
