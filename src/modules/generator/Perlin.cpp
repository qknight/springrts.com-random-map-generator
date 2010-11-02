#include "Perlin.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Perlin);

Perlin::Perlin() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Perlin::~Perlin() {
}

