#include "GraphicsItemRelayInterface.h"
#include "GraphicsItemRelay.h"

GraphcisItemRelayInterface::GraphcisItemRelayInterface(){};

GraphcisItemRelayInterface::~GraphcisItemRelayInterface() {
    foreach(GraphicsItemRelay* r, relays) {
        delete r;
    }
}

void GraphcisItemRelayInterface::addRelay(GraphicsItemRelay* r) {
//       qDebug() << __PRETTY_FUNCTION__;
    relays.push_back(r);
}


void GraphcisItemRelayInterface::delRelay(GraphicsItemRelay* r) {
//   qDebug() << __PRETTY_FUNCTION__;
    int i = relays.removeAll(r);

    if (i <= 0)
        qDebug() << __PRETTY_FUNCTION__ << "ERROR: no connection was removed?";
}