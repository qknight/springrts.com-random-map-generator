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
#include "GraphicsItemModelExtension.h"

class Connection;

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Port : public QGraphicsItem, public GraphicsItemModelExtension
{
  public:
    QVector<Connection*> connections;
  public:
    Port( Model* model, QPersistentModelIndex item, QGraphicsItem * parent = 0);
    ~Port();
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);
    QRectF boundingRect() const;
    // input=0, modput=1, output=2
    int orientation;
  protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif