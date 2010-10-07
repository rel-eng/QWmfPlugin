/* META_SETLAYOUT record implementation.

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

#include "MetaSetlayoutRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaSetlayoutRecord::MetaSetlayoutRecord() : MetafileRecord(5, META_SETLAYOUT), layout(LAYOUT_LTR)
{
}

MetaSetlayoutRecord::MetaSetlayoutRecord(quint16 layout) : MetafileRecord(5, META_SETLAYOUT), layout(layout)
{
}

MetaSetlayoutRecord::MetaSetlayoutRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_SETLAYOUT & 0x00FF))
    {
        throw std::runtime_error("Not a META_SETLAYOUT record");
    }
    this->layout = readUnsignedWord(device);
    //Зарезервированное 16-битное значение не считываем
}

MetaSetlayoutRecord::MetaSetlayoutRecord(const MetaSetlayoutRecord &rhs) : MetafileRecord(rhs), layout(rhs.layout)
{
}

MetaSetlayoutRecord::~MetaSetlayoutRecord()
{
}

MetaSetlayoutRecord & MetaSetlayoutRecord::operator=(const MetaSetlayoutRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->layout = rhs.layout;
    }
    return *this;
}

quint16 MetaSetlayoutRecord::getLayout() const
{
    return this->layout;
}
