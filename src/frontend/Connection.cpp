#include <QtGui>

#include "Connection.h"
#include <math.h>
#include <PortTypes.h>

/*!
 * adds a graphical representation (see Connection.cpp/.h) spanning from
 * Port a to Port b (see Port.cpp/.h)
 * this function is called by the QAbstractItemModel after a connection has been inserted
 */
Connection::Connection(Model* model, QPersistentModelIndex index, ObjectPool* pool, QGraphicsItem* parent)
        : QGraphicsPathItem(parent), GraphicsItemModelExtension(model, index, pool)
{
//     qDebug() << __PRETTY_FUNCTION__;

    // 0. dst QPersistentModelIndex (that is to be queried via the model)
    QPersistentModelIndex sPortIndex = index.parent();
    QPersistentModelIndex dPortIndex = QPersistentModelIndex(model->dst(index));

    Port* srcPort = dynamic_cast<Port*> ( pool->model2GraphicsItem ( sPortIndex ) );
    Port* dstPort = dynamic_cast<Port*> ( pool->model2GraphicsItem ( dPortIndex ) );

    if (srcPort == NULL || dstPort == NULL || srcPort == dstPort) {
        if (srcPort == NULL)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == NULL";
        if (dstPort == NULL)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "dstModule == NULL";
        if (srcPort == dstPort)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == dstModule";
        exit(1);
    }

    m_sPort = srcPort;
    m_dPort = dstPort;
    
    m_suspendsrcPort = false;
    m_suspenddstPort = false;
    
    m_dPortDirection = m_dPort->portDirection();
    m_sPortDirection = m_sPort->portDirection();
    
    m_sPort->addReference(this);
    m_dPort->addReference(this);

    updatePosition();
    
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-20);
}

void Connection::suspend(Port* p) {
  if (p == m_sPort)
   m_suspendsrcPort = true;
  if (p == m_dPort)
    m_suspenddstPort = true;
}

Connection::~Connection() {
//     qDebug() << __PRETTY_FUNCTION__;
    if (!m_suspendsrcPort)
      m_sPort->delReference(this);
    if (!m_suspenddstPort)
      m_dPort->delReference(this);
}

void Connection::updatePosition() {
    if (m_suspendsrcPort || m_suspenddstPort)
      return;

    QPointF n;
    if (m_sPort->parentItem() != 0)
        n = m_sPort->parentItem()->pos();
    QPointF m;
    if (m_dPort->parentItem() != 0)
        m = m_dPort->parentItem()->pos();

    srcParentPosition = n;
    srcPosition = m_sPort->pos();
    dstParentPosition = m;
    dstPosition = m_dPort->pos();

    setPath(connectionPath());
}

/*! increases the clickable range for item selection, when clicking near the line in a QGraphicsView */
QPainterPath Connection::shape() const {
    QPainterPathStroker s;
    s.setWidth ( 20 );
    QPainterPath p = connectionPath();
    QPainterPath path = s.createStroke ( p );
    return path;
}

QPainterPath Connection::connectionPath() const {
    QPointF beginPoint = dstParentPosition + dstPosition;
    QPointF endPoint = srcParentPosition + srcPosition;
    
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
}

void Connection::dataChanged() {
    //nothing to do here, since port(s) do not have a specific role except being connectable
}
