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

#ifndef DATAABSTRACTITEM_H
#define DATAABSTRACTITEM_H

#include <QList>
#include <QDebug>
#include <QObject>

namespace DataItemType {
  enum DataItemType {
    DATAROOT,
    DATAABSTRACTMODULE,
    DATACONNECTION,
    UNKNOWN
  };
}

class DataAbstractItem : QObject {
  Q_OBJECT
    friend class DataRoot;
    friend class DataAbstractModule;
    friend class DataConnection;
    friend class Model;
  public:
    /*! returns the number of childs:
      - 0 no childs
      - >0 child amount
      - <0 error
    */
    int childCount() const;
    /*! returns the m_childItems position offset of this in/from the parent item */
    int row() const;
    /*! returns the id for this item */
//     unsigned int getId();
    /*! returns DataAbstractItem* from the m_childItems list with index=row*/
    DataAbstractItem *child( int row );
    /*! returns the parent item
      - only one item doesn't have a parent, that is the AutomateRoot
      - all other items MUST have a valid parent*/
    DataAbstractItem *parent();
    /*! returns m_childItems.size() */
    QList<DataAbstractItem*> childItems() const;
    /*! appends a new child to m_childItems, child has to have this as parent already! */
    virtual void appendChild( DataAbstractItem *child );
    /*! returns the object type, see deriving classes for details */
    virtual unsigned int getObjectType() = 0;
    /*! removes a child from m_childItems */
    virtual void removeChild( unsigned int index ) = 0;
  protected:
    /*! WARNING: never delete objects as for instance childItems within the destructor
    since this will create inconsistencies between the model and this data structure.
    A better way is to fail with exit(0) since this problem must be handled with great care! */
    virtual ~DataAbstractItem();

    /*! the constructor is protected to enforce the policy, which is:
      - only derived classes may be used to create objects from:
        - that is: AutomateRoot, node, node_connection*/
    DataAbstractItem( DataAbstractItem *parent = 0 );
    /*! id of this object
      - 0 is default but it's overwritten in the constructor of the deriving class
      - only the AutomateRoot may leave the 0 unchanged! */
//     unsigned int ID;
    /*! see TreeItemType
      This variable is used to identify what kind of object we have.*/
//     unsigned int objectType;
    /*! This container holds all child items */
    QList<DataAbstractItem*> m_childItems;
    /*! This function was introduced when I found out that we need to move the reverse connection
        from one parent to another since we don't want to create a new reverse connection for every
        forward connection which changes it's destination.*/
    void setParent(DataAbstractItem *parent);
    /*! This function dumps the whole data to stdout which is helpful when doing debugging. You could use the
        provided functionality also for other purposes as calling external algorithms which operate on the
        data structure of this automate. For example: automate_algorithms could be ported to this data structure
        so that one can convert a NDA to a DFA and stuff like that, see automate_algorithms.cpp */
    virtual void dump() = 0;
  private:
    /*! This parent item is used to traverse the tree upwards. */
    DataAbstractItem *parentItem;
};

#endif // DATAABSTRACTITEM_H