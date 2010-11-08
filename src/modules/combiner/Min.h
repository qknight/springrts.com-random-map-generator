#ifndef COMBINER_MIN__HH
#define COMBINER_MIN__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Combiner::Min"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Min : public DataAbstractModule {
public:
    Min();
    ~Min();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
