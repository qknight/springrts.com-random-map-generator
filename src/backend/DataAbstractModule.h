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
#include "DataPort.h"
#include "PortTypes.h"

/*! a node represents 'a node' in the data */
class DataAbstractModule : public DataAbstractItem {
        Q_OBJECT
        friend class DataConnection;
    public:
        DataAbstractModule ( int inputs, int modputs, int outputs );
        /*! WARNING: never delete objects as for instance childItems in the structure here
         ** since this will create inconsistencies between the model and this data structure.<br>
         ** A better way is to fail with exit(0) and a meaningful error message meant for
         ** developrs: since this problem must be handled with great care! */
        virtual ~DataAbstractModule();
        /*! dumps the internal state for debugging */
        void dump();
        /*! returns the object type which is used in the model for example */
        unsigned int getObjectType();
        /*! adds a child (a connection) but also adds a reverse child, see code since this is quite complex */
//         void appendChild ( DataAbstractItem *child ) = 0;
        /*! removes a child (a connection) but also removes a reverse child, see code since this is quite complex */
        void removeChild ( unsigned int index );
        /*! used to identify modules, used by the ModuleFactaory */
        virtual QString identify() = 0;
        int ports ( int type );
//         bool isPortUsed(DataAbstractItem *item);
    private:
        /*! This container holds all child items which reference this object as input/modput */
        QList<DataAbstractItem*> m_childItemsReferences;
        bool insertPort ( DataConnection* c );
        int inputs, outputs, modputs;
};

#endif // DATAABSTRACTMODULE_H
