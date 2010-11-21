/* GraphicsObjectPalette implementation.

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

#include "GraphicsObjectPalette.h"

#include <stdexcept>

GraphicsObjectPalette::GraphicsObjectPalette() : GraphicsObject(PALETTE_GRAPHICS_OBJECT), isValidPalette(false), record()
{
}

GraphicsObjectPalette::GraphicsObjectPalette(const MetaCreatepaletteRecord &record) : GraphicsObject(PALETTE_GRAPHICS_OBJECT), isValidPalette(true), record(record)
{
}

GraphicsObjectPalette::GraphicsObjectPalette(const GraphicsObjectPalette &rhs) : GraphicsObject(rhs), isValidPalette(rhs.isValidPalette), record(rhs.record)
{
}

GraphicsObjectPalette::~GraphicsObjectPalette()
{
}

GraphicsObjectPalette & GraphicsObjectPalette::operator=(const GraphicsObjectPalette &rhs)
{
    if (this != &rhs)
    {
        GraphicsObject::operator =(rhs);
        this->isValidPalette = rhs.isValidPalette;
        this->record = rhs.record;
    }
    return *this;
}

bool GraphicsObjectPalette::isValid() const
{
    return this->isValidPalette;
}

PaletteObject GraphicsObjectPalette::getPalette() const
{
    if(!this->isValidPalette)
    {
        throw std::runtime_error("Invalid palette graphics object");
    }
    return this->record.getPalette();
}
