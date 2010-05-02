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

//   dump();
}

DataRoot::~DataRoot() {
//   qDebug() << __PRETTY_FUNCTION__;

  if (childCount() != 0) {
    qDebug() << __PRETTY_FUNCTION__ << "-> FATAL ERROR: not all child items were removed prior to this function call, exiting";
    exit(1);
  }
}

void DataRoot::dump() {
//   qDebug() << "automateroot::ID=" << ID << " -> " << childCount() << ": " << ( unsigned int ) this;
  // call dump for all children
  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }
}

unsigned int DataRoot::getObjectType() {
  return DataItemType::DATAROOT;
}

void DataRoot::removeChild( unsigned int index ) {
  if ( (unsigned int)m_childItems.size() < index ) {
    qDebug() << "Fatal error, childItems.size() < index!";
    qDebug() << "having " << m_childItems.size() << " childs";
    exit( 1 );
  }
  DataAbstractItem* child = m_childItems[index];
  m_childItems.removeAt( index );
  delete child;
}
