#ifndef MODIFIER_ABS__HH
#define MODIFIER_ABS__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Abs"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Abs : public DataAbstractModule {
public:
    Abs();
    ~Abs();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
