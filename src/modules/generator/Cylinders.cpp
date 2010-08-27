
#include "Cylinders.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Cylinders);

Cylinders::Cylinders() : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.034f);
}

Cylinders::~Cylinders() {
}

QString Cylinders::identify() {
    return ID;
}
