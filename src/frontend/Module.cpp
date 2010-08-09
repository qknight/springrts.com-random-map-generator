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
    setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemSendsGeometryChanges);
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
    case QGraphicsItem::ItemPositionChange:
//         qDebug() << "QGraphicsItem::ItemPositionChange";
        break;
    case QGraphicsItem::ItemPositionHasChanged:
//         qDebug() << "QGraphicsItem::ItemPositionHasChanged";
        oldPosition = value.toPoint();
        setModelData(oldPosition, customRole::PosRole);
        break;
    case QGraphicsItem::ItemSceneChange:
//         createLayout();
        m_pos =  modelData ( customRole::PosRole ).toPoint();
        break;
    case QGraphicsItem::ItemScenePositionHasChanged:
//       qDebug() << "QGraphicsItem::ItemScenePositionHasChanged";
      break;
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
    
    // a QGraphicsView may be used to move the Module. It is important to know if the move request was made
    // by the 
    //  - QGraphicsView (which then was visualized already) or by the 
    //  - QTreeView (in this case we move the item)
    // if not done this way this would create a loop
    qDebug() << "FIXME: this text should show up every time a Module has moved by (dx,dy) in either cases. See if the ItemView does updateData(..) for every changed QModelIndex";
    QPoint newPosition = modelData ( customRole::PosRole ).toPoint();
    if (newPosition != oldPosition)
      m_pos =  newPosition;
    setPos ( m_pos );
}

void Module::createLayout() {
}
