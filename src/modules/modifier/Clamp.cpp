
#include "Clamp.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Clamp);

Clamp::Clamp() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Clamp::~Clamp() {
}

QString Clamp::identify() {
    return ID;
}
