#include "Power.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Power);

Power::Power() : DataAbstractModule(2,0,1) {
  setProperty("FIXME", 112);
}

Power::~Power() {
}

