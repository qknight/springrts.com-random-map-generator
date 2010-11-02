#include "Exponent.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Exponent);

Exponent::Exponent() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Exponent::~Exponent() {
}

