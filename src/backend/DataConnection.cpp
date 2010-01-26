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

DataConnection::DataConnection ( DataAbstractItem* src, int srcType, int srcPortNumber,
                                 DataAbstractItem* dst, int dstType, int dstPortNumber ) : DataAbstractItem ( src ) {
//                                    the problem lies in the fact that src(s) and dst(s) return the same values what is wrong!
    qDebug() << __PRETTY_FUNCTION__;
    m_src = src;
    m_srcType = srcType;
    m_srcPortNumber = srcPortNumber;
    m_dst = dst;
    m_dstType = dstType;
    m_dstPortNumber = dstPortNumber;
       qDebug() << "===================================================";
    qDebug() << "m_src " << m_src;
    qDebug() << "m_srcType " << m_srcType;
    qDebug() << "m_srcPortNumber " << m_srcPortNumber;
    qDebug() << "m_dst " << m_dst;
    qDebug() << "m_dstType " << m_dstType;
    qDebug() << "m_dstPortNumber " << m_dstPortNumber;
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
//   qDebug() << srcPortNumber(s);
//   qDebug() << dstPortNumber(s);
// 
// }

DataConnection::~DataConnection() {
//   qDebug() << __PRETTY_FUNCTION__;
}

DataAbstractItem* DataConnection::src ( DataAbstractItem* querier ) {
  qDebug() << "------------(";
  qDebug() << querier;
  qDebug() << parent();
  qDebug() << ")------------";
//   qDebug() << static_cast<DataAbstractModule*> (querier);
//   exit(0);
  
  qDebug() << __PRETTY_FUNCTION__ << querier->getObjectType();
    if ( parent() == querier )
        return m_src;
    else if ( m_dst == querier )
        return m_dst;
    qDebug() << __PRETTY_FUNCTION__ << "fatal error";
    exit(1);
}

int DataConnection::srcType ( DataAbstractItem* querier ) {
  qDebug() << __PRETTY_FUNCTION__ <<  querier->getObjectType();
    if ( parent() == querier )
        return m_srcType;
    else if ( m_dst == querier )
        return m_dstType;
    qDebug() << __PRETTY_FUNCTION__ << "fatal error";
    exit(1);
}

int DataConnection::srcPortNumber ( DataAbstractItem* querier ) {
  qDebug() << __PRETTY_FUNCTION__ <<  querier->getObjectType();
    if ( parent() == querier )
        return m_srcPortNumber;
    else if (m_dst == querier )
        return m_dstPortNumber;
    qDebug() << __PRETTY_FUNCTION__ << "fatal error";
    exit(1);
}

DataAbstractItem* DataConnection::dst ( DataAbstractItem* querier ) {
    return src ( querier );
}

int DataConnection::dstType ( DataAbstractItem* querier ) {
    return srcType ( querier );
}

int DataConnection::dstPortNumber ( DataAbstractItem* querier ) {
    return srcPortNumber ( querier );
}

void DataConnection::dump() {}

unsigned int DataConnection::getObjectType() {
    return DataItemType::DATACONNECTION;
}

void DataConnection::removeChild ( unsigned int index ) {
    qDebug() << "Fatal error, this should not be called, exiting...";
//     qDebug() << "having " << m_childItems.size() << " childs";
    exit ( 1 );
}

bool DataConnection::validate() {
    if ( m_src == m_dst ) {
        qDebug() << __PRETTY_FUNCTION__ << "error, can't add connection since src=dst meaning it's a loop item";
        return false;
    }
    if ( m_src == NULL || m_dst == NULL ) {
        qDebug() << __PRETTY_FUNCTION__ << "error, can't add connection since src or dst is NULL";
        return false;
    }
    // -1. check if the parents are modules
    if ((m_src->getObjectType() != DataItemType::DATAABSTRACTMODULE) || (m_dst->getObjectType() != DataItemType::DATAABSTRACTMODULE)) {
      qDebug() << __PRETTY_FUNCTION__ << "parents are no modules?!";
      return false;
    }
    
    // 0. i - i, o - o, m - m forbidden combinations
    if (m_srcType == m_dstType) {
      qDebug() << __PRETTY_FUNCTION__ << "srcType == dstType can't be used to create a connection, would you like to connect an input to an input?";
      return false;
    }
    // 1. verify input/modput/output combinations, one output is guaranteed if 
    //    we pass this test
    int c = m_srcType + m_dstType;
    if (!(c > 0 && c < 4)) {
      qDebug() << __PRETTY_FUNCTION__ << "combination was not allowed";
      return false;
    }
    
    // 2. check if there is a 'potential' free port for the type at src and at dst
    //    if someone uses model->addConnection(..) instead of the gui this might
    //    help to avoid errors
    DataAbstractModule* srcAM = static_cast<DataAbstractModule*>(m_src);
    if (srcAM->ports(m_srcType) == 0)
      return false;
    DataAbstractModule* dstAM = static_cast<DataAbstractModule*>(m_dst);
    if (dstAM->ports(m_dstType) == 0)
      return false;
    return true;
}
