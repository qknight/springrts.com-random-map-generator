
#include "ScalePoint.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(ScalePoint);

ScalePoint::ScalePoint() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

ScalePoint::~ScalePoint() {
}

QString ScalePoint::identify() {
    return ID;
}
