//
// C++ Implementation: GraphicsScene
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene() : QGraphicsScene() {
    //FIXME this should be done using the model
    connect(&menu,SIGNAL(triggered(QAction*)),
            this, SLOT(menuSelectionMade(QAction*)));
}

// GraphicsScene::~GraphicsScene() {}

void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    // FIXME: add icons for each module
    screenPos = contextMenuEvent->screenPos();
    // create menu
    menu.clear();
    //FIXME this should be done using the model
    for (int i=0; i < loadableModuleNames.size(); i++) {
        menu.addAction(loadableModuleNames[i]);
    }
    menu.exec(contextMenuEvent->screenPos());
}

void GraphicsScene::menuSelectionMade(QAction* action) {
//     qDebug() << "creating module: " << action->text() << " at pos: "
//     << screenPos.x() << "x" << screenPos.y();;
  emit CreateModuleSignal(action->text(), screenPos);
}
void GraphicsScene::setLoadableModuleNames(QVector<QString> loadableModuleNames) {
  this->loadableModuleNames=loadableModuleNames;
}
