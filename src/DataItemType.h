#ifndef __DATAITEMTYPE__HH__
#define __DATAITEMTYPE__HH__

/*! this struct is important for the backend and frontend*/
namespace DataItemType {
  enum DataItemType {
    ROOT,
    MODULE,
    PROPERTY,
    PORT,
    CONNECTION,
    UNKNOWN
  };
}

#endif