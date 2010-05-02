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

DataAbstractModule::DataAbstractModule ( int inputs, int modputs, int outputs ) {
    // create the appropriate Ports
//     for(int i = 0; i < inputs; ++i) {
//       insertPort(type);  
//     }
//     for(int i = 0; i < modputs; ++i) {
//       insertPort(type);  
//     }
//     for(int i = 0; i < outputs; ++i) {
//       insertPort(type);  
//     }
}

DataAbstractModule::~DataAbstractModule() {
//     qDebug() << __FUNCTION__;
//     if ( m_childItems.size() > 0 ) {
//         qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "FATAL ERROR: Still have " << m_childItems.size() << " childItems";
//         exit ( 1 );
//     }
//     if ( m_childItemsReferences.size() > 0 ) {
//         qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "FATAL ERROR: Still have " << m_childItemsReferences.size() << " reverseChildItems";
//         exit ( 1 );
//     }
}

void DataAbstractModule::dump() {}

unsigned int DataAbstractModule::getObjectType() {
    return DataItemType::DATAABSTRACTMODULE;
}

void DataAbstractModule::appendChild ( DataAbstractItem *item ) {
  qDebug() << __PRETTY_FUNCTION__;
    if ( item->parent() != this ) {
        qDebug ( "ERROR: you can't add a child to a parent item where \
            the parent of the child doesn't match the parent you want to add it to!" );
        return;
    }
/*
    // this is the inverted connection item: r_item
    DataPort* p = static_cast<DataPort*> ( item );

    // 0. check if allowed (no loops to the same item)
    if ( ! ( c->validate() ) ) {
        qDebug() << __PRETTY_FUNCTION__ << "item not valid";
        return;
    }
    if ( c->srcType ( this ) == PortType::OUTPUT ) {
        insertConnection ( c );
        return;
    } else {
        DataAbstractModule* dstItem = static_cast<DataAbstractModule*> ( c->dst ( this ) );
        dstItem->insertConnection ( c );
        return;
    }*/
}

bool DataAbstractModule::isPortUsed(DataAbstractItem *item) {
//   qDebug() << __PRETTY_FUNCTION__;
//   DataConnection* c = static_cast<DataConnection*> ( item );
//     // a. copy all 'references' into a list
//     // b. remove all 'outputs' from that list
//     // c. filter all items except those with dstType, 
//     //    now search for an item with known portnumber, 
//     //    if item is found 'return false'
//     foreach(DataAbstractItem* ref, m_childItemsReferences) {
//       DataConnection* r = static_cast<DataConnection*> ( ref );
//       if ((c->srcType(this) == r->srcType(this)) && (c->srcPortNumber(this) == r->srcPortNumber(this)))
//         return true;
//     }
//     
    return false;
}

//FIXME todo
void DataAbstractModule::removeChild ( unsigned int index ) {
  // remove child
  // removeReference at remote object
}

// will return how many ports are used per type
int DataAbstractModule::ports ( int type ) {
    switch ( type ) {
    case PortType::INPUT:
        return inputs;
        break;
    case PortType::MODPUT:
        return modputs;
        break;
    case PortType::OUTPUT:
        return outputs;
        break;
    default:
        return 0;
    }
}
