/* META_TEXTOUT record definition.

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

#ifndef METATEXTOUTRECORD_H
#define METATEXTOUTRECORD_H

#include <QtGlobal>
#include <QIODevice>
#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QPoint>

#include "MetafileRecord.h"

class MetaTextoutRecord : public MetafileRecord
{
private:
    quint16 stringLength;
    QByteArray textString;
    qint16 yStart;
    qint16 xStart;
public:
    MetaTextoutRecord();
    MetaTextoutRecord(const QByteArray &textString, qint16 yStart, qint16 xStart);
    MetaTextoutRecord(QIODevice &device);
    MetaTextoutRecord(const MetaTextoutRecord &rhs);
    virtual ~MetaTextoutRecord();
    MetaTextoutRecord &operator=(const MetaTextoutRecord &rhs);
    QString getString(QTextCodec *codec) const;
    QPoint getStart() const;
};

#endif // METATEXTOUTRECORD_H
