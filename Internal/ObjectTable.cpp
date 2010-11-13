/* ObjectTable implementation.

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

#include "ObjectTable.h"

#include <stdexcept>

ObjectTable::ObjectTable(size_t numberOfObjects) : freeHandles(numberOfObjects), objects()
{
    for(size_t index = 0; index < numberOfObjects; index++)
    {
        freeHandles.insert(static_cast<GraphicsObjectHandle>(index));
    }
}

ObjectTable::~ObjectTable()
{
}

GraphicsObjectHandle ObjectTable::insertObject(QSharedPointer<GraphicsObject> object)
{
    if(this->freeHandles.isEmpty())
    {
        throw std::runtime_error("Object table is full");
    }
    GraphicsObjectHandle handle = this->freeHandles.deleteMin();
    this->objects.insert(handle, object);
    return handle;
}

void ObjectTable::removeObject(GraphicsObjectHandle handle)
{
    if(!this->objects.contains(handle))
    {
        throw std::runtime_error("Removing nonexistent object from object table");
    }
    this->objects.remove(handle);
    this->freeHandles.insert(handle);
}

QSharedPointer<GraphicsObject> ObjectTable::getObjectByHandle(GraphicsObjectHandle handle)
{
    if(!this->objects.contains(handle))
    {
        throw std::runtime_error("Invalid graphics object handle");
    }
    return this->objects.value(handle);
}
