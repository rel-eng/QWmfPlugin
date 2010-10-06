/* Wmf handler definition.

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

#ifndef WMFHANDLER_H
#define WMFHANDLER_H

#include <QImageIOHandler>
#include <QImage>
#include <QByteArray>
#include <QIODevice>
#include <QVariant>

class WmfHandler : public QImageIOHandler
{
public:
    WmfHandler();
    ~WmfHandler();
    bool canRead() const;
    bool read(QImage *image);
    QByteArray name() const;
    static bool canRead(QIODevice *device);
    QVariant option(ImageOption option) const;
    void setOption(ImageOption option, const QVariant &value);
    bool supportsOption(ImageOption option) const;
};

#endif // WMFHANDLER_H
