/* Font object implementation.

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

#include "FontObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

FontObject::FontObject() : height(0), width(0), escapement(0), orientation(0), weight(0), italic(false), underline(false), strikeOut(false), charset(ANSI_CHARSET), outPrecision(OUT_DEFAULT_PRECIS), clipPrecision(CLIP_DEFAULT_PRECIS), quality(DEFAULT_QUALITY), pitch(DEFAULT_PITCH), family(FF_DONTCARE), faceName(), sizeInWords(10)
{
}

FontObject::FontObject(qint16 height, qint16 width, qint16 escapement, qint16 orientation, qint16 weight, bool italic, bool underline, bool strikeOut, quint8 charset, quint8 outPrecision, quint8 clipPrecision, quint8 quality, quint8 pitch, quint8 family, const QString &faceName) : height(height), width(width), escapement(escapement), orientation(orientation), weight(weight), italic(italic), underline(underline), strikeOut(strikeOut), charset(charset), outPrecision(outPrecision), clipPrecision(clipPrecision), quality(quality), pitch(pitch), family(family), faceName(faceName), sizeInWords(9 + faceName.length() + 1 + ((((faceName.length() + 1) % 2) != 0) ? 1 : 0))
{
}

FontObject::FontObject(QIODevice &device)
{
    this->height = readSignedWord(device);
    this->weight = readSignedWord(device);
    this->escapement = readSignedWord(device);
    this->orientation = readSignedWord(device);
    this->weight = readSignedWord(device);
    this->italic = false;
    if(readUnsignedByte(device) != 0)
    {
        this->italic = true;
    }
    this->underline = false;
    if(readUnsignedByte(device) != 0)
    {
        this->underline = true;
    }
    this->strikeOut = false;
    if(readUnsignedByte(device) != 0)
    {
        this->strikeOut = true;
    }
    this->charset = readUnsignedByte(device);
    this->outPrecision = readUnsignedByte(device);
    this->clipPrecision = readUnsignedByte(device);
    this->quality = readUnsignedByte(device);
    quint8 pitchAndFamily = readUnsignedByte(device);
    this->family = pitchAndFamily & 0x0F;
    this->pitch = ((pitchAndFamily & 0x3F) >> 6) & 0x03;
    qint64 faceNameLength = 0;
    this->faceName = readNullTerminatedString(device, Q_INT64_C(32), QTextCodec::codecForName("CP1252"), faceNameLength);
    this->sizeInWords = 9 + faceNameLength/2 + faceNameLength%2 ;
}

FontObject::FontObject(const FontObject &rhs) : height(rhs.height), width(rhs.width), escapement(rhs.escapement), orientation(rhs.orientation), weight(rhs.weight), italic(rhs.italic), underline(rhs.underline), strikeOut(rhs.strikeOut), charset(rhs.charset), outPrecision(rhs.outPrecision), clipPrecision(rhs.clipPrecision), quality(rhs.quality), pitch(rhs.pitch), family(rhs.family), faceName(rhs.faceName), sizeInWords(rhs.sizeInWords)
{
}

FontObject::~FontObject()
{
}

FontObject & FontObject::operator=(const FontObject &rhs)
{
    if (this != &rhs)
    {
        this->height = rhs.height;
        this->width = rhs.width;
        this->escapement = rhs.escapement;
        this->orientation = rhs.orientation;
        this->weight = rhs.weight;
        this->italic = rhs.italic;
        this->underline = rhs.underline;
        this->strikeOut = rhs.strikeOut;
        this->charset = rhs.charset;
        this->outPrecision = rhs.outPrecision;
        this->clipPrecision = rhs.clipPrecision;
        this->quality = rhs.quality;
        this->pitch = rhs.pitch;
        this->family = rhs.family;
        this->faceName = rhs.faceName;
        this->sizeInWords = rhs.sizeInWords;
    }
    return *this;
}

qint16 FontObject::getHeight() const
{
    return this->height;
}

qint16 FontObject::getWidth() const
{
    return this->width;
}

qint16 FontObject::getEscapement() const
{
    return this->escapement;
}

qint16 FontObject::getOrientation() const
{
    return this->orientation;
}

qint16 FontObject::getWeight() const
{
    return this->weight;
}

bool FontObject::isItalic() const
{
    return this->italic;
}

bool FontObject::isUnderline() const
{
    return this->underline;
}

bool FontObject::isStrikeOut() const
{
    return this->strikeOut;
}

QTextCodec *FontObject::getTextCodec() const
{
    QTextCodec *codec = NULL;
    switch (static_cast<FontCharset> (this->charset))
    {
    case FontCharset::ANSI_CHARSET:
        codec = QTextCodec::codecForName("CP1252");
        break;
    case FontCharset::DEFAULT_CHARSET:
        codec = QTextCodec::codecForName("CP1252");
        break;
    case FontCharset::SYMBOL_CHARSET:
        codec = QTextCodec::codecForName("CP1252");
        //Не поддерживается
        break;
    case FontCharset::MAC_CHARSET:
        codec = QTextCodec::codecForName("Apple Roman");
        break;
    case FontCharset::SHIFTJIS_CHARSET:
        codec = QTextCodec::codecForName("Shift-JIS");
        break;
    case FontCharset::HANGUL_CHARSET:
        codec = QTextCodec::codecForName("eucKR");
        break;
    case FontCharset::JOHAB_CHARSET:
        codec = QTextCodec::codecForName("CP1361");
        //На данный момент не поддерживается Qt
        break;
    case FontCharset::GB2312_CHARSET:
        codec = QTextCodec::codecForName("GB2312");
        break;
    case FontCharset::CHINESEBIG5_CHARSET:
        codec = QTextCodec::codecForName("Big5-HKSCS");
        break;
    case FontCharset::GREEK_CHARSET:
        codec = QTextCodec::codecForName("CP1253");
        break;
    case FontCharset::TURKISH_CHARSET:
        codec = QTextCodec::codecForName("CP1254");
        break;
    case FontCharset::VIETNAMESE_CHARSET:
        codec = QTextCodec::codecForName("CP1258");
        break;
    case FontCharset::HEBREW_CHARSET:
        codec = QTextCodec::codecForName("CP1255");
        break;
    case FontCharset::ARABIC_CHARSET:
        codec = QTextCodec::codecForName("CP1256");
        break;
    case FontCharset::BALTIC_CHARSET:
        codec = QTextCodec::codecForName("CP1257");
        break;
    case FontCharset::RUSSIAN_CHARSET:
        codec = QTextCodec::codecForName("CP1251");
        break;
    case FontCharset::THAI_CHARSET:
        codec = QTextCodec::codecForName("CP874");
        break;
    case FontCharset::EASTEUROPE_CHARSET:
        codec = QTextCodec::codecForName("CP1250");
        break;
    case FontCharset::OEM_CHARSET:
        codec = QTextCodec::codecForName("CP850");
        break;
    default:
        codec = QTextCodec::codecForName("CP1252");
    }
    if (codec == NULL)
    {
        codec = QTextCodec::codecForName("CP1252");
        if(codec == NULL)
        {
            throw std::runtime_error("Unable to create text codec");
        }
    }
    return codec;
}

quint8 FontObject::getOutPrecision() const
{
    return this->outPrecision;
}

quint8 FontObject::getClipPrecision() const
{
    return this->clipPrecision;
}

quint8 FontObject::getQuality() const
{
    return this->quality;
}

quint8 FontObject::getPitch() const
{
    return this->pitch;
}

quint8 FontObject::getFamily() const
{
    return this->family;
}

QString FontObject::getFaceName() const
{
    return this->faceName;
}

quint32 FontObject::getSizeInWords() const
{
    return this->sizeInWords;
}
