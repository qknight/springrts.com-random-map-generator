#ifndef TRANSFORMER_SCALEPOINT__HH
#define TRANSFORMER_SCALEPOINT__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Transformer::ScalePoint"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class ScalePoint : public DataAbstractModule {
public:
    ScalePoint();
    ~ScalePoint();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
