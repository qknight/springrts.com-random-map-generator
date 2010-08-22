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
              
    // as this GraphicsScene is now somehow a QAbstractItemView, we need to connect the functionality
    connect( model, SIGNAL(modelReset ()),
             this, SLOT(reset()));
    connect( model, SIGNAL(rowsInserted ( const QModelIndex & , int , int  )),
             this, SLOT(rowsInserted ( const QModelIndex & , int , int  )));
    connect( model, SIGNAL(rowsAboutToBeRemoved ( const QModelIndex & , int , int  )),
             this, SLOT(rowsAboutToBeRemoved ( const QModelIndex & , int , int  )));
    connect( model, SIGNAL(dataChanged ( const QModelIndex & , const QModelIndex &  )),
             this, SLOT(dataChanged ( const QModelIndex & , const QModelIndex &  )));             
              
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
            // this is the position where the QMenu was created and where we phut the module
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











void GraphicsScene::reset() {
    qDebug() << __PRETTY_FUNCTION__;
}

void GraphicsScene::rowsInserted( const QModelIndex & parent, int start, int end ) {
//     qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        switch (model->data( item, customRole::TypeRole ).toInt()) {
        case DataItemType::MODULE:
//             qDebug() << __FUNCTION__ << " DataItemType::MODULE " << model->data( item, customRole::TypeRole ).toInt();
            moduleInserted( QPersistentModelIndex( item ) );
            break;
        case DataItemType::CONNECTION:
//             qDebug() << __FUNCTION__ << " DataItemType::CONNECTION " << model->data( item, customRole::TypeRole ).toInt();
            connectionInserted( QPersistentModelIndex( item ));
            break;
        case DataItemType::PROPERTY:
            qDebug() << __PRETTY_FUNCTION__ << " DataProperty inserted: we ignore this currently!";
            break;
        default:
            //FIXME why does that happen?!
            qDebug() << __PRETTY_FUNCTION__ << " UNKNOWN?! " << model->data( item, customRole::TypeRole ).toInt();
        }
    }
}

/*! this view only visualizes modules, ports and connections (properties only indirectional) 
**  ports are directly created when a module is inserted (not otherwise) */
void GraphicsScene::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
//   qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        if ( model->data( item, customRole::TypeRole ).toInt() == DataItemType::MODULE )
            moduleRemoved( QPersistentModelIndex( item ) );
        else if ( model->data( item, customRole::TypeRole ).toInt() == DataItemType::CONNECTION )
            connectionRemoved( QPersistentModelIndex( item ) );
    }
}

void GraphicsScene::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
//   qDebug() << __FUNCTION__;
    QModelIndex tmpIndex = topLeft;
    do {
//     qDebug() << "dataChanged is now called()";
        switch (model->data( tmpIndex, customRole::TypeRole ).toInt()) {
        case DataItemType::MODULE:
            moduleUpdated( QPersistentModelIndex( tmpIndex ) );
            break;
        case DataItemType::CONNECTION:
            //not implemented, but we probably don't need that
            break;
        case DataItemType::PROPERTY:
            qDebug() << __PRETTY_FUNCTION__ << " FIXME: not implemented yet for PROPERTY";
            break;
        default:
            qDebug() << __PRETTY_FUNCTION__ << " didn't understand what i should be doing";
            exit(0);
        }
        if (tmpIndex == bottomRight)
            break;
        tmpIndex = traverseTroughIndexes( tmpIndex );
    } while ( tmpIndex.isValid() );
}

