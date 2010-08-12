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
#include <QPoint>
#include "DataItemType.h"

class Document;
class ModuleFactory;
class DataAbstractItem;
class DataRoot;
class DataAbstractModule;
class DataPort;
class DataProperty;
class DataConnection;

namespace customRole {
  enum CustomRole {
    // UserRole is the first number one can use for selfassigned roles by the Qt-toolkit
    TypeRole = Qt::UserRole, // used by views to query a QModelIndex for its type rootNode, module, property, port, connection
    SortRole, // used by the TreeView to sort items
    PosRole, // used by GraphicsView to place a new node on 'node-creation-time'
    InputsRole, // returns the amount of inputs of a module
    ModputsRole,// returns the amount of modputs of a module
    OutputsRole,// returns the amount of outputs of a module
    ConnectionDestinationRole, // use to get the destination of a connection, that is a QModelIndex
    PortType,
    PortDirection,
    PortNumber
  };
}

/*! this is one of the core parts of this work and this code is very important in regards of syncing
**  the different views (as TreeView/GraphicsView)
**  the use of forward declarations are great since it helps to hide the data structure internals
**  and a view MUST NOT know anything about that -> all data must be queried/written using the model
*/
class Model : public QAbstractItemModel {
    friend class GraphicsItemModelExtension;
    friend class Document;
    friend class GraphicsScene;
    friend class ItemView;

  protected:
    /*! rootItem is the root of the data structure, living in this Model class */
    Model();
    /*! if this is called, we assume that no more view is attached */
    ~Model();
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
    ** this inserts a module of type 'QString type' at position pos, pos is importatnt for the QGraphicsScene*/
    QModelIndex insertModule(QString type, QPoint pos=QPoint());
    QModelIndex insertConnection(QPersistentModelIndex a, QPersistentModelIndex b);
    bool removeModule( const QModelIndex & parent );
    bool removeConnection( const QModelIndex & parent );
    
    QModelIndex dst(QPersistentModelIndex item);
  private:
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
    QVector<QString> LoadableModuleNames();
};

#endif

