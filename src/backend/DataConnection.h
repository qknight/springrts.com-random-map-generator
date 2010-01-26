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
 * it is designed that dependant who asks (either src module or dst module) will get 
 * the wanted answer seen from these objects, meaning:
 *   'src module' named a asks for dst() using dst(a), this will return 'dst'
 * 
 * this class can be used to validate a connection, see the code to learn which criteria 
 * is tested for...
 */
class DataConnection : public DataAbstractItem {
  Q_OBJECT
  public:
    DataConnection( DataAbstractItem* src, int srcType, int srcPortNumber, 
		    DataAbstractItem* dst, int dstType, int dstPortNumber );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataConnection();
    /*! dumps the internal data structure for debugging use */
    void dump();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    /*! can't think of why this is used in a DataConnection */
    void removeChild( unsigned int index );
    DataAbstractItem* dst(DataAbstractItem* querier);
    int srcType(DataAbstractItem* querier);
    int srcPortNumber(DataAbstractItem* querier);
    DataAbstractItem* src(DataAbstractItem* querier);
    int dstType(DataAbstractItem* querier);
    int dstPortNumber(DataAbstractItem* querier);
    bool validate();
  protected:
    DataAbstractItem* m_src; 
    int m_srcType; 
    int m_srcPortNumber; 
    DataAbstractItem* m_dst; 
    int m_dstType; 
    int m_dstPortNumber;
};

#endif // DATACONNECTION_H
