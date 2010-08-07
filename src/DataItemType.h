#ifndef __DATAITEMTYPE__HH__
#define __DATAITEMTYPE__HH__

/*! this struct is important for the backend data structure */
namespace DataItemType {
  enum DataItemType {
    DATAROOT,
    DATAABSTRACTMODULE,
    DATAPROPERTY,
    DATAPORT,
    DATACONNECTION,
    DATAUNKNOWN
  };
}

#endif