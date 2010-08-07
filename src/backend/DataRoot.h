/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef DATAROOT_H
#define DATAROOT_H

#include "DataAbstractItem.h"

/*! this class is only instantiated once for every automate
 ** this is the only instance which is able to give valid IDs */
class DataRoot : public DataAbstractItem {
  friend class Model;
  public:
    DataRoot( DataAbstractItem* parent = 0 );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataRoot();
    /*! helper to identify what kind of object 'this' is */
    unsigned int getObjectType();
    /*! removes a node at index position [index]
     - if index is valid, then the item at pos index is removed
     - if index is invalid then the program stops with exit(0) */
    void removeChild( unsigned int index );
};

#endif // DATAROOT_H
