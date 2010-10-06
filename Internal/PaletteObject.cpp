/* Palette object implementation.

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

#include "PaletteObject.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

PaletteObject::PaletteObject() : start(0x0300), numberOfEntries(0), colorEntries(), flagEntries()
{
}

PaletteObject::PaletteObject(quint16 start, QList<QPair<QRgb, quint8> > entries) : start(start), colorEntries(), flagEntries()
{
    if(entries.count() <= 0xFFFF)
    {
        this->numberOfEntries = static_cast<quint16>(entries.count());
        if(entries.count() > 0)
        {
            QScopedArrayPointer<QRgb>(new QRgb[static_cast<size_t>(entries.count())]).swap(this->colorEntries);
            QScopedArrayPointer<quint8>(new quint8[static_cast<size_t>(entries.count())]).swap(this->flagEntries);
            for(int i = 0; i < entries.count(); i++)
            {
                this->colorEntries[i] = entries.at(i).first;
                this->flagEntries[i] = entries.at(i).second;
            }
        }
    }
    else
    {
        throw std::runtime_error("Too much entries in palette");
    }
}

PaletteObject::PaletteObject(QIODevice &device) : colorEntries(), flagEntries()
{
    this->start = readUnsignedWord(device);
    this->numberOfEntries = readUnsignedWord(device);
    if(this->numberOfEntries > 0)
    {
        QScopedArrayPointer<QRgb>(new QRgb[static_cast<size_t>(this->numberOfEntries)]).swap(this->colorEntries);
        QScopedArrayPointer<quint8>(new quint8[static_cast<size_t>(this->numberOfEntries)]).swap(this->flagEntries);
        QScopedArrayPointer<quint8> buffer(new quint8[static_cast<size_t>(4 * this->numberOfEntries)]);
        fillBuffer(device, static_cast<qint64>(4 * this->numberOfEntries), reinterpret_cast<void *>(buffer.data()), static_cast<size_t>(4 * this->numberOfEntries));
        for(quint16 i = 0; i < this->numberOfEntries; i++)
        {
            this->flagEntries[i] = buffer[4*i];
            quint8 blue = buffer[4*i + 1];
            quint8 green = buffer[4*i + 2];
            quint8 red = buffer[4*i + 3];
            this->colorEntries[i] = qRgb(red, green, blue);
        }
    }
}

PaletteObject::PaletteObject(const PaletteObject &rhs) : start(rhs.start), numberOfEntries(rhs.numberOfEntries), colorEntries(), flagEntries()
{
    if(rhs.numberOfEntries > 0)
    {
        QScopedArrayPointer<QRgb>(new QRgb[static_cast<size_t>(rhs.numberOfEntries)]).swap(this->colorEntries);
        QScopedArrayPointer<quint8>(new quint8[static_cast<size_t>(rhs.numberOfEntries)]).swap(this->flagEntries);
        memcpy(reinterpret_cast<char *>(this->colorEntries.data()), reinterpret_cast<const char *>(rhs.colorEntries.data()), sizeof(QRgb)*static_cast<size_t>(rhs.numberOfEntries));
        memcpy(reinterpret_cast<char *>(this->flagEntries.data()), reinterpret_cast<const char *>(rhs.flagEntries.data()), sizeof(quint8)*static_cast<size_t>(rhs.numberOfEntries));
    }
}

PaletteObject::~PaletteObject()
{
}

PaletteObject & PaletteObject::operator=(const PaletteObject &rhs)
{
    if (this != &rhs)
    {
        this->start = rhs.start;
        this->numberOfEntries = rhs.numberOfEntries;
        if(rhs.numberOfEntries > 0)
        {
            QScopedArrayPointer<QRgb>(new QRgb[static_cast<size_t>(rhs.numberOfEntries)]).swap(this->colorEntries);
            QScopedArrayPointer<quint8>(new quint8[static_cast<size_t>(rhs.numberOfEntries)]).swap(this->flagEntries);
            memcpy(reinterpret_cast<char *>(this->colorEntries.data()), reinterpret_cast<const char *>(rhs.colorEntries.data()), sizeof(QRgb)*static_cast<size_t>(rhs.numberOfEntries));
            memcpy(reinterpret_cast<char *>(this->flagEntries.data()), reinterpret_cast<const char *>(rhs.flagEntries.data()), sizeof(quint8)*static_cast<size_t>(rhs.numberOfEntries));
        }
        else
        {
            QScopedArrayPointer<QRgb>().swap(this->colorEntries);
            QScopedArrayPointer<quint8>().swap(this->flagEntries);
        }
    }
    return *this;
}

quint16 PaletteObject::getPaletteStart() const
{
    return this->start;
}

quint16 PaletteObject::getPaletteEntriesCount() const
{
    return this->numberOfEntries;
}

QRgb PaletteObject::getPaletteEntryColor(quint16 index) const
{
    if(index < this->numberOfEntries)
    {
        return this->colorEntries[index];
    }
}

quint8 PaletteObject::getPaletteEntryFlag(quint16 index) const
{
    if(index < this->numberOfEntries)
    {
        return this->flagEntries[index];
    }
}
