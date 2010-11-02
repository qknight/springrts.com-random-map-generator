#ifndef MODIFIER_TERRACE__HH
#define MODIFIER_TERRACE__HH

#include <DataAbstractModule.h>

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
};

#endif
