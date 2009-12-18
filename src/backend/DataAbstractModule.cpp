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

#include "DataAbstractModule.h"

DataAbstractModule::DataAbstractModule( /*DataAbstractItem* parent*/ ) /*: DataAbstractItem( parent )*/ {}

DataAbstractModule::~DataAbstractModule() {
//   qDebug() << __FUNCTION__;
  if ( m_childItems.size() > 0 ) {
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "FATAL ERROR: Still have " << m_childItems.size() << " childItems";
    exit( 1 );
  }
  if ( m_reverseChildItems.size() > 0 ) {
    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "FATAL ERROR: Still have " << m_reverseChildItems.size() << " reverseChildItems";
    exit( 1 );
  }
}

void DataAbstractModule::dump() {
//   qDebug() << "  \\---DataModule::ID=" << ID << " childs:" << childCount() << ": " << ( unsigned int ) this << " parent=(" << ( unsigned int ) this->parent() << ")";
  // call dump for all children

  qDebug() << "     |-forward childs";
  for ( int i = 0; i < childCount(); ++i ) {
    child( i )->dump();
  }

  qDebug() << "     |-backward childs";
  for ( int i = 0; i < reverseChildItems().size(); ++i ) {
    reverseChildItems()[i]->dump();
  }
}

unsigned int DataAbstractModule::getObjectType() {
  return DataItemType::DATAABSTRACTMODULE;
}

//FIXME CRITICAL check this code below
void DataAbstractModule::appendChild( DataAbstractItem *item ) {

  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
    return;
  }

  // this is the inverted connection item: r_item
  DataConnection* f_item = static_cast<DataConnection*>( item );
  DataConnection* r_item;

  // in any case we want to add a r_item and link it to f_item with the
  // inverseConnection pointer! we can overwrite the next_DataModule later anyway...
  if ( f_item->next_node() == NULL )
    r_item = new DataConnection( this );
  else
    r_item = new DataConnection( f_item->next_node() );
  r_item->setNext_node( this );

  DataAbstractModule* dst = static_cast<DataAbstractModule*>( f_item->next_node() );

  f_item->inverseConnection = r_item;
  r_item->inverseConnection = f_item;

  if ( f_item->next_node() != NULL )
    // when creating a connection manually we ignore to execute the next statement
    // when using the randomAutomate script in automatehandler.cpp the setNext_DataModule
    // call is already used and we can add the reversePath to dst!
    dst->appendChildReversePath( r_item );

  appendChildForwardPath( f_item );
}

void DataAbstractModule::removeChild( unsigned int index ) {
  // 1. first delete the reverse connection
  DataConnection* f_item = (( DataConnection* )m_childItems[index] );
  DataConnection* r_item = f_item->inverseConnection;
//   qDebug() << (unsigned int)f_item->inverseConnection;
//   qDebug() << (unsigned int)r_item->inverseConnection;
//   ((DataModule*)r_item->parent())->removeChildReversePath(r_item);

//   DataAbstractItem* rItem = r_item;//inverseConnection;
  DataAbstractItem* rItemParent = r_item->parent();
  (( DataAbstractModule* )rItemParent )->removeChildReversePath( r_item );

//   DataConnection* f_item = ((DataConnection*)m_childItems[index]);
//   DataConnection* r_item = f_item->inverseConnection;
//   ((DataModule*)r_item->parent())->removeChildReversePath(r_item);

  // 2. now finally delete the forward connection
  m_childItems.removeAt( index );

  // free the objects
  delete r_item;
  delete f_item;
}

void DataAbstractModule::appendChildForwardPath( DataAbstractItem *item ) {
  if ( m_childItems.contains( item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing child!" );
    return;
  }
  m_childItems.append( item );
}

void DataAbstractModule::appendChildReversePath( DataAbstractItem *r_item ) {
  //TODO symbol needs to be set as well
  if ( m_reverseChildItems.contains( r_item ) ) {
    qDebug( "ERROR: detected an attepmt to add an already existing reverseChild!" );
    return;
  }

  m_reverseChildItems.append( r_item );
}

void DataAbstractModule::removeChildReversePath( DataAbstractItem *item ) {
  for ( int i = 0; i < m_reverseChildItems.size(); ++i )
    if ( item == m_reverseChildItems[i] ) {
//       qDebug() << (unsigned int) this << "Item to delete found";
      m_reverseChildItems.removeAt( i );
      return;
    }
//     qDebug() << (unsigned int) this <<  "Item to delete NOT found";
}

const QList<DataAbstractItem*> DataAbstractModule::reverseChildItems() {
  return m_reverseChildItems;
}


