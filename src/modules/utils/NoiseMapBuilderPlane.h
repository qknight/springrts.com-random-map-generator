#ifndef UTILS_NOISEMAPBUILDERPLANE__HH
#define UTILS_NOISEMAPBUILDERPLANE__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Utils::NoiseMapBuilderPlane"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class NoiseMapBuilderPlane : public DataAbstractModule {
public:
    NoiseMapBuilderPlane();
    ~NoiseMapBuilderPlane();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
