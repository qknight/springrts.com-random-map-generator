//
// C++ Implementation: ModuleFactorySingleton
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "ModuleFactorySingleton.h"

ModuleFactorySingleton::ModuleFactorySingleton(graphicsScene* scene) {
}

ModuleFactorySingleton::~ModuleFactorySingleton() { }

ModuleFactory* ModuleFactorySingleton::instance() {
  return moduleFactory;
}
