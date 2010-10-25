/* META_DIBCREATEPATTERNBRUSH record implementation.

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

#include "MetaDibcreatepatternbrushRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaDibcreatepatternbrushRecord::MetaDibcreatepatternbrushRecord() : MetafileRecord(11, META_DIBCREATEPATTERNBRUSH), style(BS_NULL), colorUsage(DIB_RGB_COLORS), dib(), bitmap(), isDib(true)
{
}

MetaDibcreatepatternbrushRecord::MetaDibcreatepatternbrushRecord(quint16 style, quint16 colorUsage, const DeviceIndependentBitmapObject &dib) : MetafileRecord(5 + dib.getSizeInWords(), META_DIBCREATEPATTERNBRUSH), style(style), colorUsage(colorUsage), dib(dib), bitmap(), isDib(true)
{
}

MetaDibcreatepatternbrushRecord::MetaDibcreatepatternbrushRecord(quint16 style, quint16 colorUsage, const Bitmap16Object &bitmap) : MetafileRecord(5 + bitmap.getSizeInWords(), META_DIBCREATEPATTERNBRUSH), style(style), colorUsage(colorUsage), dib(), bitmap(bitmap), isDib(false)
{
}

MetaDibcreatepatternbrushRecord::MetaDibcreatepatternbrushRecord(QIODevice &device) : MetafileRecord(device), dib(), bitmap()
{
    this->style = readUnsignedWord(device);
    this->colorUsage = readUnsignedWord(device);
    if(this->style == BS_PATTERN)
    {
        this->bitmap = Bitmap16Object(device);
        this->isDib = false;
    }
    else
    {
        this->dib = DeviceIndependentBitmapObject(device, this->colorUsage, static_cast<qint64>(this->getRecordSizeInWords() - 5)*Q_INT64_C(2));
        this->isDib = true;
    }
}

MetaDibcreatepatternbrushRecord::MetaDibcreatepatternbrushRecord(const MetaDibcreatepatternbrushRecord &rhs) : MetafileRecord(rhs), style(rhs.style), colorUsage(rhs.colorUsage), dib(rhs.dib), bitmap(rhs.bitmap), isDib(rhs.isDib)
{
}

MetaDibcreatepatternbrushRecord::~MetaDibcreatepatternbrushRecord()
{
}

MetaDibcreatepatternbrushRecord & MetaDibcreatepatternbrushRecord::operator=(const MetaDibcreatepatternbrushRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->style = rhs.style;
        this->colorUsage = rhs.colorUsage;
        this->dib = rhs.dib;
        this->bitmap = rhs.bitmap;
        this->isDib = rhs.isDib;
    }
    return *this;
}

quint16 MetaDibcreatepatternbrushRecord::getStyle() const
{
    return this->style;
}

quint16 MetaDibcreatepatternbrushRecord::getColorUsage() const
{
    return this->colorUsage;
}

QImage MetaDibcreatepatternbrushRecord::getImage() const
{
    if(this->isDib)
    {
        return this->dib.getImage();
    }
    else
    {
        return this->bitmap.getImage();
    }
}

QImage MetaDibcreatepatternbrushRecord::getImage(const PaletteObject &palette) const
{
    if(this->isDib)
    {
        return this->dib.getImage(palette);
    }
    else
    {
        return this->bitmap.getImage(palette);
    }
}
