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

DataPort::~DataPort(){};

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

bool DataPort::insertConnection ( DataConnection* c ) {
//   qDebug() << __PRETTY_FUNCTION__;
//     DataAbstractModule* dstItem = static_cast<DataAbstractModule*> ( c->dst ( this ) );
//     // 1. check if already in use (check remote side only!)
//     //    - inputs/modputs can only be used once
//     //    - outputs may have multiple connections 
//     //      ('this' is the side with the output, this is guaranteed by 
//     //      appendChild and (c->validate() already ))
//     if ( dstItem->isPortUsed(c) )
//         return false;
// 
//     // 2. insert connection & also the respective backward connection
//     m_childItems.append ( c );
//     dstItem->insertReference ( c );
    return true;
}

void DataPort::insertReference ( DataAbstractItem* item ) {
//   qDebug() << __PRETTY_FUNCTION__;
//     m_childItemsReferences.append ( item );
}

void DataPort::removeChild ( unsigned int index ) {
  // remove childs (all ports)
}

//FIXME todo
void DataPort::removeReference ( DataAbstractItem* item ) {
//   m_childItemsReferences.remove ( item );
}

void DataPort::dump(){};