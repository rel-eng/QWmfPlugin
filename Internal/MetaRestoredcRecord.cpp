/* META_RESTOREDC record implementation.

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

#include "MetaRestoredcRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaRestoredcRecord::MetaRestoredcRecord() : MetafileRecord(4, META_RESTOREDC), nSavedDC(0)
{
}

MetaRestoredcRecord::MetaRestoredcRecord(qint16 nSavedDC) : MetafileRecord(4, META_RESTOREDC), nSavedDC(nSavedDC)
{
}

MetaRestoredcRecord::MetaRestoredcRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_RESTOREDC & 0x00FF))
    {
        throw std::runtime_error("Not a META_RESTOREDC record");
    }
    this->nSavedDC = readSignedWord(device);
}

MetaRestoredcRecord::MetaRestoredcRecord(const MetaRestoredcRecord &rhs) : MetafileRecord(rhs), nSavedDC(rhs.nSavedDC)
{
}

MetaRestoredcRecord::~MetaRestoredcRecord()
{
}

MetaRestoredcRecord & MetaRestoredcRecord::operator=(const MetaRestoredcRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->nSavedDC = rhs.nSavedDC;
    }
    return *this;
}

qint16 MetaRestoredcRecord::getNSavedDC() const
{
    return this->nSavedDC;
}
