#include "Mapgenerator.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Mapgenerator);

Mapgenerator::Mapgenerator() : DataAbstractModule(1,0,0) {
  setProperty("FIXME", 112);
}

Mapgenerator::~Mapgenerator() {
}

