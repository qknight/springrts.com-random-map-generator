#include "Add.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Add);

Add::Add() : DataAbstractModule(2,0,1) {
  setProperty("FIXME", 112);
}

Add::~Add() {
}

