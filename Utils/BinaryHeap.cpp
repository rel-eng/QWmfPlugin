/* Binary heap implementation.

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

#include "BinaryHeap.h"

#include <stdexcept>

template <class T> BinaryHeap<T>::BinaryHeap(size_t capacity) : capacity(capacity), size(0), elements()
{
    QScopedArrayPointer<T>(new T[this->capacity]).swap(this->elements);
}


template <class T> BinaryHeap<T>::~BinaryHeap()
{
}

template <class T> bool BinaryHeap<T>::isEmpty() const
{
    return (this->size == 0);
}

template <class T> void BinaryHeap<T>::insert(T element)
{
    if(this->size >= this->capacity)
    {
        throw std::runtime_error("Unable to add element, binary heap is already full");
    }
    size_t slot = this->size+1;
    while((slot > 1) && (element < this->elements[slot/2-1]))
    {
        this->elements[slot-1] = this->elements[slot/2-1];
        slot=slot/2;
    }
    this->elements[slot-1] = element;
    this->size++;
}

template <class T> T BinaryHeap<T>::deleteMin()
{
    size_t child = 0;
    size_t slot = 1;
    if(this->size == 0)
    {
        throw std::runtime_error("Unable to delete element, binary heap is already empty");
    }
    T minNode = this->elements[0];
    T lastNode = this->elements[this->size-1];
    this->elements[0] = this->elements[this->size-1];
    this->size--;
    while((slot * 2 - 1) < (this->size + 1))
    {
        child=slot * 2;
        if(!(child==this->size + 1) && (this->elements[child] < this->elements[child-1]))
        {
            child++;
        }
        if(this->elements[child-1] < lastNode)
        {
            this->elements[slot-1] = this->elements[child-1];
        }
        else
        {
            break;
        }
        slot = child;
    }
    this->elements[slot-1] = lastNode;
    return minNode;
}
