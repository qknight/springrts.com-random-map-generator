//
// C++ Interface: Module
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MODULE_H
#define MODULE_H

#include <QGraphicsItem>
#include <QPersistentModelIndex>
#include <QPainter>
#include <QDebug>

#include "GraphicsItemModelExtension.h"

class Port;

/*!
 *  @author Joachim Schiele <js@lastlog.de>
 */
class Module : public QGraphicsItem, public GraphicsItemModelExtension {
public:
    Module(Model* model, QPersistentModelIndex index);
    ~Module();
    void updateData();
    
private:
    void createLayout();
    QVector<Port*> ports;
    Model* model;
    QString m_label;
    int type() const {
        return DataItemType::MODULE;
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    int w;
    int h;
    int x;
    int y;
};

#endif
