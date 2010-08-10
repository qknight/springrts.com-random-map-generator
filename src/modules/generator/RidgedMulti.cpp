//
// C++ Implementation: NoiseGenRidgedMulti
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//

#include "NoiseGenRidgedMulti.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenRidgedMulti);

NoiseGenRidgedMulti::NoiseGenRidgedMulti()  : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.234f);
  setProperty("Lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence", 22);
  setProperty("Seed", 3);
  setProperty("Noise quality", 3);
}

NoiseGenRidgedMulti::~NoiseGenRidgedMulti() {
}

QString NoiseGenRidgedMulti::identify() {
  return ID;
}
