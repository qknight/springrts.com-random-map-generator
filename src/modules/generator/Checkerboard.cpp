#include "Checkerboard.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Checkerboard);

Checkerboard::Checkerboard() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Checkerboard::~Checkerboard() {
}

