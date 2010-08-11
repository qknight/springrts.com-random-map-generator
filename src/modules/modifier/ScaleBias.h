
#ifndef MODIFIER_SCALEBIAS__HH
#define MODIFIER_SCALEBIAS__HH

#include <DataAbstractModule.h>

#define ID "Modifier::ScaleBias"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class ScaleBias : public DataAbstractModule {
public:
    ScaleBias();
    ~ScaleBias();

    QString identify();
};

#endif
