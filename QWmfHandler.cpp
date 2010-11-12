/* Wmf handler implementation.

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

#include <QBuffer>

#include "QWmfHandler.h"
#include "Internal/MetaPlaceableRecord.h"
#include "Internal/MetaHeaderRecord.h"
#include "Internal/ConcurrentRecordLoader.h"

QWmfHandler::QWmfHandler(QIODevice *device)
{
    setDevice(device);
}

QWmfHandler::~QWmfHandler()
{
}

bool QWmfHandler::canRead() const
{
    return device()->peek(4) == "\x9A\xC6\xCD\xD7";
}

bool QWmfHandler::canRead(QIODevice *device)
{
    return device->peek(4) == "\x9A\xC6\xCD\xD7";
}

bool QWmfHandler::read(QImage *image)
{
    MetaPlaceableRecord header;
    MetaHeaderRecord metaHeader;
    bool invalidHeader = false;
    try
    {
        header = MetaPlaceableRecord(*device());
        metaHeader = MetaHeaderRecord(*device());
    }
    catch(...)
    {
        invalidHeader = true;
    }
    if (invalidHeader)
    {
        return false;
    }
    qreal widthLU = static_cast<qreal>(qAbs(header.getRight() - header.getLeft()));
    qreal heightLU = static_cast<qreal>(qAbs(header.getBottom() - header.getTop()));
    qreal tpi = qAbs(static_cast<qreal>(header.getTpi()));
    int width = qRound((widthLU / tpi) * static_cast<qreal>(72.0));
    int height = qRound((heightLU / tpi) * static_cast<qreal>(72.0));
    QImage result(width, height, QImage::Format_ARGB32);
    result.fill(0);
    result.setDotsPerMeterX(2835);
    result.setDotsPerMeterY(2835);
    bool invalidRecordsData = false;
    try
    {
        ConcurrentRecordLoader recordLoader(*device());
    }
    catch(...)
    {
        invalidRecordsData = true;
    }
    if(invalidRecordsData)
    {
        return false;
    }
    *image = result;
    return true;
}

bool QWmfHandler::supportsOption(ImageOption option) const
{
    return option == Size;
}

QVariant QWmfHandler::option(ImageOption option) const
{
    if (option == Size)
    {
        QByteArray bytes = device()->peek(22);
        if(bytes.size() == 22)
        {
            QBuffer headerBuf(&bytes);
            headerBuf.open(QIODevice::ReadOnly);
            MetaPlaceableRecord header;
            bool invalidHeader = false;
            try
            {
                header = MetaPlaceableRecord(headerBuf);
            }
            catch(...)
            {
                invalidHeader = true;
            }
            headerBuf.close();
            if(!invalidHeader)
            {
                qreal widthLU = static_cast<qreal>(qAbs(header.getRight() - header.getLeft()));
                qreal heightLU = static_cast<qreal>(qAbs(header.getBottom() - header.getTop()));
                qreal tpi = qAbs(static_cast<qreal>(header.getTpi()));
                int width = qRound((widthLU / tpi) * static_cast<qreal>(72.0));
                int height = qRound((heightLU / tpi) * static_cast<qreal>(72.0));
                return QSize(width, height);
            }
        }
    }
    return QVariant();
}
