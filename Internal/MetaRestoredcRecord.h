/* META_RESTOREDC record definition.

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

#ifndef METARESTOREDCRECORD_H
#define METARESTOREDCRECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

class MetaRestoredcRecord : public MetafileRecord
{
private:
    //Если положительный, то абсолютный номер контекса, если отрицательный - то смещение относительно текущего номера контекста
    qint16 nSavedDC;
public:
    MetaRestoredcRecord();
    MetaRestoredcRecord(qint16 nSavedDC);
    MetaRestoredcRecord(QIODevice &device);
    MetaRestoredcRecord(const MetaRestoredcRecord &rhs);
    virtual ~MetaRestoredcRecord();
    MetaRestoredcRecord &operator=(const MetaRestoredcRecord &rhs);
    qint16 getNSavedDC() const;
};

#endif // METARESTOREDCRECORD_H
