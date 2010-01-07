/****************************************************************************
**
** Copyright (C) 2007-2007 Trolltech ASA. All rights reserved.
**
** This file is part of the example classes of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.0, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** In addition, as a special exception, Trolltech, as the sole copyright
** holder for Qt Designer, grants users of the Qt/Eclipse Integration
** plug-in the right for the Qt/Eclipse Integration to link to
** functionality provided by Qt Designer and its related libraries.
**
** Trolltech reserves all rights not expressly granted herein.
**
** Trolltech ASA (c) 2007
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#include <QtGui>

#include "modulePortConnection.h"
#include <math.h>

const qreal Pi = 3.14;

modulePortConnection::modulePortConnection(modulePort *startItem, modulePort *endItem,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF modulePortConnection::boundingRect() const
{
//     qreal extra = (pen().width() + 20) / 2.0;

/*    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);*/
/*    myStartItem;
    myEndItem;*/
//   qDebug("TODO boundingRect, modulePortConnection");
  return QRectF(-2000,-2000,4000,4000);
}

QPainterPath modulePortConnection::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void modulePortConnection::updatePosition() {
    QRectF(mapFromItem(myStartItem, 0, 0)-QPointF(120,0),mapFromItem(myEndItem, 0, 0)+QPointF(120,0));

/*    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);*/
}

void modulePortConnection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
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
