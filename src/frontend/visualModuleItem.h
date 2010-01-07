//
// C++ Interface: visualModuleItem
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef VISUALMODULEITEM_H
#define VISUALMODULEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "modulePort.h"
/**
	@author Joachim Schiele <js@lastlog.de>
*/
class visualModuleItem : public QGraphicsItem
{
  public:
    visualModuleItem();
    ~visualModuleItem();
  private:
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//     QUuid id(forwarder_to_real_class);
//     QString label();
//     int in_connections(int type);
//     int out_connections(int type);
//  signals:
//    inConnectionChanged();
//    outConnectionChanged();
    int w;
    int h;
    int x;
    int y;

  protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif
