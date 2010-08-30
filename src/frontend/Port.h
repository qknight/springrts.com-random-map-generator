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
#include <QDebug>
#include "GraphicsItemModelExtension.h"

class GraphicsItemRelay;
class Connection;

/**
  @author Joachim Schiele <js@lastlog.de>
*/
class Port : public QGraphicsItem, public GraphicsItemModelExtension {
public:
    QList<Connection*> connections;
public:
    Port( Model* model, QPersistentModelIndex index, int portDirection, int portType, int portNumber, ObjectPool* pool, QGraphicsItem * parent = 0);
    ~Port();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QRectF boundingRect() const;
    
    void addRelay(GraphicsItemRelay* r);
    void delRelay(GraphicsItemRelay* r);
    
    // -> see DataItemType.h
    int portType();
    int portNumber();
    int portDirection();
    
    void updateConnections();

    int orientation;
    void dataChanged() {};
    int type() const {
        return GraphicsItemModelExtension::type();
    }
    int customType() const
         { return DataItemType::PORT; }
private:
    QList<GraphicsItemRelay*> relays;
    int m_portType;
    int m_portNumber;
    int m_portDirection;
};

#endif
