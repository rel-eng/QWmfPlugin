/* I/O functions implementation.

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

#include "IOUtils.h"

#include <QtEndian>
#include <QScopedArrayPointer>
#include <QScopedPointer>
#include <QTextDecoder>

#include <stdexcept>

void seekDevice(QIODevice &device, qint64 offset)
{
    if (!device.seek(offset))
    {
        throw std::runtime_error("Unable to seek file");
    }
}

quint8 readUnsignedByte(QIODevice &device)
{
    quint8 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(1)) != Q_INT64_C(1))
    {
        throw std::runtime_error("Unable to read file");
    }
    return result;
}

qint8 readSignedByte(QIODevice &device)
{
    qint8 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(1)) != Q_INT64_C(1))
    {
        throw std::runtime_error("Unable to read file");
    }
    return result;
}

quint16 readUnsignedWord(QIODevice &device)
{
    quint16 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(2)) != Q_INT64_C(2))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

qint16 readSignedWord(QIODevice &device)
{
    qint16 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(2)) != Q_INT64_C(2))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

quint32 readUnsignedDWord(QIODevice &device)
{
    quint32 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

qint32 readSignedDWord(QIODevice &device)
{
    qint32 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

quint64 readUnsignedQWord(QIODevice &device)
{
    quint64 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(8)) != Q_INT64_C(8))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

qint64 readSignedQWord(QIODevice &device)
{
    qint64 result = 0;
    if (device.read(reinterpret_cast<char *> (&result), Q_INT64_C(8)) != Q_INT64_C(8))
    {
        throw std::runtime_error("Unable to read file");
    }
    result = qFromLittleEndian(result);
    return result;
}

void fillBuffer(QIODevice &device, qint64 length, void *buffer, size_t bufferSize)
{
    if(length < Q_INT64_C(0))
    {
        throw std::runtime_error("Invalid length parameter value");
    }
    if(bufferSize < static_cast<size_t>(length))
    {
        throw std::runtime_error("Buffer is too small");
    }
    qint64 bytesRead = device.read(reinterpret_cast<char *> (buffer), length);
    if (bytesRead != length)
    {
        throw std::runtime_error("Unable to read file");
    }
}

void peekToBuffer(QIODevice &device, qint64 length, void *buffer, size_t bufferSize)
{
    if(length < Q_INT64_C(0))
    {
        throw std::runtime_error("Invalid length parameter value");
    }
    if(bufferSize < static_cast<size_t>(length))
    {
        throw std::runtime_error("Buffer is too small");
    }
    qint64 bytesRead = device.peek(reinterpret_cast<char *> (buffer), length);
    if (bytesRead != length)
    {
        throw std::runtime_error("Unable to read file");
    }
}

QString readFixedLengthString(QIODevice &device, uint length, QTextCodec *codec)
{
    if(codec == NULL)
    {
        throw std::runtime_error("Codec is NULL");
    }
    if(length > 0)
    {
        QScopedArrayPointer<quint8> stringIn(new quint8[static_cast<size_t>(length)]);
        if (device.read(reinterpret_cast<char *> (stringIn.data()), static_cast<qint64>(length)) != static_cast<qint64>(length))
        {
            throw std::runtime_error("Unable to read file");
        }
        uint stringLength = qstrnlen(reinterpret_cast<char *> (stringIn.data()), length);
        QScopedPointer<QTextDecoder> decoder(codec->makeDecoder());
        if (decoder.isNull())
        {
            throw std::runtime_error("Unable to create text decoder");
        }
        return decoder->toUnicode(reinterpret_cast<const char *> (stringIn.data()), static_cast<int> (stringLength));
    }
    else
    {
        return QString();
    }
}

QString readNullTerminatedString(QIODevice &device, qint64 maxSize, QTextCodec *codec, qint64 &length)
{
    if(codec == NULL)
    {
        throw std::runtime_error("Codec is NULL");
    }
    if(maxSize > Q_INT64_C(0))
    {
        qint64 pos = device.pos();
        qint64 bytesRead = Q_INT64_C(0);
        while (bytesRead < maxSize)
        {
            quint8 nextSymbol = 0;
            if (device.read(reinterpret_cast<char *> (&nextSymbol), Q_INT64_C(1)) != Q_INT64_C(1))
            {
                throw std::runtime_error("Unable to read file");
            }
            bytesRead++;
            if (nextSymbol == 0)
            {
                break;
            }
        }
        qint64 stringLength = device.pos() - pos;
        length = stringLength;
        seekDevice(device, pos);
        QScopedArrayPointer<quint8> stringIn(new quint8[stringLength]);
        if (device.read(reinterpret_cast<char *> (stringIn.data()), stringLength) != stringLength)
        {
            throw std::runtime_error("Unable to read file");
        }
        QScopedPointer<QTextDecoder> decoder(codec->makeDecoder());
        if (decoder.isNull())
        {
            throw std::runtime_error("Unable to create text decoder");
        }
        if(bytesRead < maxSize)
        {
            return decoder->toUnicode(reinterpret_cast<const char *> (stringIn.data()), static_cast<int> (stringLength - Q_INT64_C(1)));
        }
        else
        {
            return decoder->toUnicode(reinterpret_cast<const char *> (stringIn.data()), static_cast<int> (stringLength));
        }
    }
    else
    {
        length = Q_INT64_C(0);
        return QString();
    }
}

QRgb readRGBDword(QIODevice &device)
{
    quint8 data[] = {0, 0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 redIn = data[0];
    quint8 greenIn = data[1];
    quint8 blueIn = data[2];
    return qRgb(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn));
}

QRgb readRGBADword(QIODevice &device)
{
    quint8 data[] = {0, 0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 redIn = data[0];
    quint8 greenIn = data[1];
    quint8 blueIn = data[2];
    quint8 alphaIn = data[3];
    return qRgba(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn), static_cast<int>(alphaIn));
}

QRgb readBGRDword(QIODevice &device)
{
    quint8 data[] = {0, 0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 blueIn = data[0];
    quint8 greenIn = data[1];
    quint8 redIn = data[2];
    return qRgb(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn));
}

QRgb readBGRADword(QIODevice &device)
{
    quint8 data[] = {0, 0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(4)) != Q_INT64_C(4))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 blueIn = data[0];
    quint8 greenIn = data[1];
    quint8 redIn = data[2];
    quint8 alphaIn = data[3];
    return qRgba(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn), static_cast<int>(alphaIn));
}

QRgb readRGBBytes(QIODevice &device)
{
    quint8 data[] = {0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(3)) != Q_INT64_C(3))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 redIn = data[0];
    quint8 greenIn = data[1];
    quint8 blueIn = data[2];
    return qRgb(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn));
}

QRgb readBGRBytes(QIODevice &device)
{
    quint8 data[] = {0, 0, 0};
    if (device.read(reinterpret_cast<char *> (&data), Q_INT64_C(3)) != Q_INT64_C(3))
    {
        throw std::runtime_error("Unable to read file");
    }
    quint8 blueIn = data[0];
    quint8 greenIn = data[1];
    quint8 redIn = data[2];
    return qRgb(static_cast<int>(redIn), static_cast<int>(greenIn), static_cast<int>(blueIn));
}
