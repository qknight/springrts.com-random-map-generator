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

/*! A new connection is created with a invalid destination (NULL) and:
** - the destination can be changed as often as needed but
** - it can't be resetted to NULL
** - if a node is deleted all the connection references (in/out/loop) are removed
**   (see node.cpp for more detail)
** You can use the internal int representation of the literals Sigma used to express
** transitions (values on the edges) from one node to another (or loop). This is handy
** in case you want to compare values fast (instead of QString compare)
**
 ** inserting childs and removing childs is heavily modified in this class!
*/
class DataConnection : public DataAbstractItem {
  Q_OBJECT
  public:
    DataConnection( DataAbstractItem* parent );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataConnection();
    /*! NULL or a valid DataAbstractItem: can be set quit flexible */
    DataAbstractItem* next_node();
    /*! dumps the internal data structure for debugging use */
    void dump();
    /*! sets the 'next node' to node*/
    void setNext_node( DataAbstractItem* node );
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    /*! can't think of why this is used in a DataConnection */
    void removeChild( unsigned int index );
    /*! this was added very late but showed to be helpful in many regards */
    DataConnection* inverseConnection;
  private:
    /*! internal storage of the next_node pointer */
    DataAbstractItem* m_next_node;
};

#endif // DATACONNECTION_H
