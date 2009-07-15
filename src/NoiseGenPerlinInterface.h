//
// C++ Interface: NoiseGenPerlinInterface
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NOISEGENPERLININTERFACE_H
#define NOISEGENPERLININTERFACE_H

#include "NoiseGenPerlin.h"
#include "AbstractModule.h"
#include "ModuleFactory.h"

class NoiseGenPerlinInterface {
  public:
    NoiseGenPerlinInterface();
    ~NoiseGenPerlinInterface();
    static AbstractModule* CreateModule();
    const QString Id;
};

#endif
