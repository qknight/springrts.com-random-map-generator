#ifndef GENERATOR_CONST__HH
#define GENERATOR_CONST__HH

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "Generator::Const"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Const : public DataAbstractModule {
public:
    Const();
    ~Const();

    QString identify();
    NoiseNetwork* network();
};

#endif
