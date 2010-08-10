//
// C++ Implementation: NoiseGenBillow
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Billow.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenBillow);

NoiseGenBillow::NoiseGenBillow() : DataAbstractModule(0,0,1) {
  setProperty("Frequency", 0.234f);
  setProperty("Lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence",22);
  setProperty("Seed",3);
  setProperty("Noise quality",3);
}

NoiseGenBillow::~NoiseGenBillow() {
//     qDebug() << __PRETTY_FUNCTION__;
}

QString NoiseGenBillow::identify() {
  return ID;
}
