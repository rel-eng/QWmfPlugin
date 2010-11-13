/* MetafilePlayer definition.

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

#ifndef METAFILEPLAYER_H
#define METAFILEPLAYER_H

#include <QtGlobal>
#include <QImage>

#include "MetaPlaceableRecord.h"
#include "MetaHeaderRecord.h"
#include "ConcurrentRecordLoader.h"

class MetafilePlayer
{
private:
    Q_DISABLE_COPY(ObjectTable)
public:
    MetafilePlayer();
    virtual ~MetafilePlayer();
    void playMetafile(const MetaPlaceableRecord &placeableRecord, const MetaHeaderRecord &headerRecord, const ConcurrentRecordLoader &recordLoader, QImage &outputImage);
};

#endif // METAFILEPLAYER_H
