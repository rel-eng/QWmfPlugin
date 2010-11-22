/* MetafilePlayer implementation.

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

#include "MetafilePlayer.h"

#include <stdexcept>

#include "DeviceContext.h"
#include "MetaEofRecord.h"
#include "MetaExcludecliprectRecord.h"
#include "MetaIntersectcliprectRecord.h"
#include "MetaAnimatepaletteRecord.h"
#include "MetaMovetoRecord.h"
#include "MetaOffsetcliprgnRecord.h"
#include "MetaOffsetviewportorgRecord.h"
#include "MetaOffsetwindoworgRecord.h"
#include "MetaRealizepaletteRecord.h"
#include "MetaResizepaletteRecord.h"
#include "MetaRestoredcRecord.h"
#include "MetaSavedcRecord.h"
#include "MetaScaleviewportextRecord.h"
#include "MetaScalewindowextRecord.h"
#include "MetaSetbkcolorRecord.h"
#include "MetaSetbkmodeRecord.h"
#include "MetaSetlayoutRecord.h"
#include "MetaSetmapmodeRecord.h"
#include "MetaSetmapperflagsRecord.h"
#include "MetaSetpalentriesRecord.h"
#include "MetaSetpolyfillmodeRecord.h"
#include "MetaSetrelabsRecord.h"
#include "MetaSetrop2Record.h"
#include "MetaSetstretchbltmodeRecord.h"
#include "MetaSettextalignRecord.h"
#include "MetaSettextcharextraRecord.h"
#include "MetaSettextcolorRecord.h"
#include "MetaSettextjustificationRecord.h"
#include "MetaSetviewportextRecord.h"
#include "MetaSetviewportorgRecord.h"
#include "MetaSetwindowextRecord.h"
#include "MetaSetwindoworgRecord.h"
#include "MetaEscapeRecord.h"
#include "MetaArcRecord.h"
#include "MetaChordRecord.h"
#include "MetaEllipseRecord.h"
#include "MetaExtfloodfillRecord.h"
#include "MetaExttextoutRecord.h"
#include "MetaFillregionRecord.h"
#include "MetaFloodfillRecord.h"
#include "MetaFrameregionRecord.h"
#include "MetaInvertregionRecord.h"
#include "MetaLinetoRecord.h"
#include "MetaPaintregionRecord.h"
#include "MetaPatbltRecord.h"
#include "MetaPieRecord.h"
#include "MetaPolylineRecord.h"
#include "MetaPolygonRecord.h"
#include "MetaPolypolygonRecord.h"
#include "MetaRectangleRecord.h"
#include "MetaRoundrectRecord.h"
#include "MetaSetpixelRecord.h"
#include "MetaTextoutRecord.h"
#include "MetaCreatebrushindirectRecord.h"
#include "MetaCreatefontindirectRecord.h"
#include "MetaCreatepaletteRecord.h"
#include "MetaCreatepatternbrushRecord.h"
#include "MetaCreatepenindirectRecord.h"
#include "MetaCreateregionRecord.h"
#include "MetaDeleteobjectRecord.h"
#include "MetaDibcreatepatternbrushRecord.h"
#include "MetaSelectclipregionRecord.h"
#include "MetaSelectobjectRecord.h"
#include "MetaSelectpaletteRecord.h"
#include "MetaBitbltRecord.h"
#include "MetaDibbitbltRecord.h"
#include "MetaDibstretchbltRecord.h"
#include "MetaSetdibtodevRecord.h"
#include "MetaStretchbltRecord.h"
#include "MetaStretchdibRecord.h"

MetafilePlayer::MetafilePlayer()
{
}

MetafilePlayer::~MetafilePlayer()
{
}

void MetafilePlayer::playMetafile(const MetaPlaceableRecord &placeableRecord, const MetaHeaderRecord &headerRecord, const ConcurrentRecordLoader &recordLoader, QImage &outputImage)
{
    DeviceContext deviceContext(static_cast<size_t>(headerRecord.getNumberOfObjects()));
    for(int recordIndex = 0; recordIndex < recordLoader.getRecordsCount(); recordIndex++)
    {
        QSharedPointer<MetafileRecord> currentRecord = recordLoader.getRecord(recordIndex);
        switch(currentRecord->getRecordFunction() & 0x00FF)
        {
        case (META_EOF & 0x00FF):
            break;
        case (META_REALIZEPALETTE & 0x00FF):
            break;
        case (META_SETPALENTRIES & 0x00FF):
            break;
        case (META_SETBKMODE & 0x00FF):
            break;
        case (META_SETMAPMODE & 0x00FF):
            break;
        case (META_SETROP2 & 0x00FF):
            break;
        case (META_SETRELABS & 0x00FF):
            break;
        case (META_SETPOLYFILLMODE & 0x00FF):
            break;
        case (META_SETSTRETCHBLTMODE & 0x00FF):
            break;
        case (META_SETTEXTCHAREXTRA & 0x00FF):
            break;
        case (META_RESTOREDC & 0x00FF):
            break;
        case (META_RESIZEPALETTE & 0x00FF):
            break;
        case (META_DIBCREATEPATTERNBRUSH & 0x00FF):
            break;
        case (META_SETLAYOUT & 0x00FF):
            break;
        case (META_SETBKCOLOR & 0x00FF):
            break;
        case (META_SETTEXTCOLOR & 0x00FF):
            break;
        case (META_OFFSETVIEWPORTORG & 0x00FF):
            break;
        case (META_LINETO & 0x00FF):
            break;
        case (META_MOVETO & 0x00FF):
            break;
        case (META_OFFSETCLIPRGN & 0x00FF):
            break;
        case (META_FILLREGION & 0x00FF):
            break;
        case (META_SETMAPPERFLAGS & 0x00FF):
            break;
        case (META_SELECTPALETTE & 0x00FF):
            break;
        case (META_POLYGON & 0x00FF):
            break;
        case (META_POLYLINE & 0x00FF):
            break;
        case (META_SETTEXTJUSTIFICATION & 0x00FF):
            break;
        case (META_SETWINDOWORG & 0x00FF):
            break;
        case (META_SETWINDOWEXT & 0x00FF):
            break;
        case (META_SETVIEWPORTORG & 0x00FF):
            break;
        case (META_SETVIEWPORTEXT & 0x00FF):
            break;
        case (META_OFFSETWINDOWORG & 0x00FF):
            break;
        case (META_SCALEWINDOWEXT & 0x00FF):
            break;
        case (META_SCALEVIEWPORTEXT & 0x00FF):
            break;
        case (META_EXCLUDECLIPRECT & 0x00FF):
            break;
        case (META_INTERSECTCLIPRECT & 0x00FF):
            break;
        case (META_ELLIPSE & 0x00FF):
            break;
        case (META_FLOODFILL & 0x00FF):
            break;
        case (META_FRAMEREGION & 0x00FF):
            break;
        case (META_ANIMATEPALETTE & 0x00FF):
            break;
        case (META_TEXTOUT & 0x00FF):
            break;
        case (META_POLYPOLYGON & 0x00FF):
            break;
        case (META_EXTFLOODFILL & 0x00FF):
            break;
        case (META_RECTANGLE & 0x00FF):
            break;
        case (META_SETPIXEL & 0x00FF):
            break;
        case (META_ROUNDRECT & 0x00FF):
            break;
        case (META_PATBLT & 0x00FF):
            break;
        case (META_SAVEDC & 0x00FF):
            break;
        case (META_PIE & 0x00FF):
            break;
        case (META_STRETCHBLT & 0x00FF):
            break;
        case (META_ESCAPE & 0x00FF):
            break;
        case (META_INVERTREGION & 0x00FF):
            break;
        case (META_PAINTREGION & 0x00FF):
            break;
        case (META_SELECTCLIPREGION & 0x00FF):
            break;
        case (META_SELECTOBJECT & 0x00FF):
            break;
        case (META_SETTEXTALIGN & 0x00FF):
            break;
        case (META_ARC & 0x00FF):
            break;
        case (META_CHORD & 0x00FF):
            break;
        case (META_BITBLT & 0x00FF):
            break;
        case (META_EXTTEXTOUT & 0x00FF):
            break;
        case (META_SETDIBTODEV & 0x00FF):
            break;
        case (META_DIBBITBLT & 0x00FF):
            break;
        case (META_DIBSTRETCHBLT & 0x00FF):
            break;
        case (META_STRETCHDIB & 0x00FF):
            break;
        case (META_DELETEOBJECT & 0x00FF):
            break;
        case (META_CREATEPALETTE & 0x00FF):
            deviceContext.CreatePalette(currentRecord.dynamicCast<MetaCreatepaletteRecord>().operator *());
            break;
        case (META_CREATEPATTERNBRUSH & 0x00FF):
            deviceContext.CreatePatternBrush(currentRecord.dynamicCast<MetaCreatepatternbrushRecord>().operator *());
            break;
        case (META_CREATEPENINDIRECT & 0x00FF):
            deviceContext.CreatePenIndirect(currentRecord.dynamicCast<MetaCreatepenindirectRecord>().operator *());
            break;
        case (META_CREATEFONTINDIRECT & 0x00FF):
            deviceContext.CreateFontIndirect(currentRecord.dynamicCast<MetaCreatefontindirectRecord>().operator *());
            break;
        case (META_CREATEBRUSHINDIRECT & 0x00FF):
            deviceContext.CreateBrushIndirect(currentRecord.dynamicCast<MetaCreatebrushindirectRecord>().operator *());
            break;
        case (META_CREATEREGION & 0x00FF):
            deviceContext.CreateRegion(currentRecord.dynamicCast<MetaCreateregionRecord>().operator *());
            break;
        default:
            throw std::runtime_error("Unknown record function");
        }
    }
}
