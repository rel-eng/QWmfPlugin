# QWmfPlugin project file.
#
# Copyright (C) 2010 rel-eng
#
# This file is part of QWmfPlugin.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

TARGET  = qwmf
TEMPLATE = lib
CONFIG = qt plugin
VERSION = 1.0.0

HEADERS = \
    Utils/IOUtils.h \
    Internal/MetaPlaceableRecord.h \
    Internal/MetaHeaderRecord.h \
    Internal/MetafileRecord.h \
    Internal/MetaEofRecord.h \
    Internal/PaletteObject.h \
    Internal/Bitmap16Object.h \
    Internal/ConcurrentRecordLoader.h \
    Internal/MetaAnimatepaletteRecord.h \
    Internal/MetaExcludecliprectRecord.h \
    Internal/MetaIntersectcliprectRecord.h \
    Internal/MetaMovetoRecord.h \
    Internal/MetaOffsetcliprgnRecord.h \
    Internal/MetaOffsetviewportorgRecord.h \
    Internal/MetaOffsetwindoworgRecord.h \
    Internal/MetaRealizepaletteRecord.h \
    Internal/MetaResizepaletteRecord.h \
    Internal/MetaRestoredcRecord.h \
    Internal/MetaSavedcRecord.h \
    Internal/MetaScaleviewportextRecord.h \
    Internal/MetaScalewindowextRecord.h \
    Internal/MetaSetbkcolorRecord.h \
    Internal/MetaSetbkmodeRecord.h \
    Internal/MetaSetlayoutRecord.h \
    Internal/MetaSetmapmodeRecord.h \
    Internal/MetaSetmapperflagsRecord.h \
    Internal/MetaSetpalentriesRecord.h \
    Internal/MetaSetpolyfillmodeRecord.h \
    Internal/MetaSetrelabsRecord.h \
    Internal/MetaSetrop2Record.h \
    Internal/MetaSetstretchbltmodeRecord.h \
    Internal/MetaSettextalignRecord.h \
    Internal/MetaSettextcharextraRecord.h \
    Internal/MetaSettextcolorRecord.h \
    Internal/MetaSettextjustificationRecord.h \
    Internal/MetaSetviewportextRecord.h \
    Internal/MetaSetviewportorgRecord.h \
    Internal/MetaSetwindowextRecord.h \
    Internal/MetaSetwindoworgRecord.h \
    Internal/MetaEscapeRecord.h \
    Internal/MetaArcRecord.h \
    Internal/MetaChordRecord.h \
    Internal/MetaEllipseRecord.h \
    Internal/MetaExtfloodfillRecord.h \
    Internal/RectObject.h \
    Internal/MetaExttextoutRecord.h \
    Internal/MetaFillregionRecord.h \
    Internal/MetaFloodfillRecord.h \
    Internal/MetaFrameregionRecord.h \
    Internal/MetaInvertregionRecord.h \
    Internal/MetaLinetoRecord.h \
    Internal/MetaPaintregionRecord.h \
    Internal/TernaryRasterOperation.h \
    Internal/MetaPatbltRecord.h \
    Internal/MetaPieRecord.h \
    Internal/MetaPolylineRecord.h \
    Internal/MetaPolygonRecord.h \
    Internal/MetaPolypolygonRecord.h \
    Internal/MetaRectangleRecord.h \
    Internal/MetaRoundrectRecord.h \
    Internal/MetaSetpixelRecord.h \
    Internal/MetaTextoutRecord.h \
    Internal/LogBrushObject.h \
    Internal/MetaCreatebrushindirectRecord.h \
    Internal/FontObject.h \
    Internal/MetaCreatefontindirectRecord.h \
    Internal/MetaCreatepaletteRecord.h \
    Internal/MetaCreatepatternbrushRecord.h \
    Internal/PenObject.h \
    Internal/MetaCreatepenindirectRecord.h \
    Internal/ScanObject.h \
    Internal/RegionObject.h \
    Internal/MetaCreateregionRecord.h \
    Internal/MetaDeleteobjectRecord.h \
    Internal/BitmapCoreHeaderObject.h \
    Internal/BitmapInfoHeaderObject.h \
    Internal/DeviceIndependentBitmapObject.h \
    Internal/MetaDibcreatepatternbrushRecord.h \
    Internal/MetaSelectclipregionRecord.h \
    Internal/MetaSelectobjectRecord.h \
    Internal/MetaSelectpaletteRecord.h \
    Internal/MetaBitbltRecord.h \
    Internal/MetaDibbitbltRecord.h \
    Internal/MetaDibstretchbltRecord.h \
    Internal/MetaSetdibtodevRecord.h \
    Internal/MetaStretchbltRecord.h \
    Internal/MetaStretchdibRecord.h \
    QWmfPlugin.h \
    QWmfHandler.h \
    Utils/BinaryHeap.h \
    Internal/GraphicsObject.h \
    Internal/ObjectTable.h \
    Internal/MetafilePlayer.h \
    Internal/DeviceContext.h \
    Internal/GraphicsObjectBrush.h \
    Internal/GraphicsObjectFont.h \
    Internal/GraphicsObjectPen.h \
    Internal/GraphicsObjectPalette.h \
    Internal/GraphicsObjectRegion.h
