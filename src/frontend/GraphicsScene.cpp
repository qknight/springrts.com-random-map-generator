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
#include <QMultiMap>
#include "GraphicsScene.h"
#include "Model.h"
#include "DataItemType.h"

GraphicsScene::GraphicsScene ( Model *model, QWidget * parent ) : QGraphicsScene() {
    this->model = model;
    connect ( &menu,SIGNAL ( triggered ( QAction* ) ),
              this, SLOT ( menuSelectionMade ( QAction* ) ) );
    line=NULL;
}

GraphicsScene::~GraphicsScene() {
}

/*! a rightclick on the QGraphicsView will pop up this QMenu */
void GraphicsScene::contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    QMultiMap<QString,QString> m;
    screenPos = contextMenuEvent->screenPos();
    // create menu
    menu.clear();
    for ( int i=0; i < loadableModuleNames.size(); i++ ) {
        QString moduleIdentifier =  loadableModuleNames[i];
        // 1. see the category c of the module. if a submenu for c already exists
        //    insert the menu entry there, if not create it first
        QString moduleCategory = moduleIdentifier.section("::",0,0);
        QString moduleName = moduleIdentifier.section("::",1,1);
        m.insert(moduleCategory, moduleName);
    }
    // we create a collection of categories and their modules to convert them into a qmenu structure
    foreach(QString category, m.uniqueKeys()) {
        QList<QString> modules = m.values(category);
        QMenu* categoryMenu = menu.addMenu ( category );
        for (int i = 0; i < modules.size(); ++i) {
            QString moduleName = modules.at(i);
            QAction* action = categoryMenu->addAction(moduleName);

            // we need to store two values in a QAction, so we have to use a QList
            QList<QVariant> d;
            // this is the unique identifier used to create the module
            QString identifier = QString("%1::%2").arg(category).arg(moduleName);
            d << identifier;
            // this is the position where the QMenu was created and where we put the module
            d << contextMenuEvent->screenPos();
            action->setData(d);
        }
    }
    menu.exec ( contextMenuEvent->screenPos() );
}

/*! after a selection in the QMenu on the QGraphicsView has been made */
void GraphicsScene::menuSelectionMade ( QAction* action ) {
    // we need the active view to map the coordinates of the click to the QGraphicsScene
    if ( !( views().size() ) ) {
        qDebug() << "Error: no view is attached to this scene, this should not happen!, exiting";
        exit ( 1 );
    }

    QGraphicsView* view = views().first();
    // parse the position and the string created in contextMenuEvent(..)
    QList<QVariant> l = action->data().toList();
    if (l.size() != 2) {
        qDebug() << __PRETTY_FUNCTION__ << " problem with parsing the arguments given by QAction->data()";
        return;
    }
    QString s =  l[0].toString();
    QPoint pos = view->mapToScene ( view->mapFromGlobal ( l[1].toPoint() ) ).toPoint();

    // this will finally create the module using the Model
    emit CreateModuleSignal ( s, pos );
}

void GraphicsScene::setLoadableModuleNames ( QVector<QString> loadableModuleNames ) {
    this->loadableModuleNames=loadableModuleNames;
}








/*!
 * adds a graphical representation (see Connection.cpp/.h) spanning from
 * Port a to Port b (see Port.cpp/.h)
 * this function is called by the QAbstractItemModel after a connection has been inserted
 */
QGraphicsItem* GraphicsScene::connectionInserted ( QPersistentModelIndex connectionIndex ) {
    // 0. dst QPersistentModelIndex (that is to be queried via the model)
    QPersistentModelIndex sPortIndex = connectionIndex.parent();
    QPersistentModelIndex dPortIndex = QPersistentModelIndex(model->dst(connectionIndex));

    Port* srcPort = dynamic_cast<Port*> ( model2GraphicsItem ( sPortIndex ) );
    Port* dstPort = dynamic_cast<Port*> ( model2GraphicsItem ( dPortIndex ) );

    if (srcPort == NULL || dstPort == NULL || srcPort == dstPort) {
        if (srcPort == NULL)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == NULL";
        if (dstPort == NULL)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "dstModule == NULL";
        if (srcPort == dstPort)
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "srcModule == dstModule";
        exit(1);
    }

    Connection* connection = new Connection ( model, connectionIndex, srcPort, dstPort);
    addItem ( connection );
//     qDebug() << __PRETTY_FUNCTION__ << "added a connection sucessfully";
    return connection;
}

