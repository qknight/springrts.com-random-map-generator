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
#include "DataConnection.h"
#include "DataAbstractModule.h"
#include "ModuleFactory.h"

Model::Model( /*DataAbstractItem* root, QObject* parent*/ ) /*: QAbstractItemModel( parent )*/ {
    rootItem = new DataRoot;
    moduleFactory = ModuleFactory::Instance();
    moduleFactory->ListLoadableModules();
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
        if ( n->getObjectType() == DataItemType::DATAABSTRACTMODULE )
            return DataItemType::DATAABSTRACTMODULE;
        if ( n->getObjectType() == DataItemType::DATAPORT )
            return DataItemType::DATAPORT;
        return DataItemType::UNKNOWN;
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
        }
        break;
    }

//   if ( role == customRole::CustomLabelRole )
//     return n->getProperty( "CustomLabelRole" );

    if ( role == customRole::PosRole )
        if ( n->getObjectType() == DataType::MODULE )
            return n->property( "pos" );

//   if ( role == customRole::InputsRole )
//     if ( n->getObjectType() == DataType::MODULE ) {
//
//       DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
//       return am->ports(PortType::INPUT);
//     }
//   if ( role == customRole::ModputsRole )
//     if ( n->getObjectType() == DataType::MODULE ) {
//       DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
//       return am->ports(PortType::MODPUT);
//     }
//   if ( role == customRole::OutputsRole )
//     if ( n->getObjectType() == DataType::MODULE ) {
//       DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
//       return am->ports(PortType::OUTPUT);
//     }
//
//   // seen from the connection's parent this 4 functions are used to query portnumber and porttype
//   if ( role == customRole::SrcPortNumberRole)
//     if ( n->getObjectType() == DataType::CONNECTION ) {
//       DataConnection* c = static_cast<DataConnection*>(n);
//       DataAbstractModule* m = static_cast<DataAbstractModule*>(index.parent().internalPointer());
// //       qDebug() << " src  " << c->srcPortNumber(m) << " dst" << c->dstPortNumber(m);
//       return c->srcPortNumber(m);
//     }
//   if ( role == customRole::SrcPortTypeRole)
//     if ( n->getObjectType() == DataType::CONNECTION ) {
//       DataConnection* c = static_cast<DataConnection*>(n);
//       DataAbstractModule* m = static_cast<DataAbstractModule*>(index.parent().internalPointer());
//       return c->srcType(m);
//     }
//   if ( role == customRole::DstPortNumberRole)
//     if ( n->getObjectType() == DataType::CONNECTION ) {
//       DataConnection* c = static_cast<DataConnection*>(n);
//       DataAbstractModule* m = static_cast<DataAbstractModule*>(index.parent().internalPointer());
//       return c->dstPortNumber(m);
//     }
//   if ( role == customRole::DstPortTypeRole)
//     if ( n->getObjectType() == DataType::CONNECTION ) {
//       DataConnection* c = static_cast<DataConnection*>(n);
//       DataAbstractModule* m = static_cast<DataAbstractModule*>(index.parent().internalPointer());
//       return c->dstType(m);
//     }




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
    qDebug() << "setData " << index.column();
