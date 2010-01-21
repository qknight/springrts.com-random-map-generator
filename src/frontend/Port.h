//
// C++ Interface: Port
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPHICSMODULEPORT_H
#define GRAPHICSMODULEPORT_H

#include <QGraphicsItem>
#include <QPainter>

class Connection;

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Port : public QGraphicsItem
{
  public:
    QVector<Connection*> arrows;
  public:
    Port(QGraphicsItem * parent = 0);
    ~Port();
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);
    QRectF boundingRect() const;
  protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif
