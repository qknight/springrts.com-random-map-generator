// automate implements an automate class in c++ using qt4
// Copyright (C) 2007 Joachim Schiele
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 3 as published by the Free Software Foundation
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

/**
  @author Joachim Schiele <js@lastlog.de>
*/

#include <QVector>
#include <QColor>
#include <QBrush>
#include <QDebug>
#include <QIcon>
#include <QVariant>

#include "Model.h"
#include "Document.h"
#include "DataRoot.h"
#include "DataAbstractItem.h"
#include "DataPort.h"
#include "DataProperty.h"
#include "DataConnection.h"
#include "DataAbstractModule.h"
#include "ModuleFactory.h"

Model::Model() {
    rootItem = new DataRoot;
    moduleFactory = ModuleFactory::Instance();
//     moduleFactory->ListLoadableModules();
}

Model::~Model() {
//     qDebug() << __PRETTY_FUNCTION__;
    // we assume that if this function is called, no views are attached anymore
    delete static_cast<DataRoot*> (rootItem);
}

QModelIndex Model::index( int row, int column, const QModelIndex & parent ) const {
    /*
    index()
     Given a model index for a parent item, this function allows views
     and delegates to access children of that item. If no valid child item -
     corresponding to the specified row, column, and parent model index,
     can be found, the function must return QModelIndex(), which is an invalid
     model index.
    */
//     qDebug() << "index(" << row <<", " <<column<<")";

    if ( !hasIndex( row, column, parent ) )
        return QModelIndex();

    DataAbstractItem* parentItem;

    //BUG, parent is never valid
    if ( !parent.isValid() )
        parentItem = rootItem;
    else {
        parentItem = static_cast<DataAbstractItem*>( parent.internalPointer() );
    }
    DataAbstractItem* childItem = parentItem->child( row );
//     qDebug() << "index: parentItem==" << (unsigned int) parentItem;
//     qDebug() << "index:  childItem==" << (unsigned int) childItem;

    if ( childItem ) {
//       qDebug() << "createIndex(" << row << ", " << column << ", " << (unsigned int) childItem << ");";
        return createIndex( row, column, childItem );
    }

//     qDebug() << "invalid";
    return QModelIndex();
}

QModelIndex Model::parent( const QModelIndex & child ) const {
    /*
    parent()
      Provides a model index corresponding to the parent of any given child item.
      If the model index specified corresponds to a top-level item in the model,
      or if there is no valid parent item in the model, the function must return
      an invalid model index, created with the empty QModelIndex() constructor.
    */
    // fall 1: parentitem fuer invalid
//       qDebug() << "parent ";
//  << QString("%1").arg((unsigned int) child);

    if ( !child.isValid() ) {
        return QModelIndex();
    }
//     qDebug() << "parent2or3";

    DataAbstractItem *childItem =
        static_cast<DataAbstractItem*>( child.internalPointer() );
    DataAbstractItem *parentItem = childItem->parent();

// fall 2: parentitem fuer rootItem
//   if ( parentItem == NULL )
//     return QModelIndex();

    if ( parentItem == rootItem )
        return QModelIndex();

// fall 3: parentitem fuer alle anderen
//     return index(r,c,parent model index);
    return createIndex( parentItem->row(), 0, parentItem );
}

