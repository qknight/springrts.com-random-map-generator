
#include "Const.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Const);

Const::Const() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Const::~Const() {
}

QString Const::identify() {
    return ID;
}
