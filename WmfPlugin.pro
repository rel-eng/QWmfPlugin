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

TARGET  = wmf
TEMPLATE = lib
CONFIG = qt plugin
VERSION = 1.0.0

HEADERS = WmfHandler.h \
    WmfPlugin.h \
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
    Internal/MetaExttextoutRecord.h
SOURCES = WmfPlugin.cpp \
    WmfHandler.cpp \
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
    Internal/MetaExttextoutRecord.cpp
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CFLAGS_DEBUG += -std=c++0x
QMAKE_CFLAGS_RELEASE += -std=c++0x