/*!
** this code should be read as table of generic cases (where row/column doesn't matter)
** which is important for the graphicsView. for the treeView there is a part of code where
** row/column matters, see the very long switch statement.
*/
QVariant Model::data( const QModelIndex &index, int role ) const {
//   qDebug() << __FUNCTION__;
    if ( !index.isValid() )
        return QVariant();

    DataAbstractItem* n = static_cast<DataAbstractItem*>( index.internalPointer() );
    //   // to understand customRole::TypeRole see the comment (Model.h - DataItemType enum comment )
    if ( role == customRole::TypeRole ) {
        if ( n->getObjectType() == DataItemType::DATAROOT )
            return DataItemType::DATAROOT;
        if ( n->getObjectType() == DataItemType::DATACONNECTION )
            return DataItemType::DATACONNECTION;
        if ( n->getObjectType() == DataItemType::DATAPROPERTY )
            return DataItemType::DATAPROPERTY;
        if ( n->getObjectType() == DataItemType::DATAABSTRACTMODULE )
            return DataItemType::DATAABSTRACTMODULE;
        if ( n->getObjectType() == DataItemType::DATAPORT )
            return DataItemType::DATAPORT;
        return DataItemType::DATAUNKNOWN;
    }
    if ( role == customRole::PortType ) {
        DataPort* p = static_cast<DataPort*>(n);
        return p->PortType();
    }
    if ( role == customRole::PortDirection ) {
        DataPort* p = static_cast<DataPort*>(n);
        return p->PortDirection();
    }
    if ( role == customRole::PortNumber ) {
        DataPort* p = static_cast<DataPort*>(n);
        return p->PortNumber();
    }

    if ( role == Qt::BackgroundRole) {
        if ( n->getObjectType() == DataItemType::DATAABSTRACTMODULE )
            return QBrush( QColor( 0, 23, 253, 255 ) );
        if ( n->getObjectType() == DataItemType::DATAPROPERTY )
            return QBrush( QColor( 255, 255, 191, 100 ));
    }

    switch ( index.column() ) {
    case 0:
        switch ( role ) {
        case Qt::DecorationRole:
        case customRole::SortRole:
        case Qt::DisplayRole:
            if ( n->getObjectType() == DataItemType::DATAABSTRACTMODULE ) {
                DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
                return am->identify();
            }
            if ( n->getObjectType() == DataItemType::DATACONNECTION )
                return "connection";
            if ( n->getObjectType() == DataItemType::DATAPORT )
                return "port";
            if ( n->getObjectType() == DataItemType::DATAPROPERTY ) {
                DataProperty* p = dynamic_cast<DataProperty*>(n);
                return p->key();
            }
        }
        break;
    case 1:
        switch (role) {
        case Qt::DisplayRole:
            if ( n->getObjectType() == DataItemType::DATAPROPERTY ) {
                DataProperty* p = dynamic_cast<DataProperty*>(n);
                return p->value();
            }
            break;
        default:
            break;
        }
    }

    if ( role == customRole::PosRole )
        if ( n->getObjectType() == DataType::MODULE ) {
            DataAbstractModule* m = dynamic_cast<DataAbstractModule*>(n);
            return m->property("pos");
        }



//   if ( role == customRole::SymbolIndexRole )
//     if ( n->getObjectType() == NODE_CONNECTION ) {
//       DataConnection* nc = static_cast<DataConnection*>( index.internalPointer() );
// //       qDebug() << __FUNCTION__ << symbol( nc->symbol_index ) << nc->symbol_index;
//       return symbol( nc->symbol_index() ) ;
//     }
//   if ( role == customRole::IdRole )
//     if ( n->getObjectType() == NODE || n->getObjectType() == NODE_CONNECTION )
//       return n->getId();
//   switch ( index.column() ) {
//   case 0:
//     switch ( role ) {
//     case Qt::DecorationRole:
//       if ( n->getObjectType() == NODE )
//         return QIcon( ":/icons/node.png" );
//       if ( n->getObjectType() == NODE_CONNECTION )
//         return QIcon( ":/icons/connect.png" );
//     }
//     break;
//   case 1:
//     switch ( role ) {
//     case Qt::ToolTipRole:
//       break;
//     case Qt::WhatsThisRole:
//       break;
//     case Qt::TextAlignmentRole:
// //           if (index.column() == 1)
// //             return Qt::AlignHCenter;
// //           if (index.column() == 2)
// //             return Qt::AlignHCenter;
//       break;
//     case customRole::SortRole:
//     case Qt::DecorationRole:
//       if ( n->getObjectType() == NODE ) {
//         if ( n->getProperty( "start" ).toBool() ) {
//           if ( role == customRole::SortRole )
//             return 1;
//           return QIcon( ":/icons/startNode.png" );
//         } else {
//           if ( role == customRole::SortRole )
//             return 0;
//         }
//       }
//       break;
// //     case Qt::BackgroundRole:
// //       break;
//     }
//     break;
//   case 2:
//     switch ( role ) {
//     case customRole::SortRole:
//     case Qt::DecorationRole:
//       if ( n->getObjectType() == NODE ) {
//         if ( n->getProperty( "final" ).toBool() ) {
//           if ( role == customRole::SortRole )
//             return 1;
//           return QIcon( ":/icons/finalNode.png" );
//         } else {
//           if ( role == customRole::SortRole )
//             return 0;
//         }
//       }
//       break;
//     }
//     break;
//   case 3:
//     switch ( role ) {
//     case customRole::SortRole:
//     case Qt::DisplayRole:
//       if ( n->getObjectType() == NODE ) {
//         if ( role == customRole::SortRole ) {
//           return n->getId();
//         }
//         if ( role == Qt::DisplayRole )
//           return QString( "n%1" ).arg( n->getId() );// "node";
//       }
//       if ( n->getObjectType() == NODE_CONNECTION ) {
//         if ( role == customRole::SortRole )
//           return n->getId();
//         if ( role == Qt::DisplayRole )
//           return QString( "c%1" ).arg( n->getId() );// "DataConnection";
//       }
//       break;
//     }
//   case 4:
//     switch ( role ) {
//     case customRole::SortRole:
//     case Qt::DisplayRole:
//       if ( n->getObjectType() == NODE_CONNECTION ) {
//         if ( role == customRole::SortRole )
//           return ( static_cast<DataConnection*>( n ) )->symbol_index();// "DataConnection";
//         if ( role == Qt::DisplayRole )
//           return symbol(( static_cast<DataConnection*>( n ) )->symbol_index() );// "DataConnection";
//       }
//     }
//
//     break;
//   case 5:
//     switch ( role ) {
//     case Qt::BackgroundRole:
//       if ( n->getObjectType() == NODE_CONNECTION )
//         if ((static_cast<DataConnection*>( n ) )->next_node() == NULL)
//           return QBrush( QColor( 255, 0, 0, 250 ) );
//       break;
//     case customRole::SortRole:
//     case Qt::DisplayRole:
//       if ( n->getObjectType() == NODE_CONNECTION ) {
//         if ((static_cast<DataConnection*>( n ) )->next_node() == NULL)
//           return "undefined";
//         DataAbstractItem* next_node = ( static_cast<DataConnection*>( n ) )->next_node();
//         if ( role == customRole::SortRole )
//           return next_node->getId();// "DataConnection";
//         if ( role == Qt::DisplayRole )
//           return QString( "n%1" ).arg( next_node->getId() );// "DataConnection";
//       }
//     }
//     break;
//   case 6:
//     if ( role == Qt::DisplayRole ) {
//       return n->getProperty( "CustomLabelRole" );
//     }
//     break;
//     /*  case 7:
//         break;*/
//   }
//   if ( role == Qt::BackgroundRole ) {
//     if ( n->getObjectType() == NODE )
//       return QBrush( QColor( 50, 160, 170, 150 ) );
//     if ( n->getObjectType() == NODE_CONNECTION )
//       return QBrush( QColor( 180, 200, 200, 50 ) );
//   }
    return QVariant();
}

