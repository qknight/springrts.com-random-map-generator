#include "ConnectionValidator.h"

// bool ConnectionValidator::validate() {
//     if ( m_src == m_dst ) {
//         qDebug() << __PRETTY_FUNCTION__ << "error, can't add connection since src=dst meaning it's a loop item";
//         return false;
//     }
//     if ( m_src == NULL || m_dst == NULL ) {
//         qDebug() << __PRETTY_FUNCTION__ << "error, can't add connection since src or dst is NULL";
//         return false;
//     }
//     // -1. check if the parents are modules
//     if ((m_src->getObjectType() != DataItemType::DATAABSTRACTMODULE) || (m_dst->getObjectType() != DataItemType::DATAABSTRACTMODULE)) {
//       qDebug() << __PRETTY_FUNCTION__ << "parents are no modules?!";
//       return false;
//     }
//     
//     // 0. i - i, o - o, m - m forbidden combinations
//     if (m_srcType == m_dstType) {
//       qDebug() << __PRETTY_FUNCTION__ << "srcType == dstType can't be used to create a connection, would you like to connect an input to an input?";
//       return false;
//     }
//     // 1. verify input/modput/output combinations, one output is guaranteed if 
//     //    we pass this test
//     int c = m_srcType + m_dstType;
//     if (!(c > 0 && c < 4)) {
//       qDebug() << __PRETTY_FUNCTION__ << "combination was not allowed";
//       return false;
//     }
//     
//     // 2. check if there is a 'potential' free port for the type at src and at dst
//     //    if someone uses model->addConnection(..) instead of the gui this might
//     //    help to avoid errors
//     DataAbstractModule* srcAM = static_cast<DataAbstractModule*>(m_src);
//     if (srcAM->ports(m_srcType) == 0)
//       return false;
//     DataAbstractModule* dstAM = static_cast<DataAbstractModule*>(m_dst);
//     if (dstAM->ports(m_dstType) == 0)
//       return false;
//     return true;
//     }