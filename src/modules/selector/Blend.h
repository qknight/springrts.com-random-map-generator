
#ifndef SELECTOR_BLEND__HH
#define SELECTOR_BLEND__HH

#include <DataAbstractModule.h>

#define ID "Selector::Blend"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Blend : public DataAbstractModule {
public:
    Blend();
    ~Blend();

    QString identify();
};

#endif
