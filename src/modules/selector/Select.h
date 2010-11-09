#ifndef SELECTOR_SELECT__HH
#define SELECTOR_SELECT__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Selector::Select"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Select : public DataAbstractModule {
public:
    Select();
    ~Select();

    QString identify();
    NoiseNetwork* network();
};

#endif
