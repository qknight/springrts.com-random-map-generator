
#include "Blend.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Blend);

Blend::Blend() : DataAbstractModule(2,1,1) {
  setProperty("FIXME", 112);
}

Blend::~Blend() {
}

QString Blend::identify() {
    return ID;
}
