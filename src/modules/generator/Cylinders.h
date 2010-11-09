#ifndef GENERATOR_CYLINDERS__HH
#define GENERATOR_CYLINDERS__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::Cylinders"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Cylinders : public DataAbstractModule {
public:
    Cylinders();
    ~Cylinders();

    QString identify();
    NoiseNetwork* network();
};

#endif
