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
#include "DataAbstractItem.h"

DataAbstractItem::DataAbstractItem( DataAbstractItem *parent ) {
//   qDebug() << "DataAbstractItem Constructor called";
  parentItem = parent;
}

DataAbstractItem::~DataAbstractItem() {
//   qDebug() << __PRETTY_FUNCTION__;
}

void DataAbstractItem::appendChild( DataAbstractItem *item ) {
  if ( item->parent() != this ) {
    qDebug( "ERROR: you can't add a child to a parent item where the parent of the child doesn't match the parent you want to add it to!" );
  }
  m_childItems.append( item );
}

DataAbstractItem *DataAbstractItem::child( int row ) {
  return m_childItems.value( row );
}

int DataAbstractItem::childCount() const {
  return m_childItems.count();
}

DataAbstractItem *DataAbstractItem::parent() {
  return parentItem;
}

int DataAbstractItem::row() const {
//   qDebug() << (unsigned int) parentItem;
  if ( parentItem )
    return parentItem->m_childItems.indexOf( const_cast<DataAbstractItem*>( this ) );

  return 0;
}

QList<DataAbstractItem*> DataAbstractItem::childItems() const {
  return m_childItems;
}

void DataAbstractItem::setParent(DataAbstractItem *parent) {
  parentItem = parent;
}
