
#include "Min.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Min);

Min::Min() : DataAbstractModule(2,0,1) {
  setProperty("FIXME", 112);
}

Min::~Min() {
}

QString Min::identify() {
    return ID;
}
