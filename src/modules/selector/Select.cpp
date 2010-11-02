#include "Select.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Select);

Select::Select() : DataAbstractModule(2,1,1) {
  setProperty("FIXME", 112);
}

Select::~Select() {
}

