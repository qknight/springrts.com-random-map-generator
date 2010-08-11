
#include "Perlin.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Perlin);

Perlin::Perlin() : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.234f);
  setProperty("Lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence",22);
  setProperty("Seed",3);
  setProperty("Noise quality",3);
}

Perlin::~Perlin() {
}

QString Perlin::identify() {
    return ID;
}
