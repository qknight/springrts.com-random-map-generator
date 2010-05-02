#ifndef PORTTYPE_H
#define PORTTYPE_H

namespace PortType {
    // the idea behind yet another type identifier is that we map the types below via the model to the
    // types defined in DataAbstractItem.h (see DataItemType in DataAbstractItem.h)
    enum PortType {
        INPUT,
        MODPUT,
        OUTPUT
    };
}

#endif