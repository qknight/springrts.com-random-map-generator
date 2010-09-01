#ifndef CONNECTION__HH
#define CONNECTION__HH

#include <QGraphicsPathItem>
#include "Port.h"
#include "GraphicsItemModelExtension.h"
#include "GraphicsItemRelayInterface.h"

class QRectF;
class QPainterPath;

class Connection : public QGraphicsPathItem, public GraphicsItemModelExtension, public GraphcisItemRelayInterface {
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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    QPainterPath connectionPath() const;
    QColor myColor;
    QPointF srcPosition;
    QPointF dstPosition;
    int m_dPortDirection;
    int m_sPortDirection;
};

#endif
