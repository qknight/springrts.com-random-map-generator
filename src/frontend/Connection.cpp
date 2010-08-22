#include <QtGui>

#include "Connection.h"
#include <math.h>
#include <PortTypes.h>

Connection::Connection(Model* model, QPersistentModelIndex index, Port *sPort, Port *dPort, QGraphicsItem *parent)
        : QGraphicsPathItem(parent), GraphicsItemModelExtension(model, index)
{
//     qDebug() << __PRETTY_FUNCTION__;
    m_sPort = sPort;
    m_dPort = dPort;
    
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
