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

#include "GraphicsItemModelExtension.h"

class Port;

/*!
 *	@author Joachim Schiele <js@lastlog.de>
 */
class Module : public QGraphicsItem, public GraphicsItemModelExtension {
  public:
    Module(Model* model, QPersistentModelIndex index);
    ~Module();
    Port* resolvePort(int portType, int portNumber);
    QString m_label;
    QPoint m_pos;
  private:
    QVector<Port*> ports;
    Model* model;
   int type() const
    { return DataType::MODULE; }
//     void createPorts(Model* model, QPersistentModelIndex item);

    
//     void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void updateData();
    int w;
    int h;
    int x;
    int y;

  protected:
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
};

#endif
