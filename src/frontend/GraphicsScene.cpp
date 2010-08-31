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
    pool = new ObjectPool(this);
    connect ( &menu,SIGNAL ( triggered ( QAction* ) ),
              this, SLOT ( menuSelectionMade ( QAction* ) ) );

    // as this GraphicsScene is now somehow a QAbstractItemView, we need to connect the functionality
    connect( model, SIGNAL(modelReset ()),
             this, SLOT(reset()));
    connect( model, SIGNAL(layoutChanged ()),
             this, SLOT(layoutChanged()));
    connect( model, SIGNAL(rowsInserted ( const QModelIndex & , int , int  )),
             this, SLOT(rowsInserted ( const QModelIndex & , int , int  )));
    connect( model, SIGNAL(rowsAboutToBeRemoved ( const QModelIndex & , int , int  )),
             this, SLOT(rowsAboutToBeRemoved ( const QModelIndex & , int , int  )));
    connect( model, SIGNAL(dataChanged ( const QModelIndex & , const QModelIndex &  )),
             this, SLOT(dataChanged ( const QModelIndex & , const QModelIndex &  )));
    line=NULL;
}

GraphicsScene::~GraphicsScene() {
    qDebug() << __PRETTY_FUNCTION__;
    delete pool;
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
    qDebug() << __PRETTY_FUNCTION__ << "FIXME: implement me";
    exit(1);
}

void GraphicsScene::layoutChanged() {
    qDebug() << __PRETTY_FUNCTION__ << "FIXME: implement me";
    exit(1);
}

void GraphicsScene::rowsInserted( const QModelIndex & parent, int start, int end ) {
//     qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        switch (model->data( item, customRole::TypeRole ).toInt()) {
        case DataItemType::MODULE:
//             qDebug() << __PRETTY_FUNCTION__ << " DataItemType::MODULE " << model->data( item, customRole::TypeRole ).toInt();
            addItem ( new Module ( model, item, pool ) );
            break;
        case DataItemType::CONNECTION:
//             qDebug() << __PRETTY_FUNCTION__ << " DataItemType::CONNECTION " << model->data( item, customRole::TypeRole ).toInt();
            //     Connection* connection = new Connection ( model, connectionIndex, srcPort, dstPort);
            addItem ( new Connection ( model, item, pool ) );
//     qDebug() << __PRETTY_FUNCTION__ << "added a connection sucessfully";
            break;
        case DataItemType::PROPERTY:
            qDebug() << __PRETTY_FUNCTION__ << " DataProperty inserted: we ignore this currently!";
            break;
        default:
            //FIXME why does that happen?!
            qDebug() << __PRETTY_FUNCTION__ << " UNKNOWN?! " << model->data( item, customRole::TypeRole ).toInt();
            exit(1);
        }
    }
}

/*! this view only visualizes modules, ports and connections (properties only indirectional)
**  ports are directly created when a module is inserted (not otherwise) */
void GraphicsScene::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
//     qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        switch (model->data( item, customRole::TypeRole ).toInt()) {
        case DataItemType::MODULE:
        case DataItemType::CONNECTION:
            QGraphicsItem* cItem = pool->model2GraphicsItem ( item );
            if ( cItem == NULL ) {
                qDebug() << "FATAL ERROR: nItem was NULL" << __FILE__ << ", " << __LINE__ << ", " << __FUNCTION__;
                // FIXME after testing this can be changed to return instaead of exit
                exit ( 1 );
            }
            delete cItem;
        }
    }
}

void GraphicsScene::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
//   qDebug() << __FUNCTION__;
    QModelIndex tmpIndex = topLeft;
    do {
        // a PROPERTY is a special case as it has no direct gui representation
        if (model->data( tmpIndex, customRole::TypeRole ).toInt() == DataItemType::PROPERTY) {
            //FIXME model->data(..) for customRole::propertyKey and customRole::propertyRole is needed
//             qDebug() << __PRETTY_FUNCTION__ << ;
            qDebug() << __PRETTY_FUNCTION__ << " FIXME: not implemented yet for PROPERTY";
        } else {
            QGraphicsItem* item = pool->model2GraphicsItem ( tmpIndex );
            if ( item == NULL ) {
                qDebug() << __PRETTY_FUNCTION__ << "FATAL ERROR: item was NULL";
                // FIXME after testing this can be changed to continue instaead of exit
                continue;
            }
            if (item->type() == DataItemType::EXTENDEDGRAPHICSITEM) {
                GraphicsItemModelExtension* i = dynamic_cast<GraphicsItemModelExtension *> ( item );
                i->dataChanged();
            }
        }
        if (tmpIndex == bottomRight)
            return;
        tmpIndex = traverseTroughIndexes( tmpIndex );
    } while ( tmpIndex.isValid() );
}

/*!
** This algorithm traverses trough the QModelIndex hierarchy
**  topleft -- itemA                      given the topLeft item it returns itemA
**             \---- -- connection1       given itemA it returns connection1
**          -- itemB                      given connection1 it returns itemB
**             \---- -- connection1       ...
**          -- itemC
**          -- itemD (bottomRight)
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex GraphicsScene::traverseTroughIndexes( QModelIndex index ) {
    qDebug() << "  " << index.row() << " ";
    // 1. dive deep into the structure until we found the bottom (not bottomRight)
    QModelIndex childIndex = model->index(0,0,index);
//     qDebug() << "step a";
    if (childIndex.isValid())
        return childIndex;

    // 2. now traverse all elements in the lowest hierarchy
    QModelIndex tmpIndex = model->index(index.row()+1,0,model->parent(index));//index.sibling(index.row()+1,0);
//     qDebug() << "step b";
    if (tmpIndex.isValid())
        return tmpIndex;

    // 3. if no more childs are found, return QModelIndex()
//     qDebug() << "step c";
    return QModelIndex();
}

/*! collect all selected items, filter out items which have a QModelIndex associated
 ** with them, finaly remove these items using the model */
void GraphicsScene::keyPressEvent( QKeyEvent * keyEvent ) {
    if (keyEvent->key() == Qt::Key_Delete) {
//         qDebug() << __PRETTY_FUNCTION__ << " delete key pressed";
        QList<QGraphicsItem *> items = selectedItems ();
        QList<QPersistentModelIndex> selectedModelIndexes;
        for (int i = 0; i < items.size(); ++i) {
            QPersistentModelIndex persistentIndex = pool->graphicsItem2Model(items[i]);
            if (persistentIndex.isValid())
                selectedModelIndexes.push_back(persistentIndex);
        }
        model->removeRows(selectedModelIndexes);
    }
    //FIXME zoom in
    //FIXME zoom out

    //select all selectable items on the scene using 'ctrl+a' modifiers
    if ((keyEvent->key() == Qt::Key_A) &&( keyEvent->modifiers() == Qt::ControlModifier )) {
//         qDebug() << "Selects all items in the scene";
        QPainterPath path;
        path.addRect ( sceneRect() );
        setSelectionArea ( path );
    }
}

void GraphicsScene::treeViewWantsItemFocus ( const QModelIndex & index ) {
    // we need to translate the index from the FilterProxyModel into the Model
    // because the QTreeView uses a FilterProxyModel on top of the Model to filter
    // port and connections
    QModelIndex srcIndex = index;
    QGraphicsItem* item = pool->model2GraphicsItem ( QPersistentModelIndex ( srcIndex ) );
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
        if ( endItems.count() && startItems.count()) {
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
    }
    QGraphicsScene::mouseReleaseEvent ( mouseEvent );
}


