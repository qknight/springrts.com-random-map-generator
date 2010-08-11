
#ifndef GENERATOR_PERLIN__HH
#define GENERATOR_PERLIN__HH

#include <DataAbstractModule.h>

#define ID "Generator::Perlin"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Perlin : public DataAbstractModule {
public:
    Perlin();
    ~Perlin();

    QString identify();
};

#endif
