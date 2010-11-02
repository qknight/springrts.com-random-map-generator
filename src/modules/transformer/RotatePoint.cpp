#include "RotatePoint.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(RotatePoint);

RotatePoint::RotatePoint() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

RotatePoint::~RotatePoint() {
}

