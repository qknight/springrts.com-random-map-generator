#ifndef TRANSFORMER_TRANSLATEPOINT__HH
#define TRANSFORMER_TRANSLATEPOINT__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Transformer::TranslatePoint"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class TranslatePoint : public DataAbstractModule {
public:
    TranslatePoint();
    ~TranslatePoint();

    QString identify();
    NoiseNetwork* network();
};

#endif