QGraphicsItem* GraphicsScene::moduleInserted ( QPersistentModelIndex item ) {
//   qDebug() << __PRETTY_FUNCTION__;
    Module* module = new Module ( model, item );
    addItem ( module );

    // FIXME: can this code be placed into Module.cpp::Module()?
    //        -> probably NO since it uses GraphicsScene::model2GraphicsItem(..)
    int child_count = model->rowCount(item);
    int in=0, mod=0, out=0;
    for (int i = 0; i < child_count; ++i) {
        QPersistentModelIndex child = model->index(i, 0, item);

        // 0. is it a property? if so we skip right here!
        if (model->data(child, customRole::TypeRole) == DataItemType::PROPERTY)
            continue;

        // 1. find the QGraphicsItem refered to by item
        QGraphicsItem* graphicsItem = model2GraphicsItem(item);

        // 2. create a new Port class object and assign it as child to the parent P
        unsigned int portDirection = model->data(child, customRole::PortDirection).toInt();
        unsigned int portType = model->data(child, customRole::PortType).toInt();
//         unsigned int portNumber = model->data(child, customRole::PortNumber).toInt();
        Port* port = new Port(model, child, portDirection, portType, i, graphicsItem);
        port->setParentItem ( graphicsItem );

        // now we do the layout of the items
        // FIXME 'this' is probably not the best case to do it (it would be better to do it in the Module context)
        //       since it makes absolute sense to make the graphical Module the layout master
        // FIXME we ignore portType currently
        // FIXME this implementation expects the ports to be ordered by portNumber

        switch (portDirection) {
        case PortDirection::IN:
            port->moveBy(-10,20+(in++)*40);
            break;
        case PortDirection::MOD:
            port->moveBy(50+20*(mod++),130);
            break;
        case PortDirection::OUT:
            port->moveBy(130,20+(out++)*40);
            break;
        default:
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << "no case matched";
            break;
        }
    }
    return NULL;
}

bool GraphicsScene::connectionRemoved( QPersistentModelIndex  item  ) {
//     qDebug() << __PRETTY_FUNCTION__;
    QGraphicsItem* cItem = model2GraphicsItem ( item );
    if ( cItem == NULL ) {
        qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
        // FIXME after testing this can be changed to return instaead of exit
        exit ( 1 );
    }
    delete cItem;
    return true;
}

bool GraphicsScene::moduleRemoved ( QPersistentModelIndex item ) {
//     qDebug() << __PRETTY_FUNCTION__;
    QGraphicsItem* nItem = model2GraphicsItem ( item );
    if ( nItem == NULL ) {
        qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
        // FIXME after testing this can be changed to return instaead of exit
        exit ( 1 );
    }
    delete nItem;
    return true;
}

void GraphicsScene::moduleUpdated(QPersistentModelIndex item) {
    QGraphicsItem* mItem = model2GraphicsItem ( item );
    if ( mItem == NULL ) {
        qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
        // FIXME after testing this can be changed to return instaead of exit
        exit ( 1 );
    }
    Module* mod = qgraphicsitem_cast<Module *> ( mItem );
    mod->updateData();
}













/*!
 * look at all items in the GraphicsScene and try to find the _one_ with the index in it
 * WARNING: be careful with using the constructor of an QGraphicsItem to allocate child items
 *          as ports (when using a module), since the required item might not have been inserted
 *          into the scene() yet.
 *          -> just commit complex new items (containing also childs) in one go, using
 *             the Model code, see Model.cpp:insertModule(..) where this is done
 */
