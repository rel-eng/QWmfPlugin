/* Scan object definition.

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

#ifndef SCANOBJECT_H
#define SCANOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QPair>
#include <QVector>

class ScanObject
{
private:
    quint16 scanCount;
    quint16 top;
    quint16 bottom;
    QVector<QPair<quint16, quint16> > scans;
public:
    ScanObject();
    ScanObject(const QVector<QPair<quint16, quint16> > &scans, quint16 top, quint16 bottom);
    ScanObject(QIODevice &device);
    ScanObject(const ScanObject &rhs);
    virtual ~ScanObject();
    ScanObject &operator=(const ScanObject &rhs);
    int getScanCount() const;
    QPair<quint16, quint16> getScan(int index) const;
    quint16 getTop() const;
    quint16 getBottom() const;
};

#endif // SCANOBJECT_H
