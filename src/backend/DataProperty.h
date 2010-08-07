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

#ifndef DATAPROPERTY_H
#define DATAPROPERTY_H

#include "DataAbstractItem.h"

class DataProperty : public DataAbstractItem {
public:
    DataProperty();
    /*! returns the object type which is used in the model for example */
    unsigned int getObjectType();
    void removeChild( unsigned int index );
    void appendChild( DataAbstractItem *child );
protected:
    /*! WARNING: never delete objects as for instance childItems in the structure here
    ** since this will create inconsistencies between the model and this data structure.<br>
    ** A better way is to fail with exit(0) and a meaningful error message meant for
    ** developrs: since this problem must be handled with great care! */
    ~DataProperty();
private:
};

#endif // DATAPROPERTY_H
