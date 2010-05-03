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

DataConnection::DataConnection ( DataAbstractItem* src, int srcType,
                                 DataAbstractItem* dst, int dstType ) : DataAbstractItem ( src ) {
    qDebug() << __PRETTY_FUNCTION__;
    m_src = src;
    m_srcType = srcType;
    m_dst = dst;
    m_dstType = dstType;
    qDebug() << "===================================================";
    qDebug() << "m_src " << m_src;
    qDebug() << "m_srcType " << m_srcType;
    qDebug() << "m_dst " << m_dst;
    qDebug() << "m_dstType " << m_dstType;
    qDebug() << "===================================================";
//    test(src);
//       qDebug() << "===================================================";
//    test(dst);
//       qDebug() << "===================================================";
//    exit(0);
   
}

// void DataConnection::test(DataAbstractItem* s) {
//   qDebug() << src(s);
//   qDebug() << dst(s);
//   qDebug() << srcType(s);
//   qDebug() << dstType(s);
// 
// }

DataConnection::~DataConnection() {
//   qDebug() << __PRETTY_FUNCTION__;
}

DataAbstractItem* DataConnection::src ( DataAbstractItem* querier ) {
//   qDebug() << "------------(";
//   qDebug() << querier;
//   qDebug() << parent();
//   qDebug() << m_src;
//   qDebug() << m_dst;
//   qDebug() << ")------------";
//   qDebug() << static_cast<DataAbstractModule*> (querier);
//   exit(0);
  
  qDebug() << __PRETTY_FUNCTION__ << querier->getObjectType();
    if ( parent() == querier )
        return m_dst;
    else if ( m_dst == querier )
        return m_src;
    qDebug() << __PRETTY_FUNCTION__ << "fatal error";
    exit(1);
}

//FIXME broken
// int DataConnection::srcType ( DataAbstractItem* querier ) {
//   qDebug() << __PRETTY_FUNCTION__ <<  querier->getObjectType();
// //     if ( parent() == querier )
// //         return m_dstType;
// //     else if ( m_dst == querier )
// //         return m_srcType;
//     qDebug() << __PRETTY_FUNCTION__ << "fatal error";
//     exit(1);
// }

DataAbstractItem* DataConnection::dst ( DataAbstractItem* querier ) {
    return src ( querier );
}

//FIXME broken
// int DataConnection::dstType ( DataAbstractItem* querier ) {
// //     return srcType ( querier );
// }

void DataConnection::dump() {}

unsigned int DataConnection::getObjectType() {
    return DataItemType::DATACONNECTION;
}

void DataConnection::removeChild ( unsigned int index ) {
    qDebug() << "Fatal error, this should not be called, exiting...";
//     qDebug() << "having " << m_childItems.size() << " childs";
    exit ( 1 );
}

