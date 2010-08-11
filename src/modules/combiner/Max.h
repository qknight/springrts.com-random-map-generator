
#ifndef COMBINER_MAX__HH
#define COMBINER_MAX__HH

#include <DataAbstractModule.h>

#define ID "Combiner::Max"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Max : public DataAbstractModule {
public:
    Max();
    ~Max();

    QString identify();
};

#endif
