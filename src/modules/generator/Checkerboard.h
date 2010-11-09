#ifndef GENERATOR_CHECKERBOARD__HH
#define GENERATOR_CHECKERBOARD__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::Checkerboard"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Checkerboard : public DataAbstractModule {
public:
    Checkerboard();
    ~Checkerboard();

    QString identify();
    NoiseNetwork* network();
};

#endif
