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
#include "src/NoiseGenBillow.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenBillow);

NoiseGenBillow::NoiseGenBillow() {
  noise::module::Billow myModule;
}

NoiseGenBillow::~NoiseGenBillow() {
}

QString NoiseGenBillow::identify() {
  return ID;
}
