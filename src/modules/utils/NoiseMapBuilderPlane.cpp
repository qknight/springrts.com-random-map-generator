#include "NoiseMapBuilderPlane.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseMapBuilderPlane);

NoiseMapBuilderPlane::NoiseMapBuilderPlane() : DataAbstractModule(1,0,0) {
  setProperty("FIXME", 112);
}

NoiseMapBuilderPlane::~NoiseMapBuilderPlane() {
}

