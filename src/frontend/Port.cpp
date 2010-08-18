//
// C++ Implementation: Port
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Port.h"
#include "Connection.h"
#include <PortTypes.h>

Port::Port ( Model* model, QPersistentModelIndex index, int portDirection, int portType, int portNumber, QGraphicsItem* parent ) :
        QGraphicsItem ( parent ), GraphicsItemModelExtension ( model, index ) {
//     qDebug() << __PRETTY_FUNCTION__;
    m_portType=portType;
    m_portNumber=portNumber;
    m_portDirection=portDirection;
}

Port::~Port() {
    qDebug() << __PRETTY_FUNCTION__;
// a Port MUST NOT contain childItems (connections) when being removed, Model::removeRows(..) should have removed already
  if (childItems().size()) {
    qDebug() << __PRETTY_FUNCTION__ << " CRITICAL ERROR: ~Port() removed, while connections are still existing";
    exit(1);
  }
}

void Port::updateConnections() {
      qDebug() << __PRETTY_FUNCTION__;
    foreach ( Connection *c, connections ) {
        c->updatePosition();
    }
}

void Port::addReference(Connection* c) {
  connections.push_back(c);
}

void Port::delReference(Connection* c) {
  qDebug() << __PRETTY_FUNCTION__;
  qDebug() << connections.size();
  int i = connections.removeAll(c);

  if (i <= 0)
    qDebug() << __PRETTY_FUNCTION__ << "ERROR: no connection was removed?";
}

QRectF Port::boundingRect() const {
    qreal penWidth = 1;
    return QRectF ( -10 - penWidth / 2, -10 - penWidth / 2,
                    20 + penWidth / 2, 20 + penWidth / 2 );
}

void Port::paint ( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )     {
    QPen oldpen = painter->pen();
    QPen p ( Qt::black, 1 );
    QBrush oldbrush = painter->brush();
    QRadialGradient gradient ( 50, 50, 50, 50, 50 );
    gradient.setColorAt ( 0, QColor::fromRgbF ( 0, 1, 0, 1 ) );
    gradient.setColorAt ( 1, QColor::fromRgbF ( 0, 0, 0, 0 ) );
    // FIXME instead of saving the pan using a variable, maybe use the painter save/load stack?
    QBrush b;
    switch (m_portDirection) {
      case PortDirection::OUT:
        b = QColor ( Qt::green );
        break;
    case PortDirection::MOD:
        b = QColor ( Qt::red );
        break;
    case PortDirection::IN:
        b = QColor ( Qt::blue );
        break;
    default:
        b = QColor ( Qt::black );
    }

    painter->setBrush ( b );
    painter->setPen ( p );
    QPainterPath* mypath = new QPainterPath;
    mypath->addEllipse ( -10, -10, 20, 20 );
    painter->drawPath ( *mypath );

    painter->setPen ( oldpen );
    painter->setBrush ( oldbrush );
}

int Port::portType() {
    return m_portType;
}
int Port::portNumber() {
    return m_portNumber;
}
int Port::portDirection() {
    return m_portDirection;
}
