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
#include "Model.h"

/**
  @author Joachim Schiele <js@lastlog.de>
*/

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphicsScene();
//     ~graphicsScene();
private:
    //FIXME this should be done using the model
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QMenu menu;
    QPoint screenPos;
public slots:
    void menuSelectionMade(QAction* action);
};

#endif
