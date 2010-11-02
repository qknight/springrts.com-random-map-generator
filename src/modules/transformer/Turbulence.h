#ifndef TRANSFORMER_TURBULENCE__HH
#define TRANSFORMER_TURBULENCE__HH

#include <DataAbstractModule.h>

#define ID "Transformer::Turbulence"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Turbulence : public DataAbstractModule {
public:
    Turbulence();
    ~Turbulence();

    QString identify();
};

#endif
