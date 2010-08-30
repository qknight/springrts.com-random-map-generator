#include "GraphicsItemRelay.h"
#include "Port.h"
#include "Connection.h"

GraphicsItemRelay::GraphicsItemRelay(Port* p, Connection* c) {
    qDebug() << __PRETTY_FUNCTION__;
    // grabe the current position of m->screenPos() and update c with that
    m_connection = c;
    m_port = p;
    m_connection->addRelay(this);
    m_port->addRelay(this);
    updatePosition(m_port->scenePos());
}
GraphicsItemRelay::~GraphicsItemRelay() {
//     qDebug() << __PRETTY_FUNCTION__;
    m_connection->delRelay(this);
    m_port->delRelay(this);
}

void GraphicsItemRelay::updatePosition(QPointF pos) {
//     qDebug() << __PRETTY_FUNCTION__ << pos;
    m_pos = pos;
    m_connection->updatePosition();
}

QPointF GraphicsItemRelay::pos() {
    return m_pos;
}