bool Model::setData( const QModelIndex & index, const QVariant & value, int role ) {
    if (!index.isValid())
        return false;

    //editing properties using the QTreeView
    DataAbstractItem* item = static_cast<DataAbstractItem*>( index.internalPointer() );
    if (item->getObjectType() == DataItemType::DATAPROPERTY && index.column() == 1 && role == Qt::EditRole) {
      DataProperty* p = static_cast<DataProperty*>(item);
      p->setValue(value);
      emit dataChanged(index,index);
      return true;
    }

    return false;
}

/*! used by the table view */
QVariant Model::headerData( int section, Qt::Orientation orientation, int role ) const {
    if ( orientation == Qt::Horizontal && ( role == Qt::DisplayRole || role == Qt::ToolTipRole ) ) {
        switch ( section ) {
        case 0:
            if ( role == Qt::DisplayRole )
                return "key";
            else
                if ( role == Qt::ToolTipRole )
                    return "FIXME";
        case 1:
            if ( role == Qt::DisplayRole )
                return "value";
            else
                if ( role == Qt::ToolTipRole )
                    return "FIXME";
        }
    }
    return QVariant();
}

int Model::rowCount( const QModelIndex & sibling ) const {
// returns how many siblings this "sibling" node has
    DataAbstractItem *parentItem;

    if ( sibling.column() > 0 ) {
//       qDebug() << "rowcount=0";
        return 0;
    }

    if ( !sibling.isValid() )
        parentItem = rootItem;
    else
        parentItem = static_cast<DataAbstractItem*>( sibling.internalPointer() );

//     qDebug() << "rowcount="<<parentItem->childCount();
    return parentItem->childCount();
}

