
//
// C++ Implementation: Module
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "Model.h"
#include "Module.h"
#include "Port.h"
#include <DataAbstractModule.h>

Module::Module(Model* model, QPersistentModelIndex index, ObjectPool* pool) : QGraphicsItem(), GraphicsItemModelExtension(model, index, pool) {
    qDebug() << __PRETTY_FUNCTION__;
    int child_count = model->rowCount(index);
    int in=0, mod=0, out=0;
    for (int i = 0; i < child_count; ++i) {
        QPersistentModelIndex child = model->index(i, 0, index);

        // 1. is it a property? if so we skip right here!
        if (model->data(child, customRole::TypeRole) == DataItemType::PROPERTY)
            continue;

        // 2. create a new Port class object and assign it as child to the parent P
        unsigned int portDirection = model->data(child, customRole::PortDirection).toInt();
        unsigned int portType = model->data(child, customRole::PortType).toInt();
//         unsigned int portNumber = model->data(child, customRole::PortNumber).toInt();
        Port* port = new Port(model, child, portDirection, portType, i, pool, this);
        port->setParentItem ( this );

        // WARNING: this implementation expects the ports to be ordered by portNumber
        switch (portDirection) {
        case PortDirection::IN:
            port->moveBy(-10,20+(in++)*40);
            break;
        case PortDirection::MOD:
            port->moveBy(50+20*(mod++),130);
            break;
        case PortDirection::OUT:
            port->moveBy(130,20+(out++)*40);
            break;
        default:
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "no case matched";
            break;
        }
    }

    dataChanged();
    
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    QGraphicsTextItem* labelItem = new QGraphicsTextItem(m_label, this);
    labelItem->moveBy(-15,-25);
    
   
    w=120;
    h=120;
    x=0;
    y=0;
}

Module::~Module() {
//     qDebug() << __PRETTY_FUNCTION__;
}

QVariant Module::itemChange ( GraphicsItemChange change, const QVariant & value ) {
    Port* p;
    switch (change) {
    case QGraphicsItem::ItemPositionHasChanged:
    case QGraphicsItem::ItemPositionChange:
        foreach ( QGraphicsItem *g, childItems()) {
            if (g->type() == DataItemType::EXTENDEDGRAPHICSITEM) {
              GraphicsItemModelExtension* eitem = dynamic_cast<GraphicsItemModelExtension*>(g);
              if (eitem->customType() == DataItemType::PORT) {
//                 qDebug() << __PRETTY_FUNCTION__ << "port->updateConnections()";
                p = qgraphicsitem_cast<Port*> ( g );
                if (p == NULL)
                    qDebug() << __PRETTY_FUNCTION__ << "the child port is not there anymore, is it?";
                else
                    p->updateConnections();
              }
            }
        }
        break;
    default:
        break;
    }
    return value;
}

void Module::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ) {
//   qDebug() << __PRETTY_FUNCTION__;
    QPoint modelPosition = modelData(customRole::PosRole).toPoint();
    if (modelPosition != pos()) {
//         qDebug() << __PRETTY_FUNCTION__ << "position has changed! from" << modelPosition << " to " << pos();
        setModelData(pos(), customRole::PosRole);
    } else {
//       qDebug() << __PRETTY_FUNCTION__ << "position has NOT changed!";
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

QRectF Module::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(x - penWidth / 2, y - penWidth / 2,
                  w + penWidth / 2, h + penWidth / 2);
}

void Module::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (isSelected()) {
        painter->save();
        QPen p = QPen ( QColor ( "red" ), 4, Qt::DashLine );
        painter->setPen(p);
        painter->drawRect(x, y, w, h);
        painter->restore();
    }
    painter->drawRect(x, y, w, h);
}

void Module::dataChanged() {
//     qDebug() << __PRETTY_FUNCTION__;
    m_label = modelData( Qt::DisplayRole ).toString();
    QPoint modelPosition = modelData ( customRole::PosRole ).toPoint();
//     qDebug() << __PRETTY_FUNCTION__ << modelPosition;
    if (modelPosition != pos()) {
        setPos( modelPosition );
    }

    if (modelData (customRole::ReadyRole).toBool())
      icon = new QGraphicsPixmapItem(QPixmap(":perlin.png"), this);
    else
      icon = new QGraphicsPixmapItem(QPixmap(":unknown.png"), this);
}

void Module::createLayout() {
}
