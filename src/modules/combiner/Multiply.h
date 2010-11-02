#ifndef COMBINER_MULTIPLY__HH
#define COMBINER_MULTIPLY__HH

#include <DataAbstractModule.h>

#define ID "Combiner::Multiply"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Multiply : public DataAbstractModule {
public:
    Multiply();
    ~Multiply();

    QString identify();
};

#endif
