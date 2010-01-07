//
// C++ Interface: modulePort
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

#include "modulePortConnection.h"

class modulePortConnection;
/**
	@author Joachim Schiele <js@lastlog.de>
*/
class modulePort : public QGraphicsItem
{
  public:
    QVector<modulePortConnection*> arrows;
  public:
    modulePort(QGraphicsItem * parent = 0);
    ~modulePort();
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);
    QRectF boundingRect() const;
  protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif
