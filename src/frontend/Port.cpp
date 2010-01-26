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

Port::Port ( Model* model, QPersistentModelIndex item, int portType, int portNumber, QGraphicsItem * parent ) :
        QGraphicsItem ( parent ), GraphicsItemModelExtension ( model, item ) {
    m_portType=portType;
    m_portNumber=portNumber;
}

QVariant Port::itemChange ( GraphicsItemChange change, const QVariant & value ) {
    if ( change == QGraphicsItem::ItemPositionChange ) {
        foreach ( Connection *c, connections ) {
            c->updatePosition();
        }
    }
    return value;
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

    QBrush b ( QColor ( Qt::green ) );

    painter->setBrush ( b );
    painter->setPen ( p );
    QPainterPath* mypath = new QPainterPath;
    mypath->addEllipse ( -10, -10, 20, 20 );
    painter->drawPath ( *mypath );

    painter->setPen ( oldpen );
    painter->setBrush ( oldbrush );
}

Port::~Port() {

}

int Port::porttype() {
    return m_portType;
}
int Port::portnumber() {
    return m_portNumber;
}