int Model::columnCount( const QModelIndex & /*parent*/ ) const {
    return 2;
}

//FIXME CRITICAL: implement removal of MODULEs, PORTs, CONNECTIONs
bool Model::removeRows( int row, int count, const QModelIndex & parent ) {
//   qDebug() << "want to remove " << count << " item(s) beginning at row " << row;
//     DataAbstractItem* abstractitem;
//     if ( !parent.isValid() ) {
//         abstractitem = rootItem;
//     } else {
//         abstractitem = static_cast<DataAbstractItem*>( parent.internalPointer() );
//     }
//
// //   qDebug() << "The id of the object to delete is id::" << abstractitem->getId();
//     int from_row = row;
//     int to_row = row + count - 1;
// //   qDebug() << "  beginRemoveRows(parent, row_first, row_last);" << from_row << " " <<  to_row;
//     beginRemoveRows( parent, from_row, to_row );
//     {
//         int i = count;
//         // FIXME deleting could be speeded up by better code design here
//         while ( i-- )
//             abstractitem->removeChild( row );
//     }
//     endRemoveRows();
//     return true;
}

bool Model::hasChildren ( const QModelIndex & parent ) const {
//   qDebug() << "one is calling me" << __FUNCTION__;
    if (!parent.isValid())
        return true;
    DataAbstractItem* item = static_cast<DataAbstractItem*>( parent.internalPointer() );
    if (item->childCount() > 0)
        return true;
    return false;
}

/*! relevant for the 'QTreeView': is item selectable? is item editable? */
Qt::ItemFlags Model::flags( const QModelIndex & index ) const {
    // if index is invalid
    if ( !index.isValid() )
        return 0;

    DataAbstractItem* item = static_cast<DataAbstractItem*>( index.internalPointer() );
    if (item->getObjectType() == DataItemType::DATAABSTRACTMODULE)
        return /*Qt::ItemIsSelectable|*/Qt::ItemIsEnabled;

    if (item->getObjectType() == DataItemType::DATAPROPERTY && index.column() == 1) {
        return Qt::ItemIsEditable|Qt::ItemIsEnabled;
    }

    //default
    return 0;
}

bool Model::insertRows( int row, int count, const QModelIndex & parent, QPoint pos, QString type ) {
    // this function is not used, see
    //  - insertModule
    //  - insertConnection
    //  instead
    return false;
}

QModelIndex Model::insertModule(QString type, QPoint pos) {
    int row = rowCount( QModelIndex() );

    // this will also add module specific properties
    DataAbstractModule* module = moduleFactory->CreateModule(type);

    // add properties every module has
    module->setProperty("pos", pos);

    // setting the correct parent is very important since it is the foundation of the hierarchy
    module->setParent( rootItem );
    beginInsertRows( QModelIndex(), row, row + 0 );
    {
        if (module != NULL) {
            rootItem->appendChild( module );

            for (int i = 0; i < module->ports(PortDirection::IN); ++i) {
                DataPort* p = new DataPort(PortType::LIBNOISE, PortDirection::IN, i);
                DataAbstractItem* portItem = dynamic_cast<DataAbstractItem*>(p);
                portItem->setParent(module);
                module->appendChild(portItem);
            }
            for (int i = 0; i < module->ports(PortDirection::MOD); ++i) {
                DataPort* p = new DataPort(PortType::LIBNOISE, PortDirection::MOD, i);
                DataAbstractItem* portItem = dynamic_cast<DataAbstractItem*>(p);
                portItem->setParent(module);
                module->appendChild(portItem);
            }
            for (int i = 0; i < module->ports(PortDirection::OUT); ++i) {
                DataPort* p = new DataPort(PortType::LIBNOISE, PortDirection::OUT, i);
                DataAbstractItem* portItem = dynamic_cast<DataAbstractItem*>(p);
                portItem->setParent(module);
                module->appendChild(portItem);
            }
        } else {
            qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: in insertRows(), exiting";
            exit(1);
        }
    }
    endInsertRows();
    return index(row, 0, QModelIndex());
}

