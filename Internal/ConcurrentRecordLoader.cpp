/* Concurrent record loader implementation.

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

#include "ConcurrentRecordLoader.h"

#include <QBuffer>
#include <QtConcurrentMap>

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
#include "Utils/IOUtils.h"

#include <stdexcept>

QSharedPointer<MetafileRecord> parseRecord(const QByteArray &rawRecord)
{
    QBuffer recordBuffer;
    recordBuffer.setData(rawRecord);
    recordBuffer.open(QIODevice::ReadOnly);
    quint16 recordFunction = 0;
    try
    {
        MetafileRecord baseRecord(recordBuffer);
        recordFunction = baseRecord.getRecordFunction() & 0x00FF;
    }
    catch(...)
    {
        throw ConcurrentRecordLoaderException();
    }
    recordBuffer.seek(Q_INT64_C(0));
    bool validRecordType = false;
    try
    {
        switch(recordFunction)
        {
        case (META_EOF & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaEofRecord(recordBuffer)));
            break;
        case (META_REALIZEPALETTE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaRealizepaletteRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETPALENTRIES & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetpalentriesRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETBKMODE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetbkmodeRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETMAPMODE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetmapmodeRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETROP2 & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetrop2Record(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETRELABS & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetrelabsRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETPOLYFILLMODE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetpolyfillmodeRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETSTRETCHBLTMODE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetstretchbltmodeRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETTEXTCHAREXTRA & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSettextcharextraRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_RESTOREDC & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaRestoredcRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_RESIZEPALETTE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaResizepaletteRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_DIBCREATEPATTERNBRUSH & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaDibcreatepatternbrushRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETLAYOUT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetlayoutRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETBKCOLOR & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetbkcolorRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETTEXTCOLOR & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSettextcolorRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_OFFSETVIEWPORTORG & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaOffsetviewportorgRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_LINETO & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaLinetoRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_MOVETO & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaMovetoRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_OFFSETCLIPRGN & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaOffsetcliprgnRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_FILLREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaFillregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETMAPPERFLAGS & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetmapperflagsRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SELECTPALETTE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSelectpaletteRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_POLYGON & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPolygonRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_POLYLINE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPolylineRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETTEXTJUSTIFICATION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSettextjustificationRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETWINDOWORG & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetwindoworgRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETWINDOWEXT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetwindowextRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETVIEWPORTORG & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetviewportorgRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETVIEWPORTEXT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetviewportextRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_OFFSETWINDOWORG & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaOffsetwindoworgRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SCALEWINDOWEXT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaScalewindowextRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SCALEVIEWPORTEXT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaScaleviewportextRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_EXCLUDECLIPRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaExcludecliprectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_INTERSECTCLIPRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaIntersectcliprectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_ELLIPSE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaEllipseRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_FLOODFILL & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaFloodfillRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_FRAMEREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaFrameregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_ANIMATEPALETTE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaAnimatepaletteRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_TEXTOUT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaTextoutRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_POLYPOLYGON & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPolypolygonRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_EXTFLOODFILL & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaExtfloodfillRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_RECTANGLE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaRectangleRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETPIXEL & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetpixelRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_ROUNDRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaRoundrectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_PATBLT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPatbltRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SAVEDC & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSavedcRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_PIE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPieRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_STRETCHBLT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaStretchbltRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_ESCAPE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaEscapeRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_INVERTREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaInvertregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_PAINTREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaPaintregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SELECTCLIPREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSelectclipregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SELECTOBJECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSelectobjectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETTEXTALIGN & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSettextalignRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_ARC & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaArcRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CHORD & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaChordRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_BITBLT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaBitbltRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_EXTTEXTOUT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaExttextoutRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_SETDIBTODEV & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaSetdibtodevRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_DIBBITBLT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaDibbitbltRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_DIBSTRETCHBLT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaDibstretchbltRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_STRETCHDIB & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaStretchdibRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_DELETEOBJECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaDeleteobjectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEPALETTE & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreatepaletteRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEPATTERNBRUSH & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreatepatternbrushRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEPENINDIRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreatepenindirectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEFONTINDIRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreatefontindirectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEBRUSHINDIRECT & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreatebrushindirectRecord(recordBuffer)));
            validRecordType = true;
            break;
        case (META_CREATEREGION & 0x00FF):
            return QSharedPointer<MetafileRecord>(dynamic_cast<MetafileRecord *>(new MetaCreateregionRecord(recordBuffer)));
            validRecordType = true;
            break;
        default:
            validRecordType = false;
        };
    }
    catch(...)
    {
        throw ConcurrentRecordLoaderException();
    }
    if(!validRecordType)
    {
        throw ConcurrentRecordLoaderException();
    }
    recordBuffer.close();
    return QSharedPointer<MetafileRecord>(new MetaEofRecord());
}

ConcurrentRecordLoader::ConcurrentRecordLoader(QIODevice &device) : processedRecords()
{
    QList<QByteArray> rawRecords;
    bool eof = false;
    while(!eof)
    {
        QByteArray recordHeader = device.peek(4);
        if(recordHeader.size() != 4)
        {
            throw std::runtime_error("Unable to read metafile record header");
        }
        QBuffer recordHeaderBuffer(&recordHeader);
        recordHeaderBuffer.open(QIODevice::ReadOnly);
        MetafileRecord baseRecord(recordHeaderBuffer);
        recordHeaderBuffer.close();
        qint64 recordSize = static_cast<qint64>(baseRecord.getRecordSizeInWords()) * Q_INT64_C(2);
        QByteArray recordBytes = device.read(recordSize);
        if(static_cast<qint64>(recordBytes.size()) != recordSize)
        {
            throw std::runtime_error("Unable to read metafile record");
        }
        rawRecords.append(recordBytes);
        if(baseRecord.getRecordFunction() == META_EOF)
        {
            eof = true;
        }
    }
    try
    {
        this->processedRecords = QtConcurrent::blockingMapped(rawRecords, parseRecord);
    }
    catch(...)
    {
        throw std::runtime_error("Metafiles record processing failed");
    }
}

ConcurrentRecordLoader::~ConcurrentRecordLoader()
{
}

int ConcurrentRecordLoader::getRecordsCount() const
{
    return this->processedRecords.count();
}

QSharedPointer<MetafileRecord> ConcurrentRecordLoader::getRecord(int index) const
{
    if((index < 0) || (index >= this->processedRecords.count()))
    {
        throw std::runtime_error("Record index out of range");
    }
    return this->processedRecords.at(index);
}
