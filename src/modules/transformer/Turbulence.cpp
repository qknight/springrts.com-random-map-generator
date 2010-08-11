
#include "Turbulence.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Turbulence);

Turbulence::Turbulence() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Turbulence::~Turbulence() {
}

QString Turbulence::identify() {
    return ID;
}
