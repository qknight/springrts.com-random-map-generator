#ifndef GENERATOR_VORONOI__HH
#define GENERATOR_VORONOI__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::Voronoi"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Voronoi : public DataAbstractModule {
public:
    Voronoi();
    ~Voronoi();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
