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

#include <QGraphicsView>
#include "GraphicsScene.h"

GraphicsScene::GraphicsScene( Model *model, QWidget * parent ) : QGraphicsScene() {
  this->model = model;
    connect(&menu,SIGNAL(triggered(QAction*)),
            this, SLOT(menuSelectionMade(QAction*)));
}

GraphicsScene::~GraphicsScene() {}

void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    // FIXME: add icons for each module
    screenPos = contextMenuEvent->screenPos();
    // create menu
    menu.clear();
    for (int i=0; i < loadableModuleNames.size(); i++) {
        menu.addAction(loadableModuleNames[i]);
    }
    menu.exec(contextMenuEvent->screenPos());
}

void GraphicsScene::menuSelectionMade(QAction* action) {
//   qDebug() << "creating module: " << action->text() << " at pos: " << screenPos.x() << "x" << screenPos.y();;
  if (!(views().size())) {
    qDebug() << "Error: no view is attached to this scene, this should not happen!, exiting";
    exit(1);
  }
  QGraphicsView* view = views().first(); 
//   QMenu* menu = action->menu()->pos();
//   if (menu == NULL)
//     return;
//   QPoint menupos = menu->pos();
  QPoint pos = view->mapToScene ( view->mapFromGlobal ( QCursor::pos() ) ).toPoint();
  emit CreateModuleSignal(action->text(), pos);
}

void GraphicsScene::setLoadableModuleNames(QVector<QString> loadableModuleNames) {
  this->loadableModuleNames=loadableModuleNames;
}

QGraphicsItem* GraphicsScene::moduleInserted( QPersistentModelIndex item ) {
//   qDebug() << __PRETTY_FUNCTION__;
  Module* module = new Module( item );
  // FIXME if an item is added to a scene() maybe the item can use that event to do updateModule ( module)
  //       instead of calling it here again
  addItem( module );
  module->setPos( model->data(item, customRole::PosRole).toPoint() );
//   updateModule( module );
  return module;
}

bool GraphicsScene::moduleRemoved( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__;
  QGraphicsItem* nItem = modelToSceenIndex( item );
  if ( nItem == NULL ) {
    qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
    // FIXME after testing this can be changed to return instaead of exit
    exit( 0 );
//     return false;
  }
//   qDebug() << "nItem is: " << QString("%1").arg((unsigned int) nItem,0,16);
  delete nItem;
  return true;
}

QGraphicsItem* GraphicsScene::modelToSceenIndex( QPersistentModelIndex index ) {
/*  QList<QGraphicsItem *> m_list = items();
//   qDebug() << "=== searching in: " << m_list.size() << " items ====";
//   qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";
  for ( int i = 0; i < m_list.size(); ++i ) {
    if ( m_list[i]->type() == SceneItem_NodeType ) {
      if ( compareIndexes((( Module * )m_list[i] )->index, index ) ) {
//         qDebug() << "node found";
        return m_list[i];
      }
    }
    if ( m_list[i]->type() == SceneItem_ConnectionType ) {
//       qDebug() << "  -->> trying:  " << (( SceneItem_Connection * )m_list[i] )->index.row() <<  " " <<
      (( Connection * )m_list[i] )->index.column();
      if ( compareIndexes((( Connection * )m_list[i] )->index, index ) ) {
//         qDebug() << "connection found";
        return m_list[i];
      }
    }
  }
  qDebug() << "FATAL: failed to modify the item, since the QGraphicsScene equivalent to the given QPersistentModelIndex wasn't found, exiting";
  exit(1);*/
  return NULL;
}

bool GraphicsScene::compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
  if ( a.row() != b.row() )
    return false;
  if ( a.internalPointer() != b.internalPointer() )
    return false;
  return true;
}

void GraphicsScene::clearScene() {}