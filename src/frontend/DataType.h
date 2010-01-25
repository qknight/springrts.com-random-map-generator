#ifndef DATATYPE__HH__
#define DATATYPE__HH__

namespace DataType {
  // the idea behind yet another type identifier is that we map the types below via the model to the
  // types defined in DataAbstractItem.h (see DataItemType in DataAbstractItem.h)
  enum TreeItemType {
    DATA_ROOT,
    MODULE,
    CONNECTION,
    PORT,
    UNKNOWN
  };
}

#endif