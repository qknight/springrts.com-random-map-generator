
#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include "Port.h"
#include "GraphicsItemModelExtension.h"

class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Port;

class Connection : public QGraphicsLineItem, public GraphicsItemModelExtension {
public:
    Connection(QPersistentModelIndex index, Model* model, Port *startItem, Port *endItem,
      QGraphicsItem *parent = 0);
      void updateData();
    int type() const
        { return DataType::CONNECTION; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color)
        { myColor = color; }
    Port *startItem() const
        { return myStartItem; }
    Port *endItem() const
        { return myEndItem; }


public slots:
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    Port *myStartItem;
    Port *myEndItem;
    QColor myColor;
    QPolygonF arrowHead;
};

#endif