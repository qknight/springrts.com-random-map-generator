#include "Max.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Max);

Max::Max() : DataAbstractModule(2,0,1) {
  setProperty("FIXME", 112);
}

Max::~Max() {
}

