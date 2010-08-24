
/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

class GraphicsScene;
class QGraphicsItem;
class QPersistentModelIndex;

/*! a helper class to organize view objects */
class ObjectPool {
  friend class GraphicsScene;
public:
    QGraphicsItem* model2GraphicsItem( QPersistentModelIndex index );
    QPersistentModelIndex graphicsItem2Model ( QGraphicsItem* graphicsItem );
protected:
    ObjectPool(GraphicsScene* scene);
    ~ObjectPool();
private:
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );
    GraphicsScene* m_scene;
};

#endif
