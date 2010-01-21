
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
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant data( const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
  protected:
    QGraphicsItem* moduleInserted( QPersistentModelIndex item );
//     void moduleUpdated( QPersistentModelIndex item );
    bool moduleRemoved( QPersistentModelIndex item );
  private:
    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * contextMenuEvent );
    QMenu menu;
    QPoint screenPos;
    QVector<QString> loadableModuleNames;
    QGraphicsItem* modelToSceenIndex( QPersistentModelIndex index );
    /*! this (red) line is needed for adding connections with the MMB (mid-mouse-button) between nodes */
    QGraphicsLineItem *line;
    /*! the GraphicsScene visualizes the data of this model */
    Model *model;
    /*! we handle all keyboard events here, this is only interrupted when an item got focus */
//     void keyPressEvent( QKeyEvent * keyEvent );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
//     void mousePressEvent( QGraphicsSceneMouseEvent * event );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
//     void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    /*! we handle all mouse events here, this is only interrupted when an item got focus */
//     void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
    bool compareIndexes( const QPersistentModelIndex & a, const QPersistentModelIndex & b );

//   public slots:
    /*! when a user want's to add a node we need to call this function which will request a node on the model side*/
//     void insertNode();
//     void insertNode(QPoint pos);
    
//   protected slots:
//     void clearScene();

  private Q_SLOTS:
    /*! the current selection of items changes, for example when some nodes or
    connections vanished based on a model request since another view deleted them */
//     void selectionChanged();

  Q_SIGNALS:
    /*! hides this view widget */
//     void hideView();
    /*! helper signal, see code */
//     void toggleRenderHints();
    /*! helper signal, see code */
//     void zoomOut();
    /*! helper signal, see code */
//     void zoomIn();
    /*! helper signal, see code */
//     void zoomFit();
    /*! when a new view pops up this reset() is called to query items from the model */
    void reset();
    void CreateModuleSignal(QString, QPoint);

  protected:
    void setLoadableModuleNames(QVector<QString> loadableModuleNames);
public Q_SLOTS:
    void menuSelectionMade(QAction* action);

};

#endif
