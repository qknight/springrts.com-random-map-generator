
#include "Cylinders.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Cylinders);

Cylinders::Cylinders() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Cylinders::~Cylinders() {
}

QString Cylinders::identify() {
    return ID;
}
