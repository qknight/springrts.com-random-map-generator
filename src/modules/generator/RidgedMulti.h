#ifndef GENERATOR_RIDGEDMULTI__HH
#define GENERATOR_RIDGEDMULTI__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::RidgedMulti"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class RidgedMulti : public DataAbstractModule {
public:
    RidgedMulti();
    ~RidgedMulti();

    QString identify();
    NoiseNetwork* network();
};

#endif
