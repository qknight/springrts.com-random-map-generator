#include <QList>
#include <QRectF>

#include "MainWidget.h"
#include "GraphicsScene.h"

// http://doc.trolltech.com/qq/qq13-attributes.html
MainWidget::MainWidget ( QMainWindow *parent ) : QMainWindow ( parent ) {
    setupUi ( this );
    setupMenus();

    doc = new Document();
    graphicsView->setRenderHints ( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
    graphicsView->show();
    
    connect (treeView, SIGNAL(clicked ( const QModelIndex & ) ),
             this, SLOT(clickRelay(const QModelIndex &)));

    // the next line of code must be used if multi document support is required
    changeActiveDocument ( doc );
}

MainWidget::~MainWidget() {
    delete doc;
}

void MainWidget::changeActiveDocument ( Document* doc ) {
    // filter out port and connection elements
    treeView->setModel(doc->filter);
    //FIXME this should go into QSettings
    treeView->setColumnWidth(0, 230);
    
    graphicsView->setScene ( doc->scene );
    //FIXME this breaks multi document support since we must disconnect this signal on doc change
    connect (this, SIGNAL(clickRelaySig(const QModelIndex &)),
             doc->scene, SLOT(treeViewWantsItemFocus ( const QModelIndex & ) ));
    connect ( doc->scene, SIGNAL ( selectionChanged() ),
              this, SLOT ( selectionChanged() ) );
    connect (doc->filter, SIGNAL(rowsInserted ( const QModelIndex & , int , int  )),
             this, SLOT(rowsInsertedNotification ( const QModelIndex & , int , int )));
             
    // for new modules we can use the rowsInserted signal but if the view is populated
    // using either Document.cpp or save/load then we need to call this 
    treeView->expandAll();
}

/*! when new items are inserted to the treeView, we expand all items */
void MainWidget::rowsInsertedNotification ( const QModelIndex & parent, int start, int end ) {
  treeView->expandAll();
}

/*! this relay translates the filter's QModelIndex(es) into the model's ones */
void MainWidget::clickRelay ( const QModelIndex & index ) {
    QModelIndex translatedIndex = doc->filter->mapToSource(index);
    emit clickRelaySig (translatedIndex);
}

void MainWidget::save() {
    QMessageBox::information ( this,"information","call to save()" );
}
void MainWidget::load() {
    QMessageBox::information ( this,"information","call to load()" );
}
void MainWidget::documentation() {
    QMessageBox::information ( this,"information","build the doxygen documentation coming with this source, also see github.com/qknight/ " );
}
void MainWidget::about() {
    QMessageBox::information ( this,"information","spring random map generator by\n Joachim Schiele <js adt lastlog dodt de>\n see github.com/qknight/" );
}

void MainWidget::setupMenus() {
    menubar->clear();
    QMenu* file = menubar->addMenu ( "&File" );
//   file->addAction("&Load", this, SLOT(load()));
//   file->addAction("&Save", this, SLOT(save()));
    file->addSeparator();
    file->addAction ( "&Quit", this, SLOT ( close() ) );

    QMenu* view = menubar->addMenu ( "&View" );
    view->addAction ( "h&ide Property dialog", this, SLOT ( hidePropertyDialog() ) );
    view->addAction ( "&unhide Property dialog", this, SLOT ( unhidePropertyDialog() ) );

    QMenu* help = menubar->addMenu ( "&Help" );
    help->addAction ( "&About", this, SLOT ( about() ) );
    help->addAction ( "&Documentation", this, SLOT ( documentation() ) );
}

void MainWidget::hidePropertyDialog() {
    dockWidget->setVisible ( false );
}

void MainWidget::unhidePropertyDialog() {
    dockWidget->setVisible ( true );
}

void MainWidget::selectionChanged() {
//     QList<QGraphicsItem *> sitems = scene->selectedItems();
//     if (sitems.size() == 1) {
//         QGraphicsItem* item = sitems[0];
//         QString s = QString("module selected:\n %1").arg(item->data(0).toString());
// //     ModuleWidget* item_moduleWidget = item->data(1).value<ModuleWidget* > ();
// //     dockWidget->setWidget(item_moduleWidget);
//         statusbar->showMessage(s,2000);
//     } else {
//         statusbar->showMessage("nothing selected",2000);
//         dockWidget->setWidget(&moduleWidget);
//     }
}
