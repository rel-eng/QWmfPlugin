/* META_EXTTEXTOUT record implementation.

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

#include "MetaExttextoutRecord.h"

#include "Utils/IOUtils.h"

#include <QScopedPointer>
#include <QTextDecoder>

#include <stdexcept>

MetaExttextoutRecord::MetaExttextoutRecord() : MetafileRecord(7, META_EXTTEXTOUT), x(0), y(0), stringLength(0), fwOpts(0), rectangle(), textString(), dX(), rectanglePresent(false), dXpresent(false)
{
}

MetaExttextoutRecord::MetaExttextoutRecord(qint16 x, qint16 y, quint16 fwOpts, RectObject rectangle, const QByteArray &textString, const QList<qint16> &dX, bool rectanglePresent, bool dXpresent) : MetafileRecord(7 + (rectanglePresent ? 4 : 0) + textString.length()/2 + (((textString.length() % 2) != 0) ? 1: 0) + (dXpresent ? dX.count() : 0), META_EXTTEXTOUT), x(x), y(y), stringLength(textString.length()), fwOpts(fwOpts), rectangle(rectangle), textString(textString), dX(), rectanglePresent(rectanglePresent), dXpresent(dXpresent)
{
    if(this->dXpresent)
    {
        if(dX.count() != textString.length())
        {
            throw std::runtime_error("Invalid DX size");
        }
        QScopedArrayPointer<qint16>(new qint16[static_cast<size_t>(dX.count())]).swap(this->dX);
        for(int i = 0; i < dX.count(); i++)
        {
            this->dX[i] = dX.at(i);
        }
    }
}

MetaExttextoutRecord::MetaExttextoutRecord(QIODevice &device) : MetafileRecord(device), textString(), dX()
{
    if((this->getRecordFunction() & 0x00FF) != (META_EXTTEXTOUT & 0x00FF))
    {
        throw std::runtime_error("Not a META_EXTTEXTOUT record");
    }
    this->y = readSignedWord(device);
    this->x = readSignedWord(device);
    this->stringLength = readUnsignedWord(device);
    this->fwOpts = readUnsignedWord(device);
    this->rectanglePresent = false;
    if(((this->fwOpts & ETO_OPAQUE) != 0) || ((this->fwOpts & ETO_CLIPPED) != 0))
    {
        this->rectangle = RectObject(device);
        this->rectanglePresent = true;
    }
    this->dXpresent = false;
    if(stringLength > 0)
    {
        this->textString = device.read(static_cast<qint64>(this->stringLength));
        if((this->stringLength % 2) != 0)
        {
            device.seek(device.pos() + Q_INT64_C(1));
        }
        if(this->textString.length() != static_cast<int>(this->stringLength))
        {
            throw std::runtime_error("Unable to read text string");
        }
        if(((this->fwOpts & ETO_GLYPH_INDEX) != 0) || ((this->fwOpts & ETO_PDY) != 0))
        {
            QScopedArrayPointer<qint16>(new qint16[this->stringLength]).swap(this->dX);
            fillBuffer(device, static_cast<qint64>(2 * this->stringLength), reinterpret_cast<void *>(this->dX.data()), sizeof(qint16) * static_cast<size_t>(this->stringLength));
            this->dXpresent = true;
        }
    }
}

MetaExttextoutRecord::MetaExttextoutRecord(const MetaExttextoutRecord &rhs) : MetafileRecord(rhs), x(rhs.x), y(rhs.y), stringLength(rhs.stringLength), fwOpts(rhs.fwOpts), rectangle(rhs.rectangle), textString(rhs.textString), dX(), rectanglePresent(rhs.rectanglePresent), dXpresent(rhs.dXpresent)
{
    if(!rhs.dX.isNull() && rhs.dXpresent && (rhs.stringLength > 0))
    {
        QScopedArrayPointer<qint16>(new qint16[static_cast<size_t>(rhs.stringLength)]).swap(this->dX);
        memcpy(reinterpret_cast<void *>(this->dX.data()), reinterpret_cast<const void *>(rhs.dX.data()), sizeof(quint16) * static_cast<size_t>(rhs.stringLength));
    }
}

MetaExttextoutRecord::~MetaExttextoutRecord()
{
}

MetaExttextoutRecord & MetaExttextoutRecord::operator=(const MetaExttextoutRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->y = rhs.y;
        this->x = rhs.x;
        this->stringLength = rhs.stringLength;
        this->fwOpts = rhs.fwOpts;
        this->rectangle = rhs.rectangle;
        this->textString = rhs.textString;
        if(!rhs.dX.isNull() && rhs.dXpresent && (rhs.stringLength > 0))
        {
            QScopedArrayPointer<qint16>(new qint16[static_cast<size_t>(rhs.stringLength)]).swap(this->dX);
            memcpy(reinterpret_cast<void *>(this->dX.data()), reinterpret_cast<const void *>(rhs.dX.data()), sizeof(quint16) * static_cast<size_t>(rhs.stringLength));
        }
        else
        {
            QScopedArrayPointer<qint16>().swap(this->dX);
        }
        this->rectanglePresent = rhs.rectanglePresent;
        this->dXpresent = rhs.dXpresent;
    }
    return *this;
}

QPoint MetaExttextoutRecord::getPoint() const
{
    return QPoint(this->x, this->y);
}

quint16 MetaExttextoutRecord::getFWOpts() const
{
    return this->fwOpts;
}

bool MetaExttextoutRecord::isRectanglePresent() const
{
    return this->rectanglePresent;
}

QRect MetaExttextoutRecord::getRect() const
{
    return this->rectangle.getRect();
}

QString MetaExttextoutRecord::getString(QTextCodec *codec) const
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

bool MetaExttextoutRecord::isDXPresent() const
{
    return this->isDXPresent();
}

qint16 MetaExttextoutRecord::getDX(int index) const
{
    if(this->dXpresent)
    {
        if((index < 0) || (index >= this->stringLength))
        {
            return 0;
        }
        return this->dX[index];
    }
    else
    {
        return 0;
    }
}
