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

#ifndef DATAPORT_H
#define DATAPORT_H

#include "DataAbstractItem.h"
#include "PortTypes.h"
#include "DataConnection.h"
#include "ConnectionValidator.h"

class DataPort : public DataAbstractItem, public ConnectionValidator {
    Q_OBJECT
public:
    DataPort(int portType, int portDirection, int portNumber);
    /*! WARNING: never delete objects as for instance childItems in the structure here
     ** since this will create inconsistencies between the model and this data structure.<br>
     ** A better way is to fail with exit(0) and a meaningful error message meant for
     ** developrs: since this problem must be handled with great care! */
    ~DataPort();
    /*! dumps the internal data structure for debugging use */
    void dump();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    void removeChild( unsigned int index );
    unsigned int PortType();
    unsigned int PortDirection();
    unsigned int PortNumber();

protected:
    bool insertConnection ( DataConnection* c );
    void insertReference ( DataAbstractItem* item );
    void removeReference ( DataAbstractItem* item );
private:
    QList<DataAbstractItem*> m_childItemsReferences;
    int m_portNumber;
    int m_portType;
    int m_portDirection;
};

#endif // DATAPORT_H
