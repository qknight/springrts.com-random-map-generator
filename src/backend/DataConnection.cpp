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

#include "DataConnection.h"
#include "DataAbstractModule.h"

DataConnection::DataConnection ( DataAbstractItem* src, DataAbstractItem* dst) : DataAbstractItem ( src ) {
    qDebug() << __PRETTY_FUNCTION__;
    m_src = src;
    m_dst = dst;
//     dump();
}

DataConnection::~DataConnection() {
//   qDebug() << __PRETTY_FUNCTION__;
}

DataAbstractItem* DataConnection::src () {
    return m_src;
}

int DataConnection::srcType ( ) {
    return m_srcType;
}

DataAbstractItem* DataConnection::dst ( ) {
    return m_dst;
}

int DataConnection::dstType ( ) {
    return m_dstType;
}

void DataConnection::dump() {
    qDebug() << "===================================================";
    qDebug() << "m_src " << m_src;
    qDebug() << "m_srcType " << m_srcType;
    qDebug() << "m_dst " << m_dst;
    qDebug() << "m_dstType " << m_dstType;
    qDebug() << "===================================================";
}

unsigned int DataConnection::getObjectType() {
    return DataItemType::DATACONNECTION;
}

void DataConnection::removeChild ( unsigned int index ) {
    qDebug() << "Fatal error, this should not be called as connections don't have childs, exiting...";
    exit ( 1 );
}

