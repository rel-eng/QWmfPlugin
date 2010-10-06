/* META_HEADER record definition.

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

#ifndef METAHEADERRECORD_H
#define METAHEADERRECORD_H

#include <QtGlobal>
#include <QIODevice>

enum MetafileType : quint16
{
    //Метафайл хранится в памяти
    MEMORY_METAFILE = 0x0001,
    //Метафайл хранится на диске
    DISK_METAFILE = 0x0002
};

enum MetafileVersion : quint16
{
    //Не поддерживаются независимые от устройства вывода битмапы
    METAFILE_VERSION100 = 0x0100,
    //Поддерживаются независимые от устройства вывода битмапы
    METAFILE_VERSION300 = 0x0300
};

class MetaHeaderRecord
{
private:
    //Тип метафайла
    quint16 type;
    //Размер заголовка в 16-битных словах
    quint16 headerSizeInWords;
    //Версия метафайла
    quint16 version;
    //Размер метафайла в 16-битных словах
    quint32 sizeInWords;
    //Количество графических объектов в метафайле
    quint16 numberOfObjects;
    //Размер наибольшей записи в метафайле в 16-битных словах
    quint32 maxRecordSizeInWords;
    //Всегда ноль
    quint16 numberOfMembers;
public:
    MetaHeaderRecord();
    MetaHeaderRecord(quint16 type, quint16 version, quint32 sizeInWords, quint16 numberOfObjects, quint32 maxRecordSizeInWords);
    MetaHeaderRecord(QIODevice &device);
    MetaHeaderRecord(const MetaHeaderRecord &rhs);
    virtual ~MetaHeaderRecord();
    MetaHeaderRecord &operator=(const MetaHeaderRecord &rhs);
    quint16 getType() const;
    quint16 getVersion() const;
    quint16 getSizeInWords() const;
    quint16 getNumberOfObjects() const;
    quint32 getMaxRecordSizeInWords() const;
};

#endif // METAHEADERRECORD_H
