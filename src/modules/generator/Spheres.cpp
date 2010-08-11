
#include "Spheres.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Spheres);

Spheres::Spheres() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Spheres::~Spheres() {
}

QString Spheres::identify() {
    return ID;
}
