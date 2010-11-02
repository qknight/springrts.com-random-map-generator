#ifndef COMBINER_POWER__HH
#define COMBINER_POWER__HH

#include <DataAbstractModule.h>

#define ID "Combiner::Power"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Power : public DataAbstractModule {
public:
    Power();
    ~Power();

    QString identify();
};

#endif
