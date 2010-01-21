#include <QtGui>

#include "Connection.h"
#include <math.h>

const qreal Pi = 3.14;

Connection::Connection(Port *startItem, Port *endItem, QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Connection::boundingRect() const
{
//     qreal extra = (pen().width() + 20) / 2.0;

/*    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);*/
/*    myStartItem;
    myEndItem;*/
//   qDebug("TODO boundingRect, Connection");
  return QRectF(-2000,-2000,4000,4000);
}

QPainterPath Connection::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Connection::updatePosition() {
    QRectF(mapFromItem(myStartItem, 0, 0)-QPointF(120,0),mapFromItem(myEndItem, 0, 0)+QPointF(120,0));

/*    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);*/
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
//   qDebug("redraw");

    if (myStartItem->collidesWithItem(myEndItem))
        return;
    QPointF n;
    if (myStartItem->parentItem() != 0)
      n = myStartItem->parentItem()->pos();
    QPointF m;
    if (myEndItem->parentItem() != 0)
      m = myEndItem->parentItem()->pos();

    QPointF beginPoint = myEndItem->pos()+m;
    QPointF endPoint = myStartItem->pos()+n;

    QLineF z = QLineF(beginPoint,endPoint);
    setLine(z);

//     painter->drawLine(z);
//     int stretch_ = 0.6 * -(beginPoint.x()-endPoint.x());
    int stretch= qAbs(0.6 * -(beginPoint.x()-endPoint.x()));
    QPainterPath myPath(QPoint(beginPoint.x(),beginPoint.y()));
    myPath.cubicTo(beginPoint+QPoint(stretch,0),endPoint-QPoint(stretch,0),QPoint(endPoint.x(),endPoint.y()));
    painter->drawPath(myPath);
}
