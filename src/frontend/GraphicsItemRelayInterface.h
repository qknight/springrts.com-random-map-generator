#ifndef GRAPHICSITEMRELAYINTERFACE_H
#define GRAPHICSITEMRELAYINTERFACE_H

#include <QList>
#include <QDebug>

class GraphicsItemRelay;

class GraphcisItemRelayInterface {
  friend class GraphicsItemRelay;
  protected:
    void addRelay(GraphicsItemRelay* r);
    void delRelay(GraphicsItemRelay* r);
    GraphcisItemRelayInterface();
    ~GraphcisItemRelayInterface();
    QList<GraphicsItemRelay*> relays;
};

#endif