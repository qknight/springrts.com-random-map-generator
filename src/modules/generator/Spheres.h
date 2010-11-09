#ifndef GENERATOR_SPHERES__HH
#define GENERATOR_SPHERES__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::Spheres"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Spheres : public DataAbstractModule {
public:
    Spheres();
    ~Spheres();

    QString identify();
    NoiseNetwork* network();
};

#endif
