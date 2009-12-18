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
/*    QVector<QString> s = model->LoadableModuleNames();
    for (int i=0; i < s.size(); i++) {
        menu.addAction(s[i]);
    }
    menu.exec(contextMenuEvent->screenPos());*/
}

void GraphicsScene::menuSelectionMade(QAction* action) {
//   qDebug() << "creating module: " << action->text() << " at pos: "
//       << screenPos.x() << "x" << screenPos.y();;
//     model->createModule(action->text(), screenPos);

}
