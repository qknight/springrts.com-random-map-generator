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
#include "PortTypes.h"
#include "GraphicsItemRelay.h"

Port::Port ( Model* model, QPersistentModelIndex index, int portDirection, int portType, int portNumber, ObjectPool* pool, QGraphicsItem* parent ) :
        QGraphicsItem ( parent ), GraphicsItemModelExtension ( model, index, pool ), GraphcisItemRelayInterface() {
    qDebug() << __PRETTY_FUNCTION__;

    // 0. collect all connections for this port
    QList<QModelIndex> v;
    for(int i = 0; i < model->rowCount(index); ++i) {
      v.push_back(model->index(i,0,index));
    }
    // 1. collect all reference-connections for this port
    v += model->references(index);
    
    // 2. now check for all connections/references if a GraphicsItemRelay is needed
    for(int i = 0; i < v.size(); ++i) {
      qDebug() << __PRETTY_FUNCTION__;
      QModelIndex cIndex = v[i];
      
      // if the connection does not yet have a frontend item representative, stop right here
      QGraphicsItem* cg = pool->model2GraphicsItem ( cIndex );
      if (cg == NULL)
        continue;
      
      Connection* dstConnection = dynamic_cast<Connection*> ( cg );
      new GraphicsItemRelay(this, dstConnection);
    }

    m_portType=portType;
    m_portNumber=portNumber;
    m_portDirection=portDirection;
}

Port::~Port() {
//     qDebug() << __PRETTY_FUNCTION__;
// a Port MUST NOT contain childItems (connections) when being removed, Model::removeRows(..) should have removed already
    if (childItems().size()) {
        qDebug() << __PRETTY_FUNCTION__ << " CRITICAL ERROR: ~Port() removed, while connections are still existing";
        exit(1);
    }
}

/*! called by Module to force a redraw of the Connection, after the position of the Module has changed */
void Port::updateConnections() {
    QPointF p = scenePos();
//     qDebug() << __PRETTY_FUNCTION__ << p;
    foreach (GraphicsItemRelay *r, relays ) {
        r->updatePosition(p);
    }
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
