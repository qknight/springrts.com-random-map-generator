//
// C++ Interface: graphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMenu>
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include "ModuleFactory.h"

/**
  @author Joachim Schiele <js@lastlog.de>
*/

class ModuleFactory;

class graphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    graphicsScene();
//     ~graphicsScene();
private:
    //FIXME this should be done using the model
    ModuleFactory* moduleFactory;
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    ModuleFactory* Instance();
    QMenu menu;
    QPoint screenPos;
public slots:
    void menuSelectionMade(QAction* action);
};

#endif
