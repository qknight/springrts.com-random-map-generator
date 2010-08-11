
#ifndef TRANSFORMER_DISPLACE__HH
#define TRANSFORMER_DISPLACE__HH

#include <DataAbstractModule.h>

#define ID "Transformer::Displace"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Displace : public DataAbstractModule {
public:
    Displace();
    ~Displace();

    QString identify();
};

#endif
