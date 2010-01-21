//
// C++ Interface: Module
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MODULE_H
#define MODULE_H

#include <QGraphicsItem>
#include <QPersistentModelIndex>
#include <QPainter>
#include <QDebug>

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Module : public QGraphicsItem {
  public:
    Module(QPersistentModelIndex item);
    ~Module();
  private:
    QPersistentModelIndex m_item;
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
