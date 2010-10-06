/* I/O functions prototypes.

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

#ifndef IOUTILS_H_
#define IOUTILS_H_

#include <QtGlobal>
#include <QString>
#include <QTextCodec>
#include <QColor>
#include <QIODevice>

#include <cstddef>

void seekDevice(QIODevice &device, qint64 offset);
quint8 readUnsignedByte(QIODevice &device);
qint8 readSignedByte(QIODevice &device);
quint16 readUnsignedWord(QIODevice &device);
qint16 readSignedWord(QIODevice &device);
quint32 readUnsignedDWord(QIODevice &device);
qint32 readSignedDWord(QIODevice &device);
quint64 readUnsignedQWord(QIODevice &device);
qint64 readSignedQWord(QIODevice &device);
void fillBuffer(QIODevice &device, qint64 length, void *buffer, size_t bufferSize);
void peekToBuffer(QIODevice &device, qint64 length, void *buffer, size_t bufferSize);
QString readFixedLengthString(QIODevice &device, uint length, QTextCodec *codec);
QString readNullTerminatedString(QIODevice &device, qint64 maxSize, QTextCodec *codec, qint64 &length);
QRgb readRGBDword(QIODevice &device);
QRgb readRGBADword(QIODevice &device);
QRgb readBGRDword(QIODevice &device);
QRgb readBGRADword(QIODevice &device);
QRgb readRGBBytes(QIODevice &device);
QRgb readBGRBytes(QIODevice &device);

#endif /* IOUTILS_H_ */
