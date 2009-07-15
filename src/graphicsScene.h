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

/**
  @author Joachim Schiele <js@lastlog.de>
*/
class ModuleFactory;

class graphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    graphicsScene();
    ~graphicsScene();
private:
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QMenu menu;
    QPoint screenPos;
public slots:
    void appendToQMenuBox(QString ModuleID);
    void menuSelectionMade(QAction* action);
signals:
    void createModule(QString ModuleID, QPoint pos);
};

#endif
