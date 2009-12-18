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

#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>

class Document;
class ModuleFactory;
class DataAbstractItem;
class DataRoot;
class DataAbstractModule;
class DataConnection;

#include <QPoint>

namespace customRole {
  enum CustomRole {
    // UserRole is the first number one can use for selfassigned roles by the Qt-toolkit
    TypeRole = Qt::UserRole, // used by views to query a QModelIndex for its type [NODE or NODE_CONNECTION .. or whatever]
    SortRole, // used by the TreeView to sort items
    PosRole, // used by GraphicsView to place a new node on 'node-creation-time'
  };
}

namespace ViewTreeItemType {
  // the idea behind yet another type identifier is that we map the types below via the model to the
  // types defined in DataAbstractItem.h (see TreeItemType in DataAbstractItem.h)
  enum TreeItemType {
    AUTOMATE_ROOT,
    NODE,
    NODE_CONNECTION,
    UNKNOWN
  };
}

/*! this is one of the core parts of this work and this code is very important in regards of syncing
**  the different views (as TreeView/GraphicsView)
**  the use of forward declarations are great since it helps to hide the data structure internals
**  and a view MUST NOT know anything about that -> all data must be queried/written using the model
*/
class Model : public QAbstractItemModel {
    friend class Document;

  protected:
    /*! a root node is mendatory to query for child items */
    Model( /*DataAbstractItem* root, QObject* parent = 0*/ );
    /*! see the Qt docs about QAbstractItemModel */
    QModelIndex index( int row, int column, const QModelIndex & parent ) const;
    /*! see the Qt docs about QAbstractItemModel */
    QModelIndex parent( const QModelIndex & index ) const;
    /*! see the Qt docs about QAbstractItemModel */
    int rowCount( const QModelIndex & parent ) const;
    /*! see the Qt docs about QAbstractItemModel */
    int columnCount( const QModelIndex & parent ) const;
    /*! see the Qt docs about QAbstractItemModel */
    QVariant data( const QModelIndex &, int role ) const;
    /*! see the Qt docs about QAbstractItemModel */
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    /*! this is the public interface, there is an private one for internal use as well!
    ** This function can be called with [node and node_connection model indexes in arbitrary order]
    **  - first all nodes get deleted BUT this list isn't altered so there might be connections in
    **    the list which are already deleted because when a NODE is deleted all incomming/outgoing
    **    connections are deleted implicitly. however having a list of connections with valid and invalid
    **    QModelIndex is no problem as only those get deleted which are still deletable.
    **  - if a NODE is deleted all incomming/outgoing connections are deleted implicitly,
    **     see: bool removeNode( QPersistentModelIndex node );
    */
//     bool removeItems( QList<QPersistentModelIndex> itemList );
    /*! this is the public interface, there is an private one for internal use as well!
    ** this inserts a node*/
//     bool insertNode(QPoint pos=QPoint());
    /*! this inserts a connection at startItem */
//     bool insertConnection( QModelIndex startItem, QModelIndex endItem = QModelIndex() );

    /*! returns the QModelIndex of the next_node from item which must be a connection */
//     QModelIndex next_nodeModelIndex( QModelIndex item );

  private:
    /*! reveals the type of object in the data structure represented by item in the model structure */
//     unsigned int getTreeItemType( const QModelIndex& item );
    /*! for debugging this function creates a QString, see the DataAbstractItem.h for reference */
//     QString objectTypeQString( unsigned int input );
    /*! this is used by the treeView when you insert a new destination for a connection. the
    ** input is then converted into a DataAbstractItem.*/
//     DataAbstractItem* DataAbstractItemFromId( unsigned int id );
    /*! removes a node */
//     bool removeNode( QPersistentModelIndex node );
    /*! removes a list of nodes in sequences (no parallel processing) */
//     bool removeNodes( QList<QPersistentModelIndex> nodeList );
    /*! removes a connection */
//     bool removeConnection( QPersistentModelIndex connection );
    /*! removes a list of connection in sequences (no parallel processing) */
//     bool removeConnections( QList<QPersistentModelIndex> nodeList );
    /*! needed when virtually deleting an item. the intention is to find out
    ** which QModelIndex must be deleted so that the item gets deleted by a model request */
//     QModelIndex getQModelIndexFromAbstractNodeItem( DataAbstractItem* item );
    /*! the root item is set by the constructor once and can't be changed and must not be deleted */
    DataAbstractItem* rootItem;
    /*! the only instance of ModuleFactory which will add new items using the model */ 
    ModuleFactory* moduleFactory;
    /*! see the Qt docs about QAbstractItemModel */
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    /*! see the Qt docs about QAbstractItemModel */
    bool hasChildren( const QModelIndex & parent = QModelIndex() ) const;
    /*! see the Qt docs about QAbstractItemModel */
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    /*! see the Qt docs about QAbstractItemModel 
    ** the obj can be used to initialize the object, check the insertRows implementation if your
    ** object type is supported (example: NODE is supported, that means one can use insertRows to insert
    ** exactly the given node called 'obj') */
    bool insertRows( int row, int count, const QModelIndex & parent = QModelIndex(), QPoint pos=QPoint(), QString type=QString());
    /*! see the Qt docs about QAbstractItemModel */
    bool removeRows( int row, int count, const QModelIndex & parent );
    
  protected:
    /*! this function removes all items expect the AutomateRoot item itself (which can't be removed by the model)
    ** It is used to cleanly destroy all objects related/including the 'class Automate'.<br>
    ** It can be called while views are attached to the model, it is not efficient performancewise */
//     void clear();
};

#endif

