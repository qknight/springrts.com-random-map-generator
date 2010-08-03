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
#include "NoiseGenBillow.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenBillow);

NoiseGenBillow::NoiseGenBillow() : DataAbstractModule(0,0,1) {
  noise::module::Billow myModule;
}

NoiseGenBillow::~NoiseGenBillow() {
//     qDebug() << __PRETTY_FUNCTION__;
}

QString NoiseGenBillow::identify() {
  return ID;
}
