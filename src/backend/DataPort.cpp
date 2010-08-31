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

#include "DataPort.h"
DataPort::DataPort(int portType, int portDirection, int portNumber) {
    qDebug() << __PRETTY_FUNCTION__;
    m_portType=portType;
    m_portDirection=portDirection;
    m_portNumber=portNumber;
}

DataPort::~DataPort() {
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << "   child" << m_childItems.size();
    qDebug() << "refchild" << m_referencesChildItems.size();
    // remove all connections
/*    foreach(DataAbstractItem* item, m_childItems) {
        removeChild(m_childItems.indexOf(item));
    }*/
    // remove all references
/*    foreach(DataAbstractItem* item, m_referencesChildItems) {
        removeReference(m_referencesChildItems.indexOf(item));
    }*/
};

unsigned int DataPort::getObjectType() {
    return DataItemType::PORT;
}

unsigned int DataPort::PortDirection() {
    return m_portDirection;
}

unsigned int DataPort::PortType() {
    return m_portType;
}

unsigned int DataPort::PortNumber() {
    return m_portNumber;
}

void DataPort::appendChild( DataAbstractItem *child ) {
    DataConnection* c = static_cast<DataConnection*>(child);
    insertConnection(c);
}

bool DataPort::insertConnection ( DataConnection* c ) {
//     qDebug() << __PRETTY_FUNCTION__;
    DataPort* dstItem = static_cast<DataPort*> ( c->dst() );
    m_childItems.append ( c );
    dstItem->insertReference ( c );
    return true;
}

void DataPort::insertReference ( DataAbstractItem* item ) {
//   qDebug() << __PRETTY_FUNCTION__;
    m_referencesChildItems.append ( item );
}

unsigned int DataPort::referenceCount ( ) {
    return m_referencesChildItems.size();
}

void DataPort::removeChild ( unsigned int index ) {
    qDebug() << __PRETTY_FUNCTION__;
    if ( m_childItems.size() < index ) {
        qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: child item not found";
        exit( 1 );
    }

    DataAbstractItem* child = m_childItems[index];

    // let's not forget to remove also the reference at the other port
    DataConnection* childConnection = static_cast<DataConnection*> (child);
    DataPort* dstItem = static_cast<DataPort*> ( childConnection->dst() );
    int i = dstItem->referenceChildItems().indexOf(childConnection);
//     qDebug() << dstItem->referenceChildItems().size();
    if (i == -1) {
        qDebug() << __PRETTY_FUNCTION__ << "this should not happen";
        exit(1);
    }
    dstItem->removeReference ( i );

    m_childItems.removeAt( index );
    delete child;
}

void DataPort::removeReference ( unsigned int index ) {
    qDebug() << __PRETTY_FUNCTION__ << index;

    if ( m_referencesChildItems.size() < index ) {
        qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: child item not found";
        exit( 1 );
    }
    DataAbstractItem* child = m_referencesChildItems[index];
    m_referencesChildItems.removeAt( index );
}

QList<DataAbstractItem*> DataPort::referenceChildItems() const {
    return m_referencesChildItems;
}
