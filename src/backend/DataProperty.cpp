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

#include "DataProperty.h"
DataProperty::DataProperty(QString key, QVariant value) {
  m_key = key;
  m_value = value;
}

QString DataProperty::key() {
    return m_key;
}

QVariant DataProperty::value() {
    return m_value;
}

void DataProperty::setValue(QVariant value) {
    m_value = value;
}

DataProperty::~DataProperty() {
//   qDebug() << __PRETTY_FUNCTION__;
};

unsigned int DataProperty::getObjectType() {
    return DataItemType::DATAPROPERTY;
}

void DataProperty::appendChild( DataAbstractItem *child ) {
  //nothing to do here
}

void DataProperty::removeChild ( unsigned int index ) {
    //nothing to do here
}



