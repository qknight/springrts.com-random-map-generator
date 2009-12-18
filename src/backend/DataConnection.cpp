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

#include "DataConnection.h"
#include "DataAbstractModule.h"

DataConnection::DataConnection( DataAbstractItem* parent ) : DataAbstractItem( parent ) {
//   ID = generateUniqueID( getObjectType() );
  m_next_node = NULL;
  inverseConnection = NULL;
  //   qDebug() << "NODE ID=" << ID << " TYPE=" << NODE;
}

DataConnection::~DataConnection() {
//   qDebug() << __FUNCTION__;
}

void DataConnection::dump() {
//   QString m_next_node_Id;
//   if(m_next_node != NULL)
//     m_next_node_Id = QString("n%1").arg(m_next_node->getId());
//   else
//     m_next_node_Id = "next_node is not set";
//   //FIXME check m_next_node for NULL
//   qDebug() << "     |  \\---((DataConnection " << QString("c%1").arg(ID) << "))" <<
// //       parent()->getId() << "@" << (unsigned int)parent() <<
//   " >> DEST = " <<
//   m_next_node_Id <<
//   "; inverseConnection =" << QString("c%1").arg(inverseConnection->getId());
// 
//   // call dump for all children
//   if ( childCount() > 0 )
//     qDebug() << "FATAL ERROR in" << __FILE__ << " " << __FUNCTION__ << "this should never happen";
// 
//   for ( int i = 0; i < childCount(); ++i ) {
//     child( i )->dump();
//   }
}

unsigned int DataConnection::getObjectType() {
  return DataItemType::DATACONNECTION;
}

void DataConnection::removeChild( unsigned int index ) {
  if (( unsigned int )m_childItems.size() < index ) {
    qDebug() << "Fatal error, childItems.size() < index!";
    qDebug() << "having " << m_childItems.size() << " childs";
    exit( 0 );
  }
  m_childItems.removeAt( index );
}

DataAbstractItem* DataConnection::next_node() {
  return m_next_node;
}

void DataConnection::setNext_node( DataAbstractItem* newNextNode ) {
  if ( m_next_node == newNextNode )
    return;
//   qDebug() << "warning: we have to relocate the reverseconnection as well";

  if ( inverseConnection == NULL ) {
    m_next_node = newNextNode;
    return;
  }
  // 1. remove the m_next_node's reverse connection reference (remove the reverse connection)
  DataAbstractItem* rItem = inverseConnection;
  DataAbstractItem* rItemParent = rItem->parent();
  (( DataAbstractModule* )rItemParent )->removeChildReversePath( rItem );

  // 2. next add the reverse connection
  (( DataAbstractModule* )newNextNode )->appendChildReversePath( rItem );

  // 3. reset the parent entry
  rItem->setParent( newNextNode );

  // 4. overwrite current m_next_node with node
  m_next_node = newNextNode;
  return;
}







