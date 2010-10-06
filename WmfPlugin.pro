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
    Internal/Bitmap16Object.h
SOURCES = WmfPlugin.cpp \
    WmfHandler.cpp \
    Utils/IOUtils.cpp \
    Internal/MetaPlaceableRecord.cpp \
    Internal/MetaHeaderRecord.cpp \
    Internal/MetafileRecord.cpp \
    Internal/MetaEofRecord.cpp \
    Internal/PaletteObject.cpp \
    Internal/Bitmap16Object.cpp
QMAKE_CXXFLAGS_DEBUG += -std=c++0x
QMAKE_CXXFLAGS_RELEASE += -std=c++0x
QMAKE_CFLAGS_DEBUG += -std=c++0x
QMAKE_CFLAGS_RELEASE += -std=c++0x
