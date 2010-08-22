#ifndef CONNECTION__HH
#define CONNECTION__HH

#include <QGraphicsPathItem>
#include "Port.h"
#include "GraphicsItemModelExtension.h"

class QGraphicsLineItem;
// class QGraphicsScene;
class QRectF;
class QPainterPath;

class Connection : public QGraphicsPathItem, public GraphicsItemModelExtension {
public:
    Connection(Model* model, QPersistentModelIndex index, Port *sPort, Port *dPort,
               QGraphicsItem *parent = 0);
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
    void suspend(Port* p);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    QPainterPath connectionPath() const;
    Port *m_sPort;
    Port *m_dPort;
    QColor myColor;
    QPointF srcParentPosition;
    QPointF srcPosition;
    QPointF dstParentPosition;
    QPointF dstPosition;
    int m_dPortDirection;
    int m_sPortDirection;
    bool m_suspendsrcPort;
    bool m_suspenddstPort;
};

#endif
