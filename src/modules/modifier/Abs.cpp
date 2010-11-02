#include "Abs.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Abs);

Abs::Abs() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Abs::~Abs() {
}

