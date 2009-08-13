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
    moduleFactory = ModuleFactory::Instance();
    connect(&menu,SIGNAL(triggered(QAction*)),
            this, SLOT(menuSelectionMade(QAction*)));
}

// graphicsScene::~graphicsScene() {}

void graphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    screenPos = contextMenuEvent->screenPos();
    // create menu
    menu.clear();
    QVector<QString> s = moduleFactory->LoadableModuleNames();
    for (int i=0; i < s.size(); i++) {
        menu.addAction(s[i]);
    }
    menu.exec(contextMenuEvent->screenPos());
}

void graphicsScene::menuSelectionMade(QAction* action) {
//   qDebug() << "creating module: " << action->text() << " at pos: "
//       << screenPos.x() << "x" << screenPos.y();;
  moduleFactory->createModule(action->text(), screenPos);
}
