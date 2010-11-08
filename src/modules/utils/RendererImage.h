#ifndef UTILS_RENDERERIMAGE__HH
#define UTILS_RENDERERIMAGE__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Utils::RendererImage"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class RendererImage : public DataAbstractModule {
public:
    RendererImage();
    ~RendererImage();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
