
#include "ScaleBias.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(ScaleBias);

ScaleBias::ScaleBias() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

ScaleBias::~ScaleBias() {
}

QString ScaleBias::identify() {
    return ID;
}
