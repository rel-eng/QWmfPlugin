/* META_HEADER record implementation.

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

#include "MetaHeaderRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaHeaderRecord::MetaHeaderRecord() : type(MEMORY_METAFILE), headerSizeInWords(9), version(METAFILE_VERSION300), sizeInWords(0), numberOfObjects(0), maxRecordSizeInWords(0), numberOfMembers(0)
{
}

MetaHeaderRecord::MetaHeaderRecord(quint16 type, quint16 version, quint32 sizeInWords, quint16 numberOfObjects, quint32 maxRecordSizeInWords) : type(type), headerSizeInWords(9), version(version), sizeInWords(sizeInWords), numberOfObjects(numberOfObjects), maxRecordSizeInWords(maxRecordSizeInWords), numberOfMembers(0)
{
}

MetaHeaderRecord::MetaHeaderRecord(QIODevice &device)
{
    this->type = readUnsignedWord(device);
    if((this->type != MEMORY_METAFILE) && (this->type != DISK_METAFILE))
    {
        throw std::runtime_error("Invalid metafile type");
    }
    this->headerSizeInWords = readUnsignedWord(device);
    if(this->headerSizeInWords != 9)
    {
        throw std::runtime_error("Invalid metafile header size");
    }
    this->version = readUnsignedWord(device);
    if((this->version != METAFILE_VERSION100) && (this->version != METAFILE_VERSION300))
    {
        throw std::runtime_error("Invalid metafile version");
    }
    this->sizeInWords = readUnsignedDWord(device);
    this->numberOfObjects = readUnsignedWord(device);
    this->maxRecordSizeInWords = readUnsignedDWord(device);
    this->numberOfMembers = readUnsignedWord(device);
    if(this->numberOfMembers != 0)
    {
        throw std::runtime_error("Number of members is non-zero");
    }
}

MetaHeaderRecord::MetaHeaderRecord(const MetaHeaderRecord &rhs) : type(rhs.type), headerSizeInWords(rhs.headerSizeInWords), version(rhs.version), sizeInWords(rhs.sizeInWords), numberOfObjects(rhs.numberOfObjects), maxRecordSizeInWords(rhs.maxRecordSizeInWords), numberOfMembers(rhs.numberOfMembers)
{
}

MetaHeaderRecord::~MetaHeaderRecord()
{
}

MetaHeaderRecord & MetaHeaderRecord::operator=(const MetaHeaderRecord &rhs)
{
    if (this != &rhs)
    {
        this->type = rhs.type;
        this->headerSizeInWords = rhs.headerSizeInWords;
        this->version = rhs.version;
        this->sizeInWords = rhs.sizeInWords;
        this->numberOfObjects = rhs.numberOfObjects;
        this->maxRecordSizeInWords = rhs.maxRecordSizeInWords;
        this->numberOfMembers = rhs.numberOfMembers;
    }
    return *this;
}

quint16 MetaHeaderRecord::getType() const
{
    return this->type;
}

quint16 MetaHeaderRecord::getVersion() const
{
    return this->version;
}

quint16 MetaHeaderRecord::getSizeInWords() const
{
    return this->sizeInWords;
}

quint16 MetaHeaderRecord::getNumberOfObjects() const
{
    return this->numberOfObjects;
}

quint32 MetaHeaderRecord::getMaxRecordSizeInWords() const
{
    return this->maxRecordSizeInWords;
}
