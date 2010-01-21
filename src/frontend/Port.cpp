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

Port::Port(QGraphicsItem * parent) : QGraphicsItem(parent) {
}

QVariant Port::itemChange ( GraphicsItemChange change, const QVariant & value ){
    if (change == QGraphicsItem::ItemPositionChange) {
      foreach (Connection *arrow, arrows) {
        arrow->updatePosition();
      }
    }
  return value;
}

QRectF Port::boundingRect() const {
         qreal penWidth = 1;
         return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                       20 + penWidth / 2, 20 + penWidth / 2);
}

void Port::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)     {
  QPen oldpen = painter->pen();
  QPen p(Qt::black, 1);
  QBrush oldbrush = painter->brush();
  QRadialGradient gradient(50, 50, 50, 50, 50);
  gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
  gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));

  QBrush b(QColor(Qt::green));

  painter->setBrush(b);
  painter->setPen(p);
  QPainterPath* mypath = new QPainterPath;
  mypath->addEllipse(-10, -10, 20, 20);
  painter->drawPath(*mypath);

  painter->setPen(oldpen);
  painter->setBrush(oldbrush);
}

Port::~Port(){

}


