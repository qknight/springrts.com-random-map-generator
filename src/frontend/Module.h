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

#include "Model.h"
#include "GraphicsItemModelExtension.h"

class Port;

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class Module : public QGraphicsItem, public GraphicsItemModelExtension {
  public:
    Module(QPersistentModelIndex item, Model* model);
    ~Module();
  private:
    QPersistentModelIndex m_item;
    QString m_label;
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
