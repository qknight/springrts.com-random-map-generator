#include <QtGui>
#include <math.h>

#include "PortTypes.h"
#include "GraphicsItemRelay.h"
#include "Connection.h"
#include "GraphicsItemRelay.h"

/*!
 * adds a graphical representation (see Connection.cpp/.h) spanning from
 * Port a to Port b (see Port.cpp/.h)
 * this function is called by the QAb3stractItemModel after a connection has been inserted
 */
Connection::Connection(Model* model, QPersistentModelIndex index, ObjectPool* pool)
        : QGraphicsPathItem(), GraphicsItemModelExtension(model, index, pool), GraphcisItemRelayInterface()
{
    qDebug() << __PRETTY_FUNCTION__;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
//     setFlag(QGraphicsItem::ItemIsMovable, true);

    // 0. dst QPersistentModelIndex (that is to be queried via the model)
    QPersistentModelIndex sPortIndex = index.parent();
    QPersistentModelIndex dPortIndex = QPersistentModelIndex(model->dst(index));

    // do not store or use any Port* reference from here
    Port* srcPort = dynamic_cast<Port*> ( pool->model2GraphicsItem ( sPortIndex ) );
    Port* dstPort = dynamic_cast<Port*> ( pool->model2GraphicsItem ( dPortIndex ) );

    if (srcPort == dstPort) {
        qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == dstModule";
        exit(1);
    }
    if (srcPort == NULL) {
        qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == NULL";
    } else {
        new GraphicsItemRelay(srcPort, this);
    }
    if (dstPort == NULL) {
        qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "dstModule == NULL";
    } else {
        new GraphicsItemRelay(dstPort, this);
    }

    m_sPortDirection = model->data(sPortIndex, customRole::PortDirection).toInt();
    m_dPortDirection = model->data(dPortIndex, customRole::PortDirection).toInt();

    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-5);
}

Connection::~Connection() {
//     qDebug() << __PRETTY_FUNCTION__;
}

void Connection::updatePosition() {
    if (relays.size() == 2) {
        srcPosition = relays[0]->pos();
        dstPosition = relays[1]->pos();

        setPath(connectionPath());
        update();
    }
}

/*! increases the clickable range for item selection, when clicking near the line in a QGraphicsView */
QPainterPath Connection::shape() const {
    QPainterPathStroker s;
    s.setWidth ( 20 );
    QPainterPath p = connectionPath();
    QPainterPath path = s.createStroke ( p );
    return path;
}

// bool Connection::contains( const QPointF & point ) const {
//     bool z = shape().contains(point);
//     qDebug() << __PRETTY_FUNCTION__ << z << "isEnabled: " << isEnabled();
//     return z;
// }

QPainterPath Connection::connectionPath() const {
    QPointF beginPoint = dstPosition;
    QPointF endPoint = srcPosition;

    int stretch= qAbs(0.6 * -(beginPoint.x()-endPoint.x()));
    QPainterPath myPath(QPoint(beginPoint.x(),beginPoint.y()));
    QPointF xPoint;

    // draw modput connections (drawn downwards)
    if (m_dPortDirection != PortDirection::MOD)
        xPoint = beginPoint-QPoint(stretch,0);
    // draw input or output connection (horizontally orientation)
    else
        xPoint = beginPoint-QPoint(0,-stretch);
    myPath.cubicTo(xPoint,
                   endPoint+QPoint(stretch,0),
                   QPoint(endPoint.x(),endPoint.y()));
    return myPath;
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QPen p = QPen ( QColor ( "red" ), 4, Qt::DashLine );

    painter->drawPath ( connectionPath() );
    if ( isSelected() ) {
        painter->setPen ( p );
    }

    painter->drawPath ( connectionPath() );
    QPen p1 = QPen ( QColor ( "green" ), 1);
    painter->setPen(p1);
    painter->drawPath(shape());
}

void Connection::dataChanged() {
    //nothing to do here, since port(s) do not have a specific role except being connectable
}

void Connection::mousePressEvent ( QGraphicsSceneMouseEvent * event ) {
  qDebug() << "here";
//   QGraphicsItem::mousePressEvent(event);
  setSelected(true);
}

void Connection::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ) {
  qDebug() << "here2";
//   QGraphicsItem::mouseDoubleClickEvent(event);
//    mousePressEvent(event);
}

void Connection::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "here3";
//     QGraphicsItem::mouseReleaseEvent(event);
}