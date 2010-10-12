/* META_TEXTOUT record implementation.

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

#include "MetaTextoutRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaTextoutRecord::MetaTextoutRecord() : MetafileRecord(6, META_TEXTOUT), stringLength(0), textString(), yStart(0), xStart(0)
{
}

MetaTextoutRecord::MetaTextoutRecord(const QByteArray &textString, qint16 yStart, qint16 xStart) : MetafileRecord(6 + textString.length() + (((textString.length() % 2) != 0) ? 1 : 0), META_TEXTOUT), stringLength(textString.length()), textString(textString), yStart(yStart), xStart(xStart)
{
}

MetaTextoutRecord::MetaTextoutRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_TEXTOUT & 0x00FF))
    {
        throw std::runtime_error("Not a META_TEXTOUT record");
    }
    this->stringLength = readUnsignedWord(device);
    if(stringLength > 0)
    {
        this->textString = device.read(static_cast<qint64>(this->stringLength));
        if((this->stringLength % 2) != 0)
        {
            seekDevice(device, device.pos() + Q_INT64_C(1));
        }
        if(this->textString.length() != static_cast<int>(this->stringLength))
        {
            throw std::runtime_error("Unable to read text string");
        }
    }
    this->yStart = readSignedWord(device);
    this->xStart = readSignedWord(device);
}

MetaTextoutRecord::MetaTextoutRecord(const MetaTextoutRecord &rhs) : MetafileRecord(rhs), stringLength(rhs.stringLength), textString(rhs.textString), yStart(rhs.yStart), xStart(rhs.xStart)
{
}

MetaTextoutRecord::~MetaTextoutRecord()
{
}

MetaTextoutRecord & MetaTextoutRecord::operator=(const MetaTextoutRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->stringLength = rhs.stringLength;
        this->textString = rhs.textString;
        this->yStart = rhs.yStart;
        this->xStart = rhs.xStart;
    }
    return *this;
}

QString MetaTextoutRecord::getString(QTextCodec *codec) const
{
    if(codec == NULL)
    {
        throw std::runtime_error("Codec is NULL");
    }
    QScopedPointer<QTextDecoder> decoder(codec->makeDecoder());
    if (decoder.isNull())
    {
        throw std::runtime_error("Unable to create text decoder");
    }
    return decoder->toUnicode(this->textString);
}

QPoint MetaTextoutRecord::getStart() const
{
    return QPoint(this->xStart, this->yStart);
}
