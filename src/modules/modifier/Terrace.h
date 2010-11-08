#ifndef MODIFIER_TERRACE__HH
#define MODIFIER_TERRACE__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Modifier::Terrace"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Terrace : public DataAbstractModule {
public:
    Terrace();
    ~Terrace();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
