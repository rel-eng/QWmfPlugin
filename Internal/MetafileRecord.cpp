/* Metafile record implementation.

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

#include "MetafileRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetafileRecord::MetafileRecord() : recordSizeInWords(3), recordFunction(META_EOF)
{
}

MetafileRecord::MetafileRecord(quint32 recordSizeInWords, quint16 recordFunction) : recordSizeInWords(recordSizeInWords), recordFunction(recordFunction)
{
}

MetafileRecord::MetafileRecord(QIODevice &device)
{
    this->recordSizeInWords = readUnsignedDWord(device);
    this->recordFunction = readUnsignedWord(device);
    bool validRecordType = false;
    switch(this->recordFunction & 0x00FF)
    {
    case (META_EOF & 0x00FF):
        validRecordType = true;
        break;
    case (META_REALIZEPALETTE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETPALENTRIES & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETBKMODE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETMAPMODE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETROP2 & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETRELABS & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETPOLYFILLMODE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETSTRETCHBLTMODE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETTEXTCHAREXTRA & 0x00FF):
        validRecordType = true;
        break;
    case (META_RESTOREDC & 0x00FF):
        validRecordType = true;
        break;
    case (META_RESIZEPALETTE & 0x00FF):
        validRecordType = true;
        break;
    case (META_DIBCREATEPATTERNBRUSH & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETLAYOUT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETBKCOLOR & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETTEXTCOLOR & 0x00FF):
        validRecordType = true;
        break;
    case (META_OFFSETVIEWPORTORG & 0x00FF):
        validRecordType = true;
        break;
    case (META_LINETO & 0x00FF):
        validRecordType = true;
        break;
    case (META_MOVETO & 0x00FF):
        validRecordType = true;
        break;
    case (META_OFFSETCLIPRGN & 0x00FF):
        validRecordType = true;
        break;
    case (META_FILLREGION & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETMAPPERFLAGS & 0x00FF):
        validRecordType = true;
        break;
    case (META_SELECTPALETTE & 0x00FF):
        validRecordType = true;
        break;
    case (META_POLYGON & 0x00FF):
        validRecordType = true;
        break;
    case (META_POLYLINE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETTEXTJUSTIFICATION & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETWINDOWORG & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETWINDOWEXT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETVIEWPORTORG & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETVIEWPORTEXT & 0x00FF):
        validRecordType = true;
        break;
    case (META_OFFSETWINDOWORG & 0x00FF):
        validRecordType = true;
        break;
    case (META_SCALEWINDOWEXT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SCALEVIEWPORTEXT & 0x00FF):
        validRecordType = true;
        break;
    case (META_EXCLUDECLIPRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_INTERSECTCLIPRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_ELLIPSE & 0x00FF):
        validRecordType = true;
        break;
    case (META_FLOODFILL & 0x00FF):
        validRecordType = true;
        break;
    case (META_FRAMEREGION & 0x00FF):
        validRecordType = true;
        break;
    case (META_ANIMATEPALETTE & 0x00FF):
        validRecordType = true;
        break;
    case (META_TEXTOUT & 0x00FF):
        validRecordType = true;
        break;
    case (META_POLYPOLYGON & 0x00FF):
        validRecordType = true;
        break;
    case (META_EXTFLOODFILL & 0x00FF):
        validRecordType = true;
        break;
    case (META_RECTANGLE & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETPIXEL & 0x00FF):
        validRecordType = true;
        break;
    case (META_ROUNDRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_PATBLT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SAVEDC & 0x00FF):
        validRecordType = true;
        break;
    case (META_PIE & 0x00FF):
        validRecordType = true;
        break;
    case (META_STRETCHBLT & 0x00FF):
        validRecordType = true;
        break;
    case (META_ESCAPE & 0x00FF):
        validRecordType = true;
        break;
    case (META_INVERTREGION & 0x00FF):
        validRecordType = true;
        break;
    case (META_PAINTREGION & 0x00FF):
        validRecordType = true;
        break;
    case (META_SELECTCLIPREGION & 0x00FF):
        validRecordType = true;
        break;
    case (META_SELECTOBJECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETTEXTALIGN & 0x00FF):
        validRecordType = true;
        break;
    case (META_ARC & 0x00FF):
        validRecordType = true;
        break;
    case (META_CHORD & 0x00FF):
        validRecordType = true;
        break;
    case (META_BITBLT & 0x00FF):
        validRecordType = true;
        break;
    case (META_EXTTEXTOUT & 0x00FF):
        validRecordType = true;
        break;
    case (META_SETDIBTODEV & 0x00FF):
        validRecordType = true;
        break;
    case (META_DIBBITBLT & 0x00FF):
        validRecordType = true;
        break;
    case (META_DIBSTRETCHBLT & 0x00FF):
        validRecordType = true;
        break;
    case (META_STRETCHDIB & 0x00FF):
        validRecordType = true;
        break;
    case (META_DELETEOBJECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEPALETTE & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEPATTERNBRUSH & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEPENINDIRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEFONTINDIRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEBRUSHINDIRECT & 0x00FF):
        validRecordType = true;
        break;
    case (META_CREATEREGION & 0x00FF):
        validRecordType = true;
        break;
    default:
        validRecordType = false;
    };
    if(!validRecordType)
    {
        throw std::runtime_error("Invalid record function");
    }
}

MetafileRecord::MetafileRecord(const MetafileRecord &rhs) : recordSizeInWords(rhs.recordSizeInWords), recordFunction(rhs.recordFunction)
{
}

MetafileRecord::~MetafileRecord()
{
}

MetafileRecord & MetafileRecord::operator=(const MetafileRecord &rhs)
{
    if (this != &rhs)
    {
        this->recordSizeInWords = rhs.recordSizeInWords;
        this->recordFunction = rhs.recordFunction;
    }
    return *this;
}

quint32 MetafileRecord::getRecordSizeInWords() const
{
    return this->recordSizeInWords;
}

quint16 MetafileRecord::getRecordFunction() const
{
    return this->recordFunction;
}

void MetafileRecord::setRecordSizeInWords(quint32 size)
{
    this->recordSizeInWords = size;
}