SOURCES = \
    Utils/IOUtils.cpp \
    Internal/MetaPlaceableRecord.cpp \
    Internal/MetaHeaderRecord.cpp \
    Internal/MetafileRecord.cpp \
    Internal/MetaEofRecord.cpp \
    Internal/PaletteObject.cpp \
    Internal/Bitmap16Object.cpp \
    Internal/ConcurrentRecordLoader.cpp \
    Internal/MetaAnimatepaletteRecord.cpp \
    Internal/MetaExcludecliprectRecord.cpp \
    Internal/MetaIntersectcliprectRecord.cpp \
    Internal/MetaMovetoRecord.cpp \
    Internal/MetaOffsetcliprgnRecord.cpp \
    Internal/MetaOffsetviewportorgRecord.cpp \
    Internal/MetaOffsetwindoworgRecord.cpp \
    Internal/MetaRealizepaletteRecord.cpp \
    Internal/MetaResizepaletteRecord.cpp \
    Internal/MetaRestoredcRecord.cpp \
    Internal/MetaSavedcRecord.cpp \
    Internal/MetaScaleviewportextRecord.cpp \
    Internal/MetaScalewindowextRecord.cpp \
    Internal/MetaSetbkcolorRecord.cpp \
    Internal/MetaSetbkmodeRecord.cpp \
    Internal/MetaSetlayoutRecord.cpp \
    Internal/MetaSetmapmodeRecord.cpp \
    Internal/MetaSetmapperflagsRecord.cpp \
    Internal/MetaSetpalentriesRecord.cpp \
    Internal/MetaSetpolyfillmodeRecord.cpp \
    Internal/MetaSetrelabsRecord.cpp \
    Internal/MetaSetrop2Record.cpp \
    Internal/MetaSetstretchbltmodeRecord.cpp \
    Internal/MetaSettextalignRecord.cpp \
    Internal/MetaSettextcharextraRecord.cpp \
    Internal/MetaSettextcolorRecord.cpp \
    Internal/MetaSettextjustificationRecord.cpp \
    Internal/MetaSetviewportextRecord.cpp \
    Internal/MetaSetviewportorgRecord.cpp \
    Internal/MetaSetwindowextRecord.cpp \
    Internal/MetaSetwindoworgRecord.cpp \
    Internal/MetaEscapeRecord.cpp \
    Internal/MetaArcRecord.cpp \
    Internal/MetaChordRecord.cpp \
    Internal/MetaEllipseRecord.cpp \
    Internal/MetaExtfloodfillRecord.cpp \
    Internal/RectObject.cpp \
    Internal/MetaExttextoutRecord.cpp \
    Internal/MetaFillregionRecord.cpp \
    Internal/MetaFloodfillRecord.cpp \
    Internal/MetaFrameregionRecord.cpp \
    Internal/MetaInvertregionRecord.cpp \
    Internal/MetaLinetoRecord.cpp \
    Internal/MetaPaintregionRecord.cpp \
    Internal/MetaPatbltRecord.cpp \
    Internal/MetaPieRecord.cpp \
    Internal/MetaPolylineRecord.cpp \
    Internal/MetaPolygonRecord.cpp \
    Internal/MetaPolypolygonRecord.cpp \
    Internal/MetaRectangleRecord.cpp \
    Internal/MetaRoundrectRecord.cpp \
    Internal/MetaSetpixelRecord.cpp \
    Internal/MetaTextoutRecord.cpp \
    Internal/LogBrushObject.cpp \
    Internal/MetaCreatebrushindirectRecord.cpp \
    Internal/FontObject.cpp \
    Internal/MetaCreatefontindirectRecord.cpp \
    Internal/MetaCreatepaletteRecord.cpp \
    Internal/MetaCreatepatternbrushRecord.cpp \
    Internal/PenObject.cpp \
    Internal/MetaCreatepenindirectRecord.cpp \
    Internal/ScanObject.cpp \
    Internal/RegionObject.cpp \
    Internal/MetaCreateregionRecord.cpp \
    Internal/MetaDeleteobjectRecord.cpp \
    Internal/BitmapCoreHeaderObject.cpp \
    Internal/BitmapInfoHeaderObject.cpp \
    Internal/DeviceIndependentBitmapObject.cpp \
    Internal/MetaDibcreatepatternbrushRecord.cpp \
    Internal/MetaSelectclipregionRecord.cpp \
    Internal/MetaSelectobjectRecord.cpp \
    Internal/MetaSelectpaletteRecord.cpp \
    Internal/MetaBitbltRecord.cpp \
    Internal/MetaDibbitbltRecord.cpp \
    Internal/MetaDibstretchbltRecord.cpp \
    Internal/MetaSetdibtodevRecord.cpp \
    Internal/MetaStretchbltRecord.cpp \
    Internal/MetaStretchdibRecord.cpp \
    QWmfPlugin.cpp \
    QWmfHandler.cpp \
    Internal/GraphicsObject.cpp \
    Internal/ObjectTable.cpp \
    Internal/MetafilePlayer.cpp \
    Internal/DeviceContext.cpp \
    Internal/GraphicsObjectBrush.cpp \
    Internal/GraphicsObjectFont.cpp \
    Internal/GraphicsObjectPen.cpp \
    Internal/GraphicsObjectPalette.cpp \
    Internal/GraphicsObjectRegion.cpp
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CFLAGS_DEBUG += -std=c++0x
QMAKE_CFLAGS_RELEASE += -std=c++0x
