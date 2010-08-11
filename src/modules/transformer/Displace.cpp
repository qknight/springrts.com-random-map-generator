
#include "Displace.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Displace);

Displace::Displace() : DataAbstractModule(1,3,1) {
  setProperty("FIXME", 112);
}

Displace::~Displace() {
}

QString Displace::identify() {
    return ID;
}
