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

GraphicsScene::GraphicsScene ( Model *model, QWidget * parent ) : QGraphicsScene() {
    this->model = model;
    connect ( &menu,SIGNAL ( triggered ( QAction* ) ),
              this, SLOT ( menuSelectionMade ( QAction* ) ) );
    line=NULL;
}

GraphicsScene::~GraphicsScene() {}

void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    // FIXME: add icons for each module
    screenPos = contextMenuEvent->screenPos();
    // create menu
    menu.clear();
    for ( int i=0; i < loadableModuleNames.size(); i++ ) {
        menu.addAction ( loadableModuleNames[i] );
    }
    menu.exec ( contextMenuEvent->screenPos() );
}

void GraphicsScene::menuSelectionMade ( QAction* action ) {
//   qDebug() << "creating module: " << action->text() << " at pos: " << screenPos.x() << "x" << screenPos.y();;
    if ( ! ( views().size() ) ) {
        qDebug() << "Error: no view is attached to this scene, this should not happen!, exiting";
        exit ( 1 );
    }
    QGraphicsView* view = views().first();
    //FIXME we need to use the QMenu::pos() instead of QCursor::pos();
//   QMenu* menu = action->menu()->pos();
//   if (menu == NULL)
//     return;
//   QPoint menupos = menu->pos();
    QPoint pos = view->mapToScene ( view->mapFromGlobal ( QCursor::pos() ) ).toPoint();
    emit CreateModuleSignal ( action->text(), pos );
}

void GraphicsScene::setLoadableModuleNames ( QVector<QString> loadableModuleNames ) {
    this->loadableModuleNames=loadableModuleNames;
}

/*!
 * inserts a Connection object which represents a QModelIndex of the Model
 * we know a lot about the connection but we must find out which ports are
 * used as parents for the connection (Module(s) are no parents) but are used to
 * find the Port(s)
 */
//FIXME this code has serious bugs and needs refactoring and testing
QGraphicsItem* GraphicsScene::connectionInserted ( QPersistentModelIndex cItem ) {/*
    // 0. dst QPersistentModelIndex (that is to be queried via the model)
    QPersistentModelIndex dItem = QPersistentModelIndex(model->dst(cItem));

    Module* srcModule = dynamic_cast<Module*> ( modelToSceenIndex ( cItem.parent() ) );
    Module* dstModule = dynamic_cast<Module*> ( modelToSceenIndex ( dItem ) );
    qDebug() << "src " << srcModule->m_label;
    qDebug() << "dst " << dstModule->m_label;
    if (srcModule == NULL) {
      qDebug() << "srcModule == NULL";
      exit(1);
    }
    if (dstModule == NULL) {
      qDebug() << "dstModule == NULL";
      exit(1);
    }
    if (srcModule == dstModule) {
      qDebug() << "srcModule == dstModule";
      exit(1);
    }
    
    // 1. type, number for both sides
    int srcPortType   = model->data(cItem, customRole::SrcPortTypeRole).toInt();
    int srcPortNumber = model->data(cItem, customRole::SrcPortNumberRole).toInt();;
    qDebug() << "src " << srcModule->m_label<< " porttype: " << srcPortType << " portnumber" << srcPortNumber;
    Port* srcPort = srcModule->resolvePort(srcPortType, srcPortNumber);
    
    // using sItem here is not wrong since dst/src query in DataConnection is context sensitive
    int dstPortType   = model->data(cItem, customRole::DstPortTypeRole).toInt();
    int dstPortNumber = model->data(cItem, customRole::DstPortNumberRole).toInt();
    qDebug() << "dst " << dstModule->m_label<< " porttype: " << dstPortType << " portnumber" << dstPortNumber;
    Port* dstPort = dstModule->resolvePort(dstPortType, dstPortNumber);

    Connection* connection = new Connection ( cItem, model, srcPort, dstPort );
    addItem ( connection );
    exit(1);
    qDebug() << __PRETTY_FUNCTION__ << "added a connection sucessfully";
    return connection;*/
}

QGraphicsItem* GraphicsScene::moduleInserted ( QPersistentModelIndex item ) {
//   qDebug() << __PRETTY_FUNCTION__;
    Module* module = new Module ( model, item );
    addItem ( module );
    return module;
}

bool GraphicsScene::moduleRemoved ( QPersistentModelIndex item ) {
//   qDebug() << __FUNCTION__;
    QGraphicsItem* nItem = modelToSceenIndex ( item );
    if ( nItem == NULL ) {
        qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
        // FIXME after testing this can be changed to return instaead of exit
        exit ( 1 );
    }
    delete nItem;
    return true;
}

/*!
 * look at all items in the GraphicsScene and try to find the _one_ with the index in it
 */
