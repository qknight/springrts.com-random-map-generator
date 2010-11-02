#ifndef GENERATOR_BILLOW__HH
#define GENERATOR_BILLOW__HH

#include <DataAbstractModule.h>

#define ID "Generator::Billow"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Billow : public DataAbstractModule {
public:
    Billow();
    ~Billow();

    QString identify();
};

#endif
