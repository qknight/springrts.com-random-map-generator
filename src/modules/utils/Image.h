#ifndef UTILS_IMAGE__HH
#define UTILS_IMAGE__HH

#include <DataAbstractModule.h>

#define ID "Utils::Image"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Image : public DataAbstractModule {
public:
    Image();
    ~Image();

    QString identify();
};

#endif
