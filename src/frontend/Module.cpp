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

Module::Module(Model* model, QPersistentModelIndex item) : QGraphicsItem(), GraphicsItemModelExtension(model, item) {
  updateData();
  setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
  QGraphicsTextItem* labelItem = new QGraphicsTextItem(m_label, this);
//   labelItem->setVisible(true);
  labelItem->moveBy(-15,-25);
  
  createPorts(model,item);
  w=100;
  h=120;
  x=0;
  y=0;

}

Module::~Module() {
  // FIXME we should remove all ports, this check should be relocated to the ports instead
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
    qDebug() << __PRETTY_FUNCTION__ << " FIXME: critical error -> this section should never be called!!! Read the comments in the code above this error string!";
    exit(1);
  }
}

// void Module::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ){ }

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
  m_label = modelData(Qt::DisplayRole).toString();
}

/*!
 * when a new Module is created on the GraphicsScene we need to add ports to the 
 * module. Connections are added later, from Port to Port
 */
void Module::createPorts(Model* model, QPersistentModelIndex item) {
  // inputs
  for (int i=0; i < modelData(customRole::InputsRole).toInt(); ++i) {
    Port* p = new Port(model, item, PortType::INPUT, i, this);  
    ports.push_back(p);
    p->moveBy(-10,20+i*40);
  }
  
  // modputs
  for (int i=0; i < modelData(customRole::ModputsRole).toInt(); ++i) {
    Port* p = new Port(model, item, PortType::MODPUT, i, this);  
    ports.push_back(p);
    p->moveBy(50+i*20,130);
  }
  
  // outputs
  for (int i=0; i < modelData(customRole::OutputsRole).toInt(); ++i) {
    Port* p = new Port(model, item, PortType::OUTPUT, i, this);  
    ports.push_back(p);
    p->moveBy(110,20+i*40);
  }
}

Port* Module::resolvePort(int portType, int portNumber) {
  if (ports.size()) {
    foreach(Port* p, ports) {
      if (p->porttype() == portType && p->portnumber() == portNumber)
        return p;
    }
  }
  qDebug() << __PRETTY_FUNCTION__ << "FATAL: there is no such port item!, exiting";
  exit(1);
  return NULL;
}

