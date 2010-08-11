
#ifndef TRANSFORMER_ROTATEPOINT__HH
#define TRANSFORMER_ROTATEPOINT__HH

#include <DataAbstractModule.h>

#define ID "Transformer::RotatePoint"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class RotatePoint : public DataAbstractModule {
public:
    RotatePoint();
    ~RotatePoint();

    QString identify();
};

#endif
