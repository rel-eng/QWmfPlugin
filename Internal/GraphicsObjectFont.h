/* GraphicsObjectFont definition.

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

#ifndef GRAPHICSOBJECTFONT_H
#define GRAPHICSOBJECTFONT_H

#include <QtGlobal>
#include <QFont>
#include <QTextCodec>

#include "GraphicsObject.h"
#include "MetaCreatefontindirectRecord.h"

class GraphicsObjectFont : public GraphicsObject
{
private:
    bool isValidFont;
    MetaCreatefontindirectRecord record;
public:
    GraphicsObjectFont();
    GraphicsObjectFont(const MetaCreatefontindirectRecord &record);
    GraphicsObjectFont(const GraphicsObjectFont &rhs);
    virtual ~GraphicsObjectFont();
    GraphicsObjectFont &operator=(const GraphicsObjectFont &rhs);
    bool isValid() const;
    QFont getFont(qreal pointsInUnitVert) const;
    QTextCodec *getTextCodec() const;
    qreal getOrientation() const;
    qreal getEscapement() const;
};

#endif // GRAPHICSOBJECTFONT_H
