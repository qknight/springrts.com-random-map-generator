
#include "Multiply.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Multiply);

Multiply::Multiply() : DataAbstractModule(2,0,1) {
  setProperty("FIXME", 112);
}

Multiply::~Multiply() {
}

QString Multiply::identify() {
    return ID;
}