/*!
 * this could be read as:
 *  - insertConnection(Port* a, Port* b); or
 *  - insertConnection(DataPort* a, DataPort* b);
 * WARNING: - only add/remove connections using insertConnection and removeConnection
 *          - when removing a module using removeModule(..) ensure that removeModule(..) deletes
 *            all connections and then all ports before said module is removed
 * very important design goals:
 * - connections can only be bidirectional (between exactly two ports)
 * - no loops
 * - output ports might be used several times, when hosting connections to different 'other ports'
 * - in contrast: input-ports or modput-ports may only host one connection each
 * - connections must be unique (there can not be two similar connections connecting portX and portY)
 * - a connection is added to it's parent. the parent is always the port with portType=OUT
*/
QModelIndex Model::insertConnection(QPersistentModelIndex a,
                                    QPersistentModelIndex b) {
//     qDebug() << __PRETTY_FUNCTION__;

    // convert both indexes into DataAbstractItem(s)
    DataAbstractItem* abstractItemA = static_cast<DataAbstractItem*>( a.internalPointer() );
    DataAbstractItem* abstractItemB = static_cast<DataAbstractItem*>( b.internalPointer() );

    // check if both are ports
    if (abstractItemA->getObjectType() != DataItemType::DATAPORT ||
            abstractItemB->getObjectType() != DataItemType::DATAPORT) {
        qDebug() << __PRETTY_FUNCTION__ << "error: both items must be ports, if you want to add a connection to";
        return QModelIndex();
    }

    // convert both indexes into DataPortItem(s)
    DataPort* dataPortA = dynamic_cast<DataPort*>(abstractItemA);
    DataPort* dataPortB = dynamic_cast<DataPort*>(abstractItemB);

    // for debugging purpose (WARNING: elements might be flipped later)
//     qDebug() << "port syntax is: type, number, direction";
//     qDebug() << dataPortA->PortType() << dataPortA->PortNumber()  << dataPortA->PortDirection();
//     qDebug() << dataPortB->PortType() << dataPortB->PortNumber()  << dataPortB->PortDirection();

    // 1. check if the ports are of compatible types
    if (dataPortA->PortType() != dataPortB->PortType()) {
        qDebug() << "both ports need to be of compatible type, for example: PortType::LIBNOISE -- PortType::LIBNOISE";
        return QModelIndex();
    }

    // 2. check if a connection is possible implementing the connection matrix below
    // invalid connections
    // - x not possible
    // - o possible
    //      in  out  mod
    // in   x   o    x
    // out  o   x    o
    // mod  x   o    x

    // we need 3 blocking rules to implement the above diagramm (all other cases will pass)
    //   1. rule
    if (dataPortA->PortDirection() == dataPortB->PortDirection()) {
        qDebug() << "RULE1: PortA must have a different PortDirection than PortB";
        return QModelIndex();
    }
    //   2. rule
    if ((dataPortA->PortDirection() == PortDirection::MOD) && (dataPortB->PortDirection() == PortDirection::IN)) {
        qDebug() << "RULE2a: can't add connection between MOD and IN";
        return QModelIndex();
    }
    //   3. rule
    if ((dataPortA->PortDirection() == PortDirection::IN) && (dataPortB->PortDirection() == PortDirection::MOD)) {
        qDebug() << "RULE2b: can't add connection between IN and MOD";
        return QModelIndex();
    }

    // 3. we swap a and b if dataPortB is the 'OUT' port
    if (dataPortA->PortDirection() == PortDirection::OUT) {
        // do nothing
    } else {
        // swap both objects
        DataAbstractItem* tmp = abstractItemA;
        abstractItemA = abstractItemB;
        abstractItemB = tmp;

        DataPort* tmp2 = dataPortA;
        dataPortA = dataPortB;
        dataPortB = tmp2;

        QModelIndex tmpIndex = a;
        a=b;
        b=tmpIndex;
    }

    // 4. check if such a connection already exists
    for (int i = 0; i < dataPortA->childCount(); ++i) {
        if (dataPortA->childItems()[i]->getObjectType() != DataItemType::DATAPORT)
            continue;
        DataConnection* childConnection = static_cast<DataConnection*>(dataPortA->childItems()[i]);
        if (childConnection->dst() == abstractItemB) {
            qDebug() << "rule 4: there is already a connection, can't connect the same port pairs twice";
            return QModelIndex();
        }
    }

    // 5. check if a modput/input port is already in use
    if (dataPortB->referenceCount() > 0) {
        qDebug() << "rule 5: remote input/modput port already in use, not adding another connection";
        return QModelIndex();
    }

    // 6. check if there is a loop, moduleA -- moduleB - .. - moduleA
    //    since loops are not allowed, checking for possible loops, when adding a new connection, is mandatory.
    //    - this function checks only for loops which 'would' be added with this 'connection'
    //    - the graph MUST NOT yet contain loops (added prior to 'adding this connection')
    // would create a loop if we can find a way (only traverse outputs) from abstractItemB to abstractItemA
    QVector<DataAbstractItem*> visited;
    QVector<DataConnection*> connections;
    DataAbstractModule* m = static_cast<DataAbstractModule*>(abstractItemB->parent());
    visited << abstractItemA->parent();
    visited << abstractItemB->parent();

    if (abstractItemA->parent() == abstractItemB->parent()) {
        qDebug() << "check 6: a loop within one module is not allowed";
        return QModelIndex();
    }
//     qDebug()<< "check 6: START: loop detection running";
    do {
//         qDebug() << "check 6: main loop started";
        // loop through all output ports
        for (int i = 0; i < m->childCount(); ++i) {
//             qDebug()<< "check 6: m->childCount()" << i;
            // loop through all connections
            DataAbstractItem* childItem = m->childItems()[i];
            if (childItem->getObjectType() != DataItemType::DATAPORT)
                continue;

            DataPort* p = static_cast<DataPort*>(childItem);
            if (p->PortDirection() != PortDirection::OUT) {
                continue;
            }
            for (int j = 0; j < childItem->childCount(); ++j) {
//                 qDebug()<< "check 6: processing output connection: " << j;
                if (childItem->childItems()[j]->getObjectType() != DataItemType::DATAPORT)
                    continue;

                DataConnection* c = static_cast<DataConnection*> (childItem->childItems()[j]);
                connections << c;
            }
        }
//         qDebug() << "check 6: " << "connections.size(): " << connections.size();
        if (connections.size() == 0) {
            break;
        } else {
            DataConnection* c = connections.at(0);
            connections.remove(0);
            m = static_cast<DataAbstractModule*>(c->dst()->parent());
            if (visited.contains(m)) {
//                 qDebug() << "check 6: visited.size(): " << visited.size();
                qDebug() << "check 6: adding this connection would create a loop which is not allowed by definition!";
                return QModelIndex();
            }
            visited << m;
        }
    } while (true);
//     qDebug() << "check 6: END loop detection: NO LOOP";

    // 7. create the new connection
    DataConnection* dc = new DataConnection( abstractItemA, abstractItemB );

    // 8. finally (after changing the core data structure using the Model) we are
    //    going to update the QGraphicsScene via the QAbstractItemModel -> insert the connection
    int row = rowCount( a );
    beginInsertRows( a, row, row + 0 );
    {
        dc->setParent(abstractItemA);
        abstractItemA->appendChild( dc );
    }
    endInsertRows();
//     qDebug() << "successfully added a new connection";
    return index(row, 0, a);
}

QVector<QString> Model::LoadableModuleNames() {
    return moduleFactory->LoadableModuleNames();
}

/*!
 * called with a item where item is a QModelIndex representing a connection
 * returns the QModelIndex of the connection's destination port
 */
QModelIndex Model::dst(QPersistentModelIndex connection) {
    // 0. check if item is a 'connection'
    if (data( connection, customRole::TypeRole ).toInt() != DataType::CONNECTION) {
        qDebug() << __PRETTY_FUNCTION__ << " fatal error: item is not a connection";
        exit(1);
    }

    DataAbstractItem* src = static_cast<DataAbstractItem*> (connection.internalPointer());
    // 1. now resolve the connection into a DataConnection
    DataConnection* c = static_cast<DataConnection*> (src);

    // 2. src ----connection----- dst
    DataAbstractItem* dPortItem = c->dst();

    // 3. the parent QModelIndex is important for the last step
    QModelIndex parentModule = index(dPortItem->parent()->row(), 0 , QModelIndex());

    // 4. now we need to find the QModelIndex of dst (dst is a DataPort)
    return index(dPortItem->row(),0 , parentModule);
}


