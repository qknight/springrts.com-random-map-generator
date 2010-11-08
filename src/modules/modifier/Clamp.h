#ifndef MODIFIER_CLAMP__HH
#define MODIFIER_CLAMP__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Clamp"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Clamp : public DataAbstractModule {
public:
    Clamp();
    ~Clamp();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
