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
#include "Module.h"
#include "Port.h"

Module::Module(Model* model, QPersistentModelIndex item) : QGraphicsItem(), GraphicsItemModelExtension(model, item) {
  setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
  w=100;
  h=120;
  x=0;
  y=0;
  updateData();
}

Module::~Module() {
  if (children().size() > 0) {
    // when removing a graphical item, this must always be done from the lower layer (by the Model)
    // WARNING this comment might be wrong, didn't check it yet 2010-01-06 (js)
    // example: removing a object which has 2 connections from the gui involves:
    //          1. send the remove request from the gui to the object visualized by the gui
    //          2. first remove all connections, say we have 2 connections
    //          2. 1 remove the first connection, which then removes the visual connection item first
    //             next removes the connection from the referencing object (maybe be two objects or more)
    //          2. 2. do this for all connections
    //          3. when all references (connections) are removed, remove the visual item (gui counterpart)
    //          4. next remove the actual item (maybe a noisegen for instance)
    //          5. now we are set and since we don't have loops this should be quite easy
    qDebug() << "FIXME: critical error -> this section should never be called!!! Read the comments in the code above this error string!";
    exit(1);
  }
}

void Module::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ){ }

QVariant Module::itemChange ( GraphicsItemChange change, const QVariant & value ){
    if (change == QGraphicsItem::ItemPositionChange) {
//       foreach (QGraphicsItem* child, children()) {
//         modulePort* child_ = static_cast<modulePort*>(child);
//         child_->updatePosition();
//         qDebug("move?");
//       }
    }
  return value;
}

QRectF Module::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(x - penWidth / 2, -15 + y - penWidth / 2,
                  30+w + penWidth / 2, 15 + h + penWidth / 2);
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
  painter->drawText(QPoint(0,0),m_label);
}

void Module::updateData() {
  m_label = modelData(Qt::DisplayRole).toString();
}
