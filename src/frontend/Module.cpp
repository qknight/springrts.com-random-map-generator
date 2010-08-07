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
    updateData();
    this->model=model;
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    QGraphicsTextItem* labelItem = new QGraphicsTextItem(m_label, this);
    labelItem->moveBy(-15,-25);

    w=100;
    h=120;
    x=0;
    y=0;
}

Module::~Module() {
//     qDebug() << __PRETTY_FUNCTION__;
}

// void Module::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ){ }

QVariant Module::itemChange ( GraphicsItemChange change, const QVariant & value ) {
    switch (change) {
    case QGraphicsItem::ItemSceneChange:
//         createLayout();
        break;
        m_pos =  modelData ( customRole::PosRole ).toPoint();
    default:
        break;
    }
    return value;
}

QRectF Module::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(x - penWidth / 2, y - penWidth / 2,
                  w + penWidth / 2, h + penWidth / 2);
}

void Module::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (isSelected()) {
        painter->save();
        QBrush b(QColor(Qt::red));
        painter->setBrush(b);
        painter->drawRect(x, y, w, h);
        painter->restore();
    }
    painter->drawRect(x, y, w, h);
}

void Module::updateData() {
    m_label = modelData( Qt::DisplayRole ).toString();
    m_pos =  modelData ( customRole::PosRole ).toPoint();
    setPos ( m_pos );
}

void Module::createLayout() {
}
