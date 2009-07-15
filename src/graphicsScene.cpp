//
// C++ Implementation: graphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "graphicsScene.h"

graphicsScene::graphicsScene() : QGraphicsScene() {
    connect(&menu,SIGNAL(triggered(QAction*)),
            this, SLOT(menuSelectionMade(QAction*)));
}

graphicsScene::~graphicsScene() { }

void graphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
  screenPos = contextMenuEvent->screenPos();
  menu.exec(contextMenuEvent->screenPos());
}

void graphicsScene::appendToQMenuBox(QString ModuleID) {
  menu.addAction(ModuleID);
}

void graphicsScene::menuSelectionMade(QAction* action) {
//   qDebug() << "creating module: " << action->text();
  emit createModule(action->text(), screenPos);
}


