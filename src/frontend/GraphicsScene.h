
/**
  @author Joachim Schiele <js@lastlog.de>
*/

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPersistentModelIndex>
#include <QGraphicsTextItem>
#include <QVariant>
#include <QDebug>
#include <QKeyEvent>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "Model.h"
#include "Module.h"
#include "Connection.h"
#include "PortTypes.h"

/**
 @author Joachim Schiele <js@lastlog.de>
*/
/*! */
class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
    friend class Document;
    friend class ItemView;

public:
    /*! constructor */
    GraphicsScene( Model *model, QWidget * parent = NULL );
    /*! destructor */
    ~GraphicsScene();

protected:
    QGraphicsItem* moduleInserted( QPersistentModelIndex item );
    QGraphicsItem* connectionInserted ( QPersistentModelIndex connectionIndex);
    void moduleUpdated( QPersistentModelIndex item );
    bool moduleRemoved( QPersistentModelIndex item );
    bool connectionRemoved( QPersistentModelIndex  item  );
    void setLoadableModuleNames(QVector<QString> loadableModuleNames);

private:
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QMenu menu;
    QPoint screenPos;
    QVector<QString> loadableModuleNames;
    QGraphicsItem* model2GraphicsItem( QPersistentModelIndex index );
    QPersistentModelIndex graphicsItem2Model ( QGraphicsItem* graphicsItem );
    /*! this (red) line is needed for adding connections with the MMB (mid-mouse-button) between nodes */
    QGraphicsLineItem *line;
    /*! the GraphicsScene visualizes the data of this model */
    Model *model;
    /*! we handle all keyboard events here, this is only interrupted when an item got focus */
    void keyPressEvent( QKeyEvent * keyEvent );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mousePressEvent ( QGraphicsSceneMouseEvent *mouseEvent );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mouseMoveEvent( QGraphicsSceneMouseEvent *mouseEvent  );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
    void mouseReleaseEvent( QGraphicsSceneMouseEvent *mouseEvent );
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );

protected Q_SLOTS:
    /*! helper function to implement a reset call for a custom view */
    void reset();
    /*! helper function to implement a layoutChanged call for a custom view */
    /*! callback which is called by the model on item insertion operations */
    void rowsInserted( const QModelIndex & parent, int start, int end );
    /*! callback which is called by the model on item removal operations */
    void rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end );
    /*! callback which is called by the model on item change operations */
    void dataChanged( const QModelIndex & , const QModelIndex & );
    /*! helper function to get all items between two items in a hierarchy
     ** we have to check all items between topLeft and bottomRight
     ** let's update all QModelIndex'es in between */
    QModelIndex traverseTroughIndexes( QModelIndex index );

private Q_SLOTS:
    /*! the current selection of items changes, for example when some nodes or
    connections vanished based on a model request since another view deleted them */
//     void selectionChanged();
public Q_SLOTS:
    void menuSelectionMade(QAction* action);
    void treeViewWantsItemFocus ( const QModelIndex & ) ;

Q_SIGNALS:
    /*! helper signal, see code */
//     void zoomOut();
    /*! helper signal, see code */
//     void zoomIn();
    /*! helper signal, see code */
//     void zoomFit();
    /*! when a new view pops up this reset() is called to query items from the model */
    void CreateModuleSignal(QString, QPoint);
};

#endif
