
#ifndef COMBINER_ADD__HH
#define COMBINER_ADD__HH

#include <DataAbstractModule.h>

#define ID "Combiner::Add"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Add : public DataAbstractModule {
public:
    Add();
    ~Add();

    QString identify();
};

#endif