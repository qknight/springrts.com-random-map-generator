
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

Module::Module(Model* model, QPersistentModelIndex index) : QGraphicsItem(), GraphicsItemModelExtension(model, index) {
    dataChanged();
    this->model=model;
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
    QGraphicsTextItem* labelItem = new QGraphicsTextItem(m_label, this);
    labelItem->moveBy(-15,-25);
    
    //FIXME later remove the next line and the QGraphicsPixmapItem include
    icon = new QGraphicsPixmapItem(QPixmap(":perlin.png"), this);
    
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
          //FIXME PORT is no longer valid, needs another cast
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
  qDebug() << __PRETTY_FUNCTION__;
    QPoint modelPosition = modelData(customRole::PosRole).toPoint();
    if (modelPosition != pos()) {
        qDebug() << __PRETTY_FUNCTION__ << "position has changed! from" << modelPosition << " to " << pos();
        setModelData(pos(), customRole::PosRole);
    } else {
      qDebug() << __PRETTY_FUNCTION__ << "position has NOT changed!";
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
}

void Module::createLayout() {
}
