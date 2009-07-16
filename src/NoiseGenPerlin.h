//
// C++ Interface: NoiseGenPerlin
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef NOISEGENPERLIN_H
#define NOISEGENPERLIN_H

#include <AbstractModule.h>
#include <noise/noise.h>
#include "visualModuleItem.h"

#define ID "NoiseGen::Perlin"

class NoiseGenPerlin : public AbstractModule {
  public:
    NoiseGenPerlin();
    ~NoiseGenPerlin();
    QString identify();
};

#endif
