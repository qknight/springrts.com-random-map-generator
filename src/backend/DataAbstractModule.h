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
#ifndef DATAABSTRACTMODULE_H
#define DATAABSTRACTMODULE_H

#include <QPoint>
#include <QString>

#include "DataAbstractItem.h"
#include "DataConnection.h"

/*! a node represents 'a node' in the data */
class DataAbstractModule : public DataAbstractItem {
  Q_OBJECT
  friend class DataConnection;
  public:
    DataAbstractModule( /*DataAbstractItem* parent*/ );
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataAbstractModule();
    /*! dumps the internal state for debugging */
    void dump();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    /*! adds a child (a connection) but also adds a reverse child, see code since this is quite complex */
    void appendChild( DataAbstractItem *child );
    /*! removes a child (a connection) but also removes a reverse child, see code since this is quite complex */
    void removeChild( unsigned int index );
    /*! returns the contents of m_reverseChildItems */
    const QList<DataAbstractItem*> reverseChildItems();
    /*! used to identify modules, used by the ModuleFactaory */
    virtual QString identify()=0;
  private:
    /*! this container is added for 'node's only and stores all references to this node */
    QList<DataAbstractItem*> m_reverseChildItems;
  protected:
    /*! internal use only: inserts a reversepath */
    void appendChildReversePath( DataAbstractItem *item );
    /*! internal use only: inserts a forwardpath */
    void appendChildForwardPath( DataAbstractItem *item );
    /*! internal use only: removes a reversepath */
    void removeChildReversePath( DataAbstractItem *item );
};

#endif // DATAABSTRACTMODULE_H
