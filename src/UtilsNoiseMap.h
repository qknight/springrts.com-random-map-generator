//
// C++ Interface: UtilsNoiseMap
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef UTILSNOISEMAP_H
#define UTILSNOISEMAP_H

#include <AbstractModule.h>
#include <noise/noise.h>
#include "visualModuleItem.h"

#define ID "Utils::NoiseMap"

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class UtilsNoiseMap : public AbstractModule {
public:
    UtilsNoiseMap();
    ~UtilsNoiseMap();

    QString identify();

};

#endif
