
#include "Invert.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Invert);

Invert::Invert() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Invert::~Invert() {
}

QString Invert::identify() {
    return ID;
}
