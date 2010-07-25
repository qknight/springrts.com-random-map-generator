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

#ifndef DATACONNECTION_H
#define DATACONNECTION_H

#include "DataAbstractItem.h"
class DataAbstractModule;

/*! 
 * this class is representing an connection (if this object is a child of a module)
 * 'in the frontend' as well as in the backend.
 * A connection has a src and a dst, see respective functions
 */
class DataConnection : public DataAbstractItem {
  Q_OBJECT
  public:
    DataConnection( DataAbstractItem* src, DataAbstractItem* dst);
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** Do delete child items from the model first!
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataConnection();
    /*! dumps the internal data structure for debugging use */
    void dump();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    void removeChild( unsigned int index );
    DataAbstractItem* dst();
    DataAbstractItem* src();
  protected:
    DataAbstractItem* m_src;
    DataAbstractItem* m_dst;
};

#endif // DATACONNECTION_H
