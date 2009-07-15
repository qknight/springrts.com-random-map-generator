//
// C++ Implementation: NoiseGenPerlinInterface
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#include "NoiseGenPerlinInterface.h"

NoiseGenPerlinInterface::NoiseGenPerlinInterface() {
  qDebug("NoiseGenPerlinInterface::CTor");
  const QString Id = ID;
  bool registered = ModuleFactory::Instance()->RegisterModule(Id, NoiseGenPerlinInterface::CreateModule);
}

NoiseGenPerlinInterface::~NoiseGenPerlinInterface() { }

AbstractModule* NoiseGenPerlinInterface::CreateModule() {
  return new NoiseGenPerlin();
}