QGraphicsItem* GraphicsScene::model2GraphicsItem ( QPersistentModelIndex index ) {
//   qDebug() << "Searching for: " << index;
    //FIXME use GraphcsItemModelExtension cast if possible not 3 times the same code! (adding this case will crash the program?!)
    QList<QGraphicsItem *> m_list = items();
//   qDebug() << "=== searching in: " << m_list.size() << " items ====";
//   qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";
    for ( int i = 0; i < m_list.size(); ++i ) {
        if ( m_list[i]->type() == DataItemType::MODULE ) {
            if ( compareIndexes ( ( ( Module * ) m_list[i] )->index(), index ) ) {
//                 qDebug() << __PRETTY_FUNCTION__ << "module found";
                return m_list[i];
            }
        }
        if ( m_list[i]->type() == DataItemType::CONNECTION ) {
            if ( compareIndexes ( ( ( Connection * ) m_list[i] )->index(), index ) ) {
//                 qDebug() << __PRETTY_FUNCTION__ << "connection found";
                return m_list[i];
            }
        }
        if ( m_list[i]->type() == DataItemType::PORT ) {
            if ( compareIndexes ( ( ( Port* ) m_list[i] )->index(), index ) ) {
//                 qDebug() << __PRETTY_FUNCTION__ << "port found";
                return m_list[i];
            }
        }
    }
    return NULL;
}

/*! */
QPersistentModelIndex GraphicsScene::graphicsItem2Model ( QGraphicsItem* graphicsItem ) {
    if ( graphicsItem->type() == DataItemType::MODULE ) {
        QPersistentModelIndex i = ( ( Module * ) graphicsItem )->index();
//                 qDebug() << __PRETTY_FUNCTION__ << "module found";
        return i;
    }
    if ( graphicsItem->type() == DataItemType::CONNECTION ) {
        QPersistentModelIndex i = ( ( Connection * ) graphicsItem )->index();
//                 qDebug() << __PRETTY_FUNCTION__ << "connection found";
        return i;
    }
    if ( graphicsItem->type() == DataItemType::PORT ) {
        QPersistentModelIndex i = ( ( Port * ) graphicsItem )->index();
//                 qDebug() << __PRETTY_FUNCTION__ << "port found";
        return i;
    }
    return QPersistentModelIndex();
}









/*! collect all selected items, filter out items which have a QModelIndex associated
 ** with them, finaly remove these items using the model */
void GraphicsScene::keyPressEvent( QKeyEvent * keyEvent ) {
    if (keyEvent->key() == Qt::Key_Delete) {
//         qDebug() << __PRETTY_FUNCTION__ << " delete key pressed";
        QList<QGraphicsItem *> items = selectedItems ();
        QList<QPersistentModelIndex> selectedModelIndexes;
        for (int i = 0; i < items.size(); ++i) {
            QPersistentModelIndex persistentIndex = graphicsItem2Model(items[i]);
            if (persistentIndex.isValid())
                selectedModelIndexes.push_back(persistentIndex);
        }
        model->removeRows(selectedModelIndexes);
    }
}

bool GraphicsScene::compareIndexes ( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
    if ( a.row() != b.row() )
        return false;
    if ( a.internalPointer() != b.internalPointer() )
        return false;
    return true;
}

void GraphicsScene::clearScene() {}

void GraphicsScene::treeViewWantsItemFocus ( const QModelIndex & index ) {
    // we need to translate the index from the FilterProxyModel into the Model
    // because the QTreeView uses a FilterProxyModel on top of the Model to filter
    // port and connections
    QModelIndex srcIndex = index;
    QGraphicsItem* item = model2GraphicsItem ( QPersistentModelIndex ( srcIndex ) );
    if (item == NULL)
        return;
    // we do have only one view
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
            if ( ( items ( mouseEvent->scenePos() ) ).first()->type() == DataItemType::PORT ) {
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

void GraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent *mouseEvent ) {
//     qDebug() << __PRETTY_FUNCTION__;
    if ( line != 0 ) {
        QList<QGraphicsItem *> startItems = items ( line->line().p1() );
        if ( startItems.count() && startItems.first() == line )
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items ( line->line().p2() );
        if ( endItems.count() && endItems.first() == line )
            endItems.removeFirst();

        removeItem ( line );
        delete line;
        line = 0;

        if ( startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == DataItemType::PORT &&
                endItems.first()->type() == DataItemType::PORT ) {
            Port *startItem = qgraphicsitem_cast<Port *> ( startItems.first() );
            Port *endItem   = qgraphicsitem_cast<Port *> ( endItems.first() );

            model->insertConnection ( startItem->index(), endItem->index() );
        }
    }
    QGraphicsScene::mouseReleaseEvent ( mouseEvent );
}


