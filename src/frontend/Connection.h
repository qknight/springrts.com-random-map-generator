
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
    Connection(Model* model, QPersistentModelIndex index, Port *sPort, Port *dPort,
      QGraphicsItem *parent = 0);
    ~Connection();
      void updateData();
    int type() const
        { return DataItemType::CONNECTION; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color)
        { myColor = color; }
    Port *startItem() const
        { return myStartItem; }
    Port *endItem() const
        { return myEndItem; }
    void suspendDrawing();



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
