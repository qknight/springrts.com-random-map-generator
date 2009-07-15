//
// C++ Implementation: registermodule_makro
//
// Description:
//  this is a macro which helps to register all modules
//  the trick is we do that in the global namespace so we do NOT
//  have to include all modules in the mainWidget.cpp code
//
//  if not done this way this would result in a major recompile
//  one minor changes
//
// Usage:
//  in a module one has to call this makro which then registers the
//  module in the objectFactory singleton
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "ModuleFactory.h"
#include "NoiseGenPerlin.h"
#include "AbstractModule.h"

class registermodule_Makro_Interface {
  public:
    registermodule_Makro_Interface();
    ~registermodule_Makro_Interface();
    static AbstractModule* CreateModule();
    const QString Id;
};

registermodule_Makro_Interface::registermodule_Makro_Interface() {
  qDebug("registermodule_Makro_Interface calling PerlinInterface::CTor");
  const QString Id = ID;
  bool registered = ModuleFactory::Instance()->RegisterModule(Id, registermodule_Makro_Interface::CreateModule);
}

registermodule_Makro_Interface::~registermodule_Makro_Interface() { }

AbstractModule* registermodule_Makro_Interface::CreateModule() {
  return new NoiseGenPerlin();
}

static registermodule_Makro_Interface* f = new registermodule_Makro_Interface();








