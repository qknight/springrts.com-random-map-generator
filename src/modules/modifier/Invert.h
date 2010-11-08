#ifndef MODIFIER_INVERT__HH
#define MODIFIER_INVERT__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Invert"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Invert : public DataAbstractModule {
public:
    Invert();
    ~Invert();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
