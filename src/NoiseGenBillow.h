//
// C++ Interface: NoiseGenBillow
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef NOISEGENBILLOW_H
#define NOISEGENBILLOW_H

#include <AbstractModule.h>
#include <noise/noise.h>

#include "visualModuleItem.h"
#include "ModuleFactory.h"

#define ID "NoiseGen::Billow"


/**
	@author Joachim Schiele <js@lastlog.de>
*/
class NoiseGenBillow : public AbstractModule {
public:
    NoiseGenBillow();
    ~NoiseGenBillow();
    QString identify();
};

#endif