/*!
** This algorithm traverses trough the QModelIndex hierarchy
**  topleft -- itemA -- connection1
**             \---- -- connection2       given the topLeft item it returns itemA
**          -- itemB                      given itemA it returns connection1
**             \---- -- connection1       given connection1 it returns itemB
**          -- itemC                      ...
**          -- itemD (bottomRight)        and so on
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex GraphicsScene::traverseTroughIndexes( QModelIndex index ) {
//   qDebug() << "  " << index.row() << " ";
    // 1. dive deep into the structure until we found the bottom (not bottomRight)
    QModelIndex childIndex = model->index(0,0,index);
//   qDebug() << "step a";
    if (childIndex.isValid())
        return childIndex;

    // 2. now traverse all elements in the lowest hierarchy
    QModelIndex tmpIndex = model->index(index.row()+1,0,model->parent(index));//index.sibling(index.row()+1,0);
//   qDebug() << "step b";
    if (tmpIndex.isValid())
        return tmpIndex;

    // 3. if no more childs are found, return QModelIndex()
//   qDebug() << "step c";
    return QModelIndex();
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

        if (graphicsItem == NULL) {
            qDebug() << __PRETTY_FUNCTION__ << "CRITICAL ERROR: item not found!? wth?!";
            continue;
        }

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
    mod->dataChanged();
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
    QList<QGraphicsItem *> m_list = items();
//     qDebug() << __PRETTY_FUNCTION__ << "=== searching in: " << m_list.size() << " items ====";
//     qDebug() << " searching for: " << index.row() <<  " " << index.column() << " row/column";
    for ( int i = 0; i < m_list.size(); ++i ) {
//         qDebug() << m_list[i]->type()/* << " " << DataItemType::EXTENDEDGRAPHICSITEM*/;
        if ( m_list[i]->type() == DataItemType::EXTENDEDGRAPHICSITEM) {
//             qDebug() << __PRETTY_FUNCTION__ << "found a DataItemType::EXTENDEDGRAPHICSITEM";
            GraphicsItemModelExtension* item = dynamic_cast<GraphicsItemModelExtension *> (m_list[i]);
            if ( compareIndexes ( item->index(), index ) ) {
//                 qDebug() << __PRETTY_FUNCTION__ << "item found";
                return m_list[i];
            }
        }
    }
//     qDebug() << __PRETTY_FUNCTION__ << "item NOT found";
    return NULL;
}

/*! TODO */
QPersistentModelIndex GraphicsScene::graphicsItem2Model ( QGraphicsItem* graphicsItem ) {
    if ( graphicsItem->type() == DataItemType::EXTENDEDGRAPHICSITEM ) {
        GraphicsItemModelExtension* item = dynamic_cast<GraphicsItemModelExtension*>(graphicsItem);
        QPersistentModelIndex i = item->index();
//         qDebug() << __PRETTY_FUNCTION__ << "module found";
        return i;
    }
    return QPersistentModelIndex();
}

/*! this implementation ignores column positions */
bool GraphicsScene::compareIndexes ( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
    if ( a.row() != b.row() )
        return false;
    if ( a.internalPointer() != b.internalPointer() )
        return false;
    return true;
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
        if ( ( items ( mouseEvent->scenePos() ) ).count() ) {
            // picks the first item in the clicked area
            QGraphicsItem* item = items ( mouseEvent->scenePos() ).first();
            if ( item->type() == DataItemType::EXTENDEDGRAPHICSITEM ) {
                GraphicsItemModelExtension* mitem = dynamic_cast<GraphicsItemModelExtension*>(item);
                // check if it is a PORT
                if (mitem->customType() == DataItemType::PORT) {
//                     qDebug() << __PRETTY_FUNCTION__ << "CLICK";
                    QGraphicsScene::mousePressEvent ( mouseEvent );
                    line = new QGraphicsLineItem ( QLineF ( mouseEvent->scenePos(),
                                                            mouseEvent->scenePos() ) );
                    line->setPen ( QPen ( QColor ( "RED" ), 2 ) );
                    line->setZValue ( 2000 );
                    addItem ( line );
                }
                return;
            }
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
        QGraphicsItem* sItem = startItems.first();
        QGraphicsItem* eItem = endItems.first();
        if ( startItems.count() && endItems.count() &&
                sItem->type() == DataItemType::EXTENDEDGRAPHICSITEM &&
                eItem->type() == DataItemType::EXTENDEDGRAPHICSITEM ) {
            GraphicsItemModelExtension* esItem = dynamic_cast<GraphicsItemModelExtension*>(sItem);
            GraphicsItemModelExtension* eeItem = dynamic_cast<GraphicsItemModelExtension*>(eItem);
            if (esItem->customType() == DataItemType::PORT && eeItem->customType() == DataItemType::PORT) {
                Port *startItem = qgraphicsitem_cast<Port *> ( sItem );
                Port *endItem   = qgraphicsitem_cast<Port *> ( eItem );
                model->insertConnection ( startItem->index(), endItem->index() );
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent ( mouseEvent );
}