//   if (( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && index.column() == 4 && role == Qt::EditRole ) ||
//       ( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && role == customRole::SymbolIndexRole ) ) {
//     DataAbstractItem* n = static_cast<DataAbstractItem*>( index.internalPointer() );
//     DataConnection* nc = static_cast<DataConnection*>( n );
// //     nc->setSymbol_index( symbol( value.toString() ) );
// //     qDebug() << __FUNCTION__ << value.toString() << " " << nc->symbol_index() << " " << symbol( nc->symbol_index() );
//     emit dataChanged( index, index );
//     return true;
//   }
//   // this code is used to redirect a DataConnection's destination (source is fixed to the node the
//   // DataConnection is assigned to). if one would not have unique IDs then it would be impossible
//   // to use a number to match a node with. say a DataConnection connects from (source node id=2) to
//   // (destination node id=4), the code below let's you use the TreeView editor to redirect it to (say node id=7)
//   // if 7 exists
//   if ( index.isValid() && getTreeItemType( index ) == NODE_CONNECTION && index.column() == 5 && role == Qt::EditRole ) {
//     DataAbstractItem* n = static_cast<DataAbstractItem*>( index.internalPointer() );
//     DataConnection* nc = static_cast<DataConnection*>( n );
//     DataAbstractItem* a = DataAbstractItemFromId( value.toInt() );
//     if ( a == NULL ) {
//       qDebug() << "can't redirect connection because the given node id was not found in the graph, please try again later!";
//       return false;
//     }
//     nc->setNext_node( a );
//     emit dataChanged( index, index );
//     return true;
//   }
//   if (( index.isValid() && index.column() == 6 && role == Qt::EditRole ) ||
//       ( index.isValid() && role == customRole::CustomLabelRole ) ) {
//     DataAbstractItem* nItem = static_cast<DataAbstractItem*>( index.internalPointer() );
//     nItem->setProperty( "CustomLabelRole", value );
//     emit dataChanged( index, index );
//     return true;
//   }
//
//   if ( index.isValid() && getTreeItemType( index ) == NODE && (( role == customRole::StartRole ) || role == customRole::FinalRole ) ) {
//     DataAbstractItem* n = static_cast<DataAbstractItem*>( index.internalPointer() );
//     QModelIndex correctedIndex;
//     if ( role == customRole::StartRole ) {
//       n->setProperty( "start", value );
//       correctedIndex = Model::index( index.row(), 1, index.parent() );
//     }
//     if ( role == customRole::FinalRole ) {
//       n->setProperty( "final", value );
//       correctedIndex = Model::index( index.row(), 2, index.parent() );
//     }
//     emit dataChanged( correctedIndex, correctedIndex );
//     return true;
//   }
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
    DataAbstractItem* abstractitem;
    if ( !parent.isValid() ) {
        abstractitem = rootItem;
    } else {
        abstractitem = static_cast<DataAbstractItem*>( parent.internalPointer() );
    }

//   qDebug() << "The id of the object to delete is id::" << abstractitem->getId();
    int from_row = row;
    int to_row = row + count - 1;
//   qDebug() << "  beginRemoveRows(parent, row_first, row_last);" << from_row << " " <<  to_row;
    beginRemoveRows( parent, from_row, to_row );
    {
        int i = count;
        // FIXME deleting could be speeded up by better code design here
        while ( i-- )
            abstractitem->removeChild( row );
    }
    endRemoveRows();
    return true;
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

Qt::ItemFlags Model::flags( const QModelIndex & index ) const {
    //FIXME only make setData able fields editable
//   if ( !index.isValid() )
    return 0;
    return QAbstractItemModel::flags( index ) | Qt::ItemIsEditable;
}

bool Model::insertRows( int row, int count, const QModelIndex & parent, QPoint pos, QString type ) {
    // this function is not used, use
    //  - insertModule
    //  - insertPort
    //  - insertConnection
    //  instead
    return false;
}

bool Model::insertModule(QString type, QPoint pos) {
    int row = rowCount( QModelIndex() );

    // no valid parent -> it's a Module to add as for instance (NoiseGenBillow)
    DataAbstractModule* module = moduleFactory->CreateModule(type);

    //FIXME this should go into a child item of module called property
    //      which should be in the same hierarchy level as the DataPort item
    module->setProperty( "pos", pos );
    module->setProperty( "type", type );
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
    return true;
}

