/* GraphicsObjectFont implementation.

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

#include "GraphicsObjectFont.h"

#include <stdexcept>

GraphicsObjectFont::GraphicsObjectFont() : GraphicsObject(FONT_GRAPHICS_OBJECT), isValidFont(false), record()
{
}

GraphicsObjectFont::GraphicsObjectFont(const MetaCreatefontindirectRecord &record) : GraphicsObject(FONT_GRAPHICS_OBJECT), isValidFont(true), record(record)
{
}

GraphicsObjectFont::GraphicsObjectFont(const GraphicsObjectFont &rhs) : GraphicsObject(rhs), isValidFont(isValidFont), record(record)
{
}

GraphicsObjectFont::~GraphicsObjectFont()
{
}

GraphicsObjectFont & GraphicsObjectFont::operator=(const GraphicsObjectFont &rhs)
{
    if (this != &rhs)
    {
        GraphicsObject::operator =(rhs);
        this->isValidFont = rhs.isValidFont;
        this->record = rhs.record;
    }
    return *this;
}

bool GraphicsObjectFont::isValid() const
{
    return this->isValidFont;
}

QFont GraphicsObjectFont::getFont(qreal pointsInUnitVert) const
{
    if(!this->isValidFont)
    {
        throw std::runtime_error("Invalid font graphics object");
    }
    QFont font;
    FontObject obj = this->record.getFont();
    font.setPointSizeF(pointsInUnitVert * obj.getHeight());
    switch(obj.getWeight())
    {
    case 100:
        font.setWeight(0);
        break;
    case 200:
        font.setWeight(12);
        break;
    case 300:
        font.setWeight(25);
        break;
    case 400:
        font.setWeight(50);
        break;
    case 500:
        font.setWeight(56);
        break;
    case 600:
        font.setWeight(63);
        break;
    case 700:
        font.setWeight(75);
        break;
    case 800:
        font.setWeight(87);
        break;
    case 900:
        font.setWeight(99);
        break;
    default:
        font.setWeight(50);
    }
    if(obj.isItalic())
    {
        font.setItalic(true);
    }
    if(obj.isUnderline())
    {
        font.setUnderline(true);
    }
    if(obj.isStrikeOut())
    {
        font.setStrikeOut(true);
    }
    switch(obj.getFamily())
    {
    case FF_DONTCARE:
        font.setStyleHint(QFont::AnyStyle);
        break;
    case FF_ROMAN:
        font.setStyleHint(QFont::Serif);
        break;
    case FF_SWISS:
        font.setStyleHint(QFont::SansSerif);
        break;
    case FF_MODERN:
        font.setStyleHint(QFont::Monospace);
        break;
    case FF_SCRIPT:
        font.setStyleHint(QFont::Cursive);
        break;
    case FF_DECORATIVE:
        font.setStyleHint(QFont::Fantasy);
        break;
    default:
        font.setStyleHint(QFont::AnyStyle);
    }
    switch(obj.getPitch())
    {
    case DEFAULT_PITCH:
        font.setFixedPitch(false);
        break;
    case FIXED_PITCH:
        font.setFixedPitch(true);
        break;
    case VARIABLE_PITCH:
        font.setFixedPitch(false);
        break;
    default:
        font.setFixedPitch(false);
    }
    return font;
}

QTextCodec *GraphicsObjectFont::getTextCodec() const
{
    if(!this->isValidFont)
    {
        throw std::runtime_error("Invalid font graphics object");
    }
    FontObject obj = this->record.getFont();
    return obj.getTextCodec();
}

qreal GraphicsObjectFont::getOrientation() const
{
    if(!this->isValidFont)
    {
        throw std::runtime_error("Invalid font graphics object");
    }
    FontObject obj = this->record.getFont();
    return obj.getOrientation() * 10.0;
}

qreal GraphicsObjectFont::getEscapement() const
{
    if(!this->isValidFont)
    {
        throw std::runtime_error("Invalid font graphics object");
    }
    FontObject obj = this->record.getFont();
    return obj.getEscapement() * 10.0;
}
