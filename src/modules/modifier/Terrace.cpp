#include "Terrace.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Terrace);

Terrace::Terrace() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Terrace::~Terrace() {
}

