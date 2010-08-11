
#include "Billow.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Billow);

Billow::Billow() : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.234f);
  setProperty("Lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence",22);
  setProperty("Seed",3);
  setProperty("Noise quality",3);
}

Billow::~Billow() {
}

QString Billow::identify() {
    return ID;
}
