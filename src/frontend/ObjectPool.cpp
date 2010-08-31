
#include <QPersistentModelIndex>
#include <QGraphicsItem>
#include "GraphicsItemModelExtension.h"
#include "ObjectPool.h"
#include "GraphicsScene.h"

/*! helper class for the GraphicsScene to translate QGraphicsItems into QPersistentModelIndex(es) and vice versa 
**  this code might be profiled to increase lookup times but as i:
**   - don't use it that often (and)
**   - don't have too many items (20-40 at best)
**  i stay with this implementation */
ObjectPool::ObjectPool(GraphicsScene* scene) {
    m_scene = scene;
}

ObjectPool::~ObjectPool() {
    qDebug() << __PRETTY_FUNCTION__;
}

/*! * searches all items() in the QGraphicsScene for the _one_ with the matching index */
QGraphicsItem* ObjectPool::model2GraphicsItem ( QPersistentModelIndex index ) {
    QList<QGraphicsItem *> m_list = m_scene->items();
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

/*! some QGraphicsItems represent an item of a QAbstractItemModel, this function extracts that information */
QPersistentModelIndex ObjectPool::graphicsItem2Model ( QGraphicsItem* graphicsItem ) {
    if ( graphicsItem->type() == DataItemType::EXTENDEDGRAPHICSITEM ) {
        GraphicsItemModelExtension* item = dynamic_cast<GraphicsItemModelExtension*>(graphicsItem);
        QPersistentModelIndex i = item->index();
//         qDebug() << __PRETTY_FUNCTION__ << "module found";
        return i;
    }
    // returns a invalid index if no such item is found
    return QPersistentModelIndex();
}

/*! this implementation ignores column positions (sometimes used in QTreeViews but not in our QGraphicsScene frontend) */
bool ObjectPool::compareIndexes ( const QPersistentModelIndex & a, const QPersistentModelIndex & b ) {
    if ( a.row() != b.row() )
        return false;
    if ( a.internalPointer() != b.internalPointer() )
        return false;
    return true;
}
