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

#include <DataAbstractModule.h>

#define ID "Generator::Billow"

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class NoiseGenBillow : public DataAbstractModule {
public:
    NoiseGenBillow();
    ~NoiseGenBillow();
    QString identify();
};

#endif
