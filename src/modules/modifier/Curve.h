#ifndef MODIFIER_CURVE__HH
#define MODIFIER_CURVE__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Curve"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Curve : public DataAbstractModule {
public:
    Curve();
    ~Curve();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