QGraphicsItem* GraphicsScene::modelToSceenIndex ( QPersistentModelIndex index ) {
    //FIXME use GraphcsItemModelExtension cast if possible not 3 times the same code!
    QList<QGraphicsItem *> m_list = items();
//   qDebug() << "=== searching in: " << m_list.size() << " items ====";
//   qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";
    for ( int i = 0; i < m_list.size(); ++i ) {
        if ( m_list[i]->type() == DataType::MODULE ) {
            if ( compareIndexes ( ( ( Module * ) m_list[i] )->index(), index ) ) {
                qDebug() << __PRETTY_FUNCTION__ << "module found";
                return m_list[i];
            }
        }
        if ( m_list[i]->type() == DataType::CONNECTION ) {
            ( ( Connection * ) m_list[i] )->index().column();
            if ( compareIndexes ( ( ( Connection * ) m_list[i] )->index(), index ) ) {
                qDebug() << __PRETTY_FUNCTION__ << "connection found";
                return m_list[i];
            }
        }
        if ( m_list[i]->type() == DataType::PORT ) {
            ( ( Port * ) m_list[i] )->index().column();
            if ( compareIndexes ( ( ( Port* ) m_list[i] )->index(), index ) ) {
                qDebug() << __PRETTY_FUNCTION__ << "port found";
                return m_list[i];
            }
        }
    }
    qDebug() << __PRETTY_FUNCTION__ << " FATAL: failed to find the item since the QGraphicsScene equivalent to the given QPersistentModelIndex wasn't found, exiting";
    exit ( 1 );
}

bool GraphicsScene::compareIndexes ( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
    if ( a.row() != b.row() )
        return false;
    if ( a.internalPointer() != b.internalPointer() )
        return false;
    return true;
}

void GraphicsScene::clearScene() {}

void GraphicsScene::listViewWantsItemFocus ( const QModelIndex & index ) {
    QGraphicsItem* item = modelToSceenIndex ( QPersistentModelIndex ( index ) );
    if ( views().size() ) {
        views().first()->centerOn ( item );
    }
}

/*!
** mousePressEvent,mouseReleaseEvent,mouseMoveEvent are used to graphically connect two nodes
** with each. even loops are possible just mouseRelease over the same node */
void GraphicsScene::mousePressEvent ( QGraphicsSceneMouseEvent *mouseEvent ) {
//     qDebug() << __PRETTY_FUNCTION__;
    if ( mouseEvent->button() == Qt::LeftButton )
        if ( ( items ( mouseEvent->scenePos() ) ).count() )
            if ( ( items ( mouseEvent->scenePos() ) ).first()->type() == DataType::PORT ) {
//                 qDebug() << __PRETTY_FUNCTION__ << "CLICK";
                QGraphicsScene::mousePressEvent ( mouseEvent );
                line = new QGraphicsLineItem ( QLineF ( mouseEvent->scenePos(),
                                                        mouseEvent->scenePos() ) );
                line->setPen ( QPen ( QColor ( "RED" ), 2 ) );
                line->setZValue ( 2000 );
                addItem ( line );
                return;
            }
    QGraphicsScene::mousePressEvent ( mouseEvent );
}

void GraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent *mouseEvent ) {
//     qDebug() << __PRETTY_FUNCTION__;
    if ( line != NULL ) {
        QLineF newLine ( line->line().p1(), mouseEvent->scenePos() );
        line->setLine ( newLine );
    } else {
        QGraphicsScene::mouseMoveEvent ( mouseEvent );
    }
}

//FIXME broken
void GraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent *mouseEvent ) {
//     qDebug() << __PRETTY_FUNCTION__;
//     if ( line != 0 ) {
//         QList<QGraphicsItem *> startItems = items ( line->line().p1() );
//         if ( startItems.count() && startItems.first() == line )
//             startItems.removeFirst();
//         QList<QGraphicsItem *> endItems = items ( line->line().p2() );
//         if ( endItems.count() && endItems.first() == line )
//             endItems.removeFirst();
// 
//         removeItem ( line );
//         delete line;
//         line = 0;
// 
//         if ( startItems.count() > 0 && endItems.count() > 0 &&
//              startItems.first()->type() == DataType::PORT &&
//              endItems.first()->type() == DataType::PORT ) {
//             Port *startItem = qgraphicsitem_cast<Port *> ( startItems.first() );
//             Port *endItem   = qgraphicsitem_cast<Port *> ( endItems.first() );
//             model->insertConnection ( startItem->index(), startItem->portnumber(), startItem->porttype(),
//                                       endItem->index(), endItem->portnumber(), endItem->porttype() );
//         }
//     }
    QGraphicsScene::mouseReleaseEvent ( mouseEvent );
}

