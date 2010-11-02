#include "RidgedMulti.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(RidgedMulti);

RidgedMulti::RidgedMulti() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

RidgedMulti::~RidgedMulti() {
}

