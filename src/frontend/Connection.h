#ifndef CONNECTION__HH
#define CONNECTION__HH

#include <QGraphicsPathItem>
#include "Port.h"
#include "GraphicsItemModelExtension.h"

class QGraphicsLineItem;
class QRectF;
class QPainterPath;
class GraphicsItemRelay;

class Connection : public QGraphicsPathItem, public GraphicsItemModelExtension {
  friend class GraphicsItemRelay;
public:
    Connection(Model* model, QPersistentModelIndex index, ObjectPool* pool);
    ~Connection();
    void dataChanged();
    int type() const {
        return GraphicsItemModelExtension::type();
    }
    int customType() const
    {
        return DataItemType::CONNECTION;
    }
    QPainterPath shape() const;
    void setColor(const QColor &color)
    {
        myColor = color;
    }
    void updatePosition();
protected:
    void addRelay(GraphicsItemRelay* r);
    void delRelay(GraphicsItemRelay* r);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    QList<GraphicsItemRelay*> relays;
    QPainterPath connectionPath() const;
    QColor myColor;
    QPointF srcPosition;
    QPointF dstPosition;
    int m_dPortDirection;
    int m_sPortDirection;
};

#endif
