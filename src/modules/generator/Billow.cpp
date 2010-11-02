#include "Billow.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Billow);

Billow::Billow() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Billow::~Billow() {
}

