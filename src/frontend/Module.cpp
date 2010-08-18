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
    qDebug() << __PRETTY_FUNCTION__;
}

QVariant Module::itemChange ( GraphicsItemChange change, const QVariant & value ) {
    Port* p;
    switch (change) {
    case QGraphicsItem::ItemPositionHasChanged:
        // this is used to sync the module position in the GraphicsView with the model data
        setModelData(oldPosition, customRole::PosRole);
    case QGraphicsItem::ItemPositionChange:
        foreach ( QGraphicsItem *g, childItems()) {
            if (g->type() == DataItemType::PORT) {
                qDebug() << __PRETTY_FUNCTION__ << "port->updateConnections()";
                p = qgraphicsitem_cast<Port*> ( g );
                if (p == NULL)
                    qDebug() << __PRETTY_FUNCTION__ << "the child port is not there anymore, is it?";
                else
                    p->updateConnections();
            }
        }
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
        QPen p = QPen ( QColor ( "red" ), 4, Qt::DashLine );
        painter->setPen(p);
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
