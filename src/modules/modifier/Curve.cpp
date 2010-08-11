
#include "Curve.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Curve);

Curve::Curve() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

Curve::~Curve() {
}

QString Curve::identify() {
    return ID;
}
