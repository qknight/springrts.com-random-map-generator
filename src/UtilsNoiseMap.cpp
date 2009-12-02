//
// C++ Implementation: UtilsNoiseMap
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "src/UtilsNoiseMap.h"

#include "registermodule_macro.cpp"
#include "ModuleFactory.h"

M_REGISTER(UtilsNoiseMap);

UtilsNoiseMap::UtilsNoiseMap() {
}

UtilsNoiseMap::~UtilsNoiseMap() {
}

QString UtilsNoiseMap::identify() {
    return ID;
}


