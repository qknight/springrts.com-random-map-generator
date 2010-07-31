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
    m_portType=portType;
    m_portDirection=portDirection;
    m_portNumber=portNumber;
}

DataPort::~DataPort() {};

unsigned int DataPort::getObjectType() {
    return DataItemType::DATAPORT;
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
    qDebug() << __PRETTY_FUNCTION__;
    DataPort* dstItem = static_cast<DataPort*> ( c->dst() );
    m_childItems.append ( c );
    dstItem->insertReference ( c );
    return true;
}

void DataPort::insertReference ( DataAbstractItem* item ) {
  qDebug() << __PRETTY_FUNCTION__;
    m_childItemsReferences.append ( item );
}

unsigned int DataPort::referenceCount ( ) {
    return m_childItemsReferences.size();
}

//FIXME todo
void DataPort::removeChild ( unsigned int index ) {
    // remove childs (all ports)
}

//FIXME todo
void DataPort::removeReference ( DataAbstractItem* item ) {
//   m_childItemsReferences.remove ( item );
}

void DataPort::dump() {};
