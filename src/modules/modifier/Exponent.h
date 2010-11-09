#ifndef MODIFIER_EXPONENT__HH
#define MODIFIER_EXPONENT__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Exponent"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Exponent : public DataAbstractModule {
public:
    Exponent();
    ~Exponent();

    QString identify();
    NoiseNetwork* network();
};

#endif
