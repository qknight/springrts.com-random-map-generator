//
// C++ Implementation: NoiseGenPerlin
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
// http://libnoise.sourceforge.net/docs/classnoise_1_1module_1_1Perlin.html

#include "NoiseGenPerlin.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenPerlin);

NoiseGenPerlin::NoiseGenPerlin() : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.234f);
  setProperty("Lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence",22);
  setProperty("Seed",3);
  setProperty("Noise quality",3);
}

NoiseGenPerlin::~NoiseGenPerlin() {
//     qDebug() << __PRETTY_FUNCTION__;
}

QString NoiseGenPerlin::identify() {
  return ID;
}
