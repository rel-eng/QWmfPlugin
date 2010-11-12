/* WMF plugin main implementation.

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

#include "QWmfPlugin.h"

#include "QWmfHandler.h"

Q_EXPORT_PLUGIN2(qwmf, QWmfPlugin)

QWmfPlugin::QWmfPlugin()
{
}

QWmfPlugin::~QWmfPlugin()
{
}

QStringList QWmfPlugin::keys() const
{
    return QStringList() << "wmf";
}

QImageIOPlugin::Capabilities QWmfPlugin::capabilities(QIODevice *device, const QByteArray &format) const
{
    if (format == "wmf")
    {
        return Capabilities(CanRead);
    }
    if (!(format.isEmpty() && device->isOpen()))
    {
        return 0;
    }
    Capabilities cap;
    if (device->isReadable() && QWmfHandler::canRead(device))
    {
        cap |= CanRead;
    }
    return cap;
}

QImageIOHandler *QWmfPlugin::create(QIODevice *device, const QByteArray &format) const
{
    QImageIOHandler *handler = new QWmfHandler(device);
    handler->setFormat(format);
    return handler;
}
