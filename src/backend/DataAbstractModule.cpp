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

#include "DataAbstractModule.h"
#include "DataProperty.h"

DataAbstractModule::DataAbstractModule ( int inputs, int modputs, int outputs ) {
    // ports need to be created from insertModule(..) in Model.cpp, see also the insertPort(..) implementation
    this->inputs=inputs;
    this->modputs=modputs;
    this->outputs=outputs;
}

DataAbstractModule::~DataAbstractModule() {
//   qDebug() << __PRETTY_FUNCTION__;
    // we have to take care about the Ports and properties, just remove all of them!
    foreach(DataAbstractItem* item, m_childItems) {
        removeChild(m_childItems.indexOf(item));
    }
}

DataProperty* DataAbstractModule::setProperty(QString key, QVariant value) {
    //search if key is already there and modify it
    for (int i = 0; i < childCount(); ++i) {
        if (childItems()[i]->getObjectType() == DataItemType::PROPERTY) {
            DataProperty* p = static_cast<DataProperty*>( childItems()[i] );
            if (p->key() == key) {
                p->setValue(value);
                return p;
            }
        }
    }
    // key wasn't found, so we create it
    DataProperty* p = new DataProperty(key, value);
    p->setParent(this);
    appendChild(p);
    return p;
}

QVariant DataAbstractModule::property(QString key) {
    for (int i = 0; i < childCount(); ++i) {
        if (childItems()[i]->getObjectType() == DataItemType::PROPERTY) {
            DataProperty* p = static_cast<DataProperty*>( childItems()[i] );
            if (p->key() == key)
                return p->value();
        }
    }
    return QVariant();
}

unsigned int DataAbstractModule::getObjectType() {
    return DataItemType::MODULE;
}

void DataAbstractModule::removeChild ( unsigned int index ) {
//   qDebug() << __PRETTY_FUNCTION__;
    if ( m_childItems.size() < index ) {
        qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: child item not found";
        exit( 1 );
    }
    DataAbstractItem* child = m_childItems[index];
    m_childItems.removeAt( index );
    delete child;
}

// will return how many ports are used per type
int DataAbstractModule::ports ( int type ) {
    switch ( type ) {
    case PortDirection::IN:
        return inputs;
        break;
    case PortDirection::MOD:
        return modputs;
        break;
    case PortDirection::OUT:
        return outputs;
        break;
    default:
        return 0;
    }
}

