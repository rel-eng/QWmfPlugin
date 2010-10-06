/* Concurrent record loader definition.

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

#ifndef CONCURRENTRECORDLOADER_H
#define CONCURRENTRECORDLOADER_H

#include <QtGlobal>
#include <QIODevice>
#include <QList>
#include <QSharedPointer>

#include <QtCore>

#include "MetafileRecord.h"

class ConcurrentRecordLoaderException : public QtConcurrent::Exception
 {
 public:
     void raise() const { throw *this; }
     Exception *clone() const { return new ConcurrentRecordLoaderException(*this); }
 };

class ConcurrentRecordLoader
{
private:
    QList<QSharedPointer<MetafileRecord> > processedRecords;
public:
    ConcurrentRecordLoader(QIODevice &device);
    virtual ~ConcurrentRecordLoader();
    int getRecordsCount() const;
    QSharedPointer<MetafileRecord> getRecord(int index) const;
    Q_DISABLE_COPY(ConcurrentRecordLoader)
};

#endif // CONCURRENTRECORDLOADER_H
