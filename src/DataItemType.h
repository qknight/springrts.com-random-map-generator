#ifndef __DATAITEMTYPE__HH__
#define __DATAITEMTYPE__HH__

/*! this struct is important for the backend and frontend*/
namespace DataItemType {
  enum DataItemType {
    ROOT = 65537,
    MODULE,
    PROPERTY,
    PORT,
    CONNECTION,
    EXTENDEDGRAPHICSITEM, // used for the QGraphicsScene
    UNKNOWN
  };
}

#endif