/*!
 * this could be read as:
 *  - insertConnection(Port* a, Port* b); or
 *  - insertConnection(DataPort* a, DataPort* b);
 * WARNING: only add/remove connections using insertConnection and removeConnection
 * very important design goals:
 * - connections can only be bidirectional (between exactly two ports)
 * - no loops
 * - output ports might be used several times, when hosting connections to different 'other ports'
 * - in contrast: input-ports or modput-ports may only host one connection each
 * - connections must be unique (there can not be two similar connections connecting portX and portY)
 * - a connection is added to it's parent. the parent is always the port with portType=OUT
*/
bool Model::insertConnection(QPersistentModelIndex a,
                             QPersistentModelIndex b) {
    qDebug() << __PRETTY_FUNCTION__;

    // convert both indexes into DataAbstractItem(s)
    DataAbstractItem* abstractItemA = static_cast<DataAbstractItem*>( a.internalPointer() );
    DataAbstractItem* abstractItemB = static_cast<DataAbstractItem*>( b.internalPointer() );

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
        return false;
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
        return false;
    }
    //   2. rule
    if ((dataPortA->PortDirection() == PortDirection::MOD) && (dataPortB->PortDirection() == PortDirection::IN)) {
        qDebug() << "RULE2a: can't add connection between MOD and IN";
        return false;
    }
    //   3. rule
    if ((dataPortA->PortDirection() == PortDirection::IN) && (dataPortB->PortDirection() == PortDirection::MOD)) {
        qDebug() << "RULE2b: can't add connection between IN and MOD";
        return false;
    }

    // 3. check if such a connection already exists
    //FIXME: implement this rule set
    qDebug() << "FIXME: " << __FILE__ << __PRETTY_FUNCTION__ << ", see check 3: check if such a connection already exists";

    // 4. create the new connection (maybe only temporarily, see check 5)
    // we flip a and b if dataPortB is the 'OUT' port
    if (dataPortA->PortDirection() == PortDirection::OUT) {
        // do nothing
    } else {
        // flip a and b
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

    DataConnection* dc = new DataConnection( abstractItemA, abstractItemB );

    // 5. test here if the connection is accepted by the modules (ask both modules)
    //FIXME: this code is currenlty not used but can be used later
//     DataAbstractModule* srcModule = static_cast<DataAbstractModule*>( srcItem );
//     DataAbstractModule* dstModule = static_cast<DataAbstractModule*>( dstItem );
//     if (srcModule->verifyConnection(dc) && dstModule->verifyConnection(dc)) {
//       delete dc;
//       return false;
//     }

    // 6. finally (after changing the core data structure using the Model) we are
    //    going to update the QGraphicsScene via the QAbstractItemModel -> insert the connection
    int row = rowCount( a );
    beginInsertRows( a, row, row + 0 );
    {
        dc->setParent(abstractItemA);
        abstractItemA->appendChild( dc );
    }
    endInsertRows();
    qDebug() << "successfully added a new connection";
    return true;
}

QVector<QString> Model::LoadableModuleNames() {
    return moduleFactory->LoadableModuleNames();
}

// QModelIndex Model::AbstractNodeItem2QModelIndex( DataAbstractItem* item ) {
//   QModelIndex ret;
//   QModelIndex z;
//   switch ( item->getObjectType() ) {
//     case DataItemType::DATAROOT:
//     break;
//   case DataItemType::DATAABSTRACTMODULE:
//     ret = index( item->row(), 0, QModelIndex() );
//     return ret;
//   case DataItemType::DATAPORT:
//   case DataItemType::DATACONNECTION:
//     z = AbstractNodeItem2QModelIndex( item->parent() );
//     ret = index( item->row(), 0, z );
//     return ret;
//     break;
//   default:
//     qDebug() << "In " << __FILE__ << ", " << __FUNCTION__ << " something went very wrong!";
//     exit( 0 );
//   }
//   return QModelIndex();
// }



/*!
 * called with a item where item is a QModelIndex representing a connection
 */
// QModelIndex Model::dst(QPersistentModelIndex item) {
//     // 0. check if item is a 'connection'
//     if (data( item, customRole::TypeRole ).toInt() != DataType::CONNECTION) {
//         qDebug() << __PRETTY_FUNCTION__ << " fatal error: item is not a connection";
//         exit(1);
//     }
//
//     DataAbstractItem* src = static_cast<DataAbstractItem*> (item.internalPointer());
//     // 1. now resolve the connection into a DataConnection
//     DataConnection* c = static_cast<DataConnection*> (src);
//
//     // 2. finally query c->dst with it's parent
//     DataAbstractItem* dst = c->src(src->parent());
//     return index(dst->row(),0, QModelIndex());
// }




