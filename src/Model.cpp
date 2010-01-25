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
    return DataItemType::UNKNOWN;
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
    }
    break;
  }

//   if ( role == customRole::CustomLabelRole )
//     return n->getProperty( "CustomLabelRole" );

  if ( role == customRole::PosRole )
    if ( n->getObjectType() == DataType::MODULE )
      return n->property( "pos" );
  if ( role == customRole::InputsRole )
    if ( n->getObjectType() == DataType::MODULE ) {

      DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
      return am->ports(PortType::INPUT);
    }
  if ( role == customRole::ModputsRole )
    if ( n->getObjectType() == DataType::MODULE ) {
      DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
      return am->ports(PortType::MODPUT);
    }
  if ( role == customRole::OutputsRole )
    if ( n->getObjectType() == DataType::MODULE ) {
      DataAbstractModule* am = dynamic_cast<DataAbstractModule*>(n);
      return am->ports(PortType::OUTPUT);
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

bool Model::insertRows( int row, int count, const QModelIndex & parent, QPoint pos, QString type ) {
  // this function is not used, use insertModule and insertConnection instead
}

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

bool Model::insertModule(QString type, QPoint pos) {
  int row = rowCount( QModelIndex() );

  // no valid parent -> it's a Module to add as for instance (NoiseGenBillow)
    beginInsertRows( QModelIndex(), row, row + 0 );
    {
      DataAbstractModule* module = moduleFactory->CreateModule(type);
//       node* n = new node(rootItem);
      module->setProperty( "pos", pos );
      module->setProperty( "type", type );
      if (module != NULL) {
	module->setParent( rootItem ); // FIXME CRITICAL: this should probably be done inside the rootItem itself! ;P
	rootItem->appendChild( module );
// 	qDebug() << __PRETTY_FUNCTION__ << ": created a new module";
      } else {
	qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: in insertRows(), exiting";
	exit(1);
      }
    }
    endInsertRows();
    return true;
}

bool Model::insertConnection(QPersistentModelIndex* src, int srcPort, int srcType, 
			     QPersistentModelIndex* dst, int dstPort, int dstType) {
/*  int row = rowCount( src );
  if ( data( src, customRole::TypeRole ).toInt() == DataItemType::DATAABSTRACTMODULE ) {
    DataAbstractItem* srcItem = static_cast<DataAbstractItem*>( src.internalPointer() );
    DataAbstractItem* dstItem = static_cast<DataAbstractItem*>( dst.internalPointer() );
    beginInsertRows( src, row, row + 0 );
    {
        DataConnection* dc = new DataConnection( srcItem , dstItem);
        srcItem->appendChild( dc );
    }
    endInsertRows();
    return true;
  }
  qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: can't add object to the automate class since i don't know what to do, exiting";
  exit(1);*/
  return false;
}


QVector<QString> Model::LoadableModuleNames() {
    return moduleFactory->LoadableModuleNames();
}