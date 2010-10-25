/* DeviceIndependentBitmap object definition.

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

#ifndef DEVICEINDEPENDENTBITMAPOBJECT_H
#define DEVICEINDEPENDENTBITMAPOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QColor>
#include <QImage>
#include <QScopedArrayPointer>
#include <QByteArray>
#include <QBuffer>

#include "BitmapCoreHeaderObject.h"
#include "BitmapInfoHeaderObject.h"
#include "PaletteObject.h"

enum ColorUsage : quint16
{
    //В таблице цветов записаны цвета RGB
    DIB_RGB_COLORS = 0x0000,
    //В таблице цветов записаны 16-битные индексы логической палитры
    DIB_PAL_COLORS = 0x0001,
    //Таблица цветов отсутствует
    DIB_PAL_INDICES = 0x0002
};

class DeviceIndependentBitmapObject
{
private:
    bool headersLoaded;
    bool isInfoHeader;
    BitmapCoreHeaderObject coreHeader;
    BitmapInfoHeaderObject infoHeader;
    QImage image;
    QScopedArrayPointer<quint8> imageBits;
    bool imageBitsValid;
    size_t imageBitsSize;
    quint16 colorUsage;
    quint32 size;
    void readUncompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, bool paletteQuad);
    void readRLE4CompressedBitmap(QIODevice &device, quint32 width, quint32 height, qint64 maxSize, quint32 paletteSize, bool paletteQuad, quint32 headerSize);
    void readRLE8CompressedBitmap(QIODevice &device, quint32 width, quint32 height, qint64 maxSize, quint32 paletteSize, bool paletteQuad, quint32 headerSize);
    void readBitfieldsCompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount);
    void loadWithRGBPalette(QIODevice &device, qint64 maxSize);
    QImage loadWithPalColors(const PaletteObject &palette) const;
    QImage loadWithPalIndices(const PaletteObject &palette) const;
    QImage readUncompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, const PaletteObject &palette) const;
    QImage readRLE4CompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const;
    QImage readRLE8CompressedBitmapPalColors(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const;
    QImage loadBitfieldsCompressedBitmap(QIODevice &device, quint32 width, quint32 height, quint16 bitCount) const;
    QImage readUncompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint16 bitCount, bool bottomUp, quint32 paletteSize, const PaletteObject &palette) const;
    QImage readRLE4CompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const;
    QImage readRLE8CompressedBitmapPalIndices(QIODevice &device, quint32 width, quint32 height, quint32 paletteSize, const PaletteObject &palette) const;
    quint32 calcShiftCount(quint32 mask) const;
public:
    DeviceIndependentBitmapObject();
    DeviceIndependentBitmapObject(QIODevice &device, qint64 maxSize);
    DeviceIndependentBitmapObject(QIODevice &device, quint16 colorUsage, qint64 maxSize);
    DeviceIndependentBitmapObject(const QImage &image);
    DeviceIndependentBitmapObject(const DeviceIndependentBitmapObject &rhs);
    virtual ~DeviceIndependentBitmapObject();
    DeviceIndependentBitmapObject &operator=(const DeviceIndependentBitmapObject &rhs);
    QImage getImage() const;
    QImage getImage(const PaletteObject &palette) const;
    quint32 getSizeInWords() const;
};

#endif // DEVICEINDEPENDENTBITMAPOBJECT_H
