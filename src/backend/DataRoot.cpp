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

#include "DataRoot.h"

DataRoot::DataRoot( DataAbstractItem* parent ) : DataAbstractItem( parent ) {
//   qDebug() << "adding a new DataRoot with parent: " << parent;
}

// WARNING
// - this function can only be called by the class Model 
// - it MAY only be called when no view is attached anymore
// - calling ~DataRoot will recycle the whole Data* backend structure
// - removing single elements maybe be done by class Model using the item's parent with removeChild(item) instead
//   of direct access by the model
DataRoot::~DataRoot() {
//   qDebug() << __PRETTY_FUNCTION__;
  foreach(DataAbstractItem* item, m_childItems) {
    removeChild(m_childItems.indexOf(item));
  }
}

unsigned int DataRoot::getObjectType() {
  return DataItemType::ROOT;
}

void DataRoot::removeChild( unsigned int index ) {
  if ( m_childItems.size() < index ) {
    qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: child item not found";
    exit( 1 );
  }
  DataAbstractItem* child = m_childItems[index];
  m_childItems.removeAt( index );
  delete child;
}
