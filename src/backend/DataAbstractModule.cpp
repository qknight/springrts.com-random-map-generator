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
  // ports need to be created from insertModule(..) in Model.cpp, see also the insertPort(..) implementation
  this->inputs=inputs;
  this->modputs=modputs;
  this->outputs=outputs;
}

DataAbstractModule::~DataAbstractModule() {
    // we have to take care about the Ports, just remove all of them!
    qDebug() << __FUNCTION__;
    while ( m_childItems.size() > 0  ) {
      DataAbstractItem* i = m_childItems.takeLast();
      delete i;
    }
}

void DataAbstractModule::dump() {
    //FIXME currently not used
}

unsigned int DataAbstractModule::getObjectType() {
    return DataItemType::DATAABSTRACTMODULE;
}

void DataAbstractModule::removeChild ( unsigned int index ) {
  // remove all Ports, that means: remove all childs
  //FIXME implement that
}

// will return how many ports are used per type
int DataAbstractModule::ports ( int type ) {
    switch ( type ) {
    case PortDirection::IN:
        return inputs;
        break;
    case PortDirection::MOD:
        return modputs;
        break;
    case PortDirection::OUT:
        return outputs;
        break;
    default:
        return 0;
    }
}




// void DataAbstractModule::appendChild ( DataAbstractItem *item ) {
//   qDebug() << __PRETTY_FUNCTION__;
//     if ( item->parent() != this ) {
//         qDebug ( "ERROR: you can't add a child to a parent item where \
//             the parent of the child doesn't match the parent you want to add it to!" );
//         return;
//     }
// 
// //     this is the inverted connection item: r_item
// //     DataPort* p = static_cast<DataPort*> ( item );
// 
// // //     0. check if allowed (no loops to the same item)
// //     if ( ! ( c->validate() ) ) {
// //         qDebug() << __PRETTY_FUNCTION__ << "item not valid";
// //         return;
// //     }
// //     if ( c->srcType ( this ) == PortType::OUTPUT ) {
// //         insertConnection ( c );
// //         return;
// //     } else {
// //         DataAbstractModule* dstItem = static_cast<DataAbstractModule*> ( c->dst ( this ) );
// //         dstItem->insertConnection ( c );
// //         return;
// //     }
// //     
// }

// bool DataAbstractModule::isPortUsed(DataAbstractItem *item) {
// //   qDebug() << __PRETTY_FUNCTION__;
// //   DataConnection* c = static_cast<DataConnection*> ( item );
// //     // a. copy all 'references' into a list
// //     // b. remove all 'outputs' from that list
// //     // c. filter all items except those with dstType, 
// //     //    now search for an item with known portnumber, 
// //     //    if item is found 'return false'
// //     foreach(DataAbstractItem* ref, m_childItemsReferences) {
// //       DataConnection* r = static_cast<DataConnection*> ( ref );
// //       if ((c->srcType(this) == r->srcType(this)) && (c->srcPortNumber(this) == r->srcPortNumber(this)))
// //         return true;
// //     }
// //     
//     return false;
// }

