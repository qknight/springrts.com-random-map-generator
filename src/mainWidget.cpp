#include "mainWidget.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

#include <QList>
#include <QRectF>
// http://doc.trolltech.com/qq/qq13-attributes.html

mainWidget::mainWidget(QMainWindow *parent) : QMainWindow(parent) {
  setupUi(this);
  setupMenus();

  scene = new graphicsScene();
  // this is the initial initalisation which must contain a scene, later no
  // scene argument is needed anymore
  moduleFactory = ModuleFactory::Instance(scene);

  graphicsView->setScene(scene);
  graphicsView->show();
  graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

  connect(scene,SIGNAL(selectionChanged()),
          this,SLOT(selectionChanged()));
  connect(moduleFactory,SIGNAL(appendToQMenuBox(QString)),
          scene,SLOT(appendToQMenuBox(QString)));
  connect(scene, SIGNAL(createModule(QString, QPoint)),
          moduleFactory,SLOT(createModule(QString, QPoint)));

  dockWidget->setWidget(&moduleWidget);
}

mainWidget::~mainWidget() {
  //BUG, handle unload of modules on exit
  delete scene;
}

// void mainWidget::load_modules(){
//   // all modules listed here will be added to the moduleFactory automatically on init
//   NoiseGenPerlinInterface* ngpi = new NoiseGenPerlinInterface();
// }

void mainWidget::save(){
  QMessageBox::information(this,"information","call to save()");
}
void mainWidget::load(){
  QMessageBox::information(this,"information","call to load()");
}
void mainWidget::documentation(){
  QMessageBox::information(this,"information","call to help()");
}
void mainWidget::about(){
  QMessageBox::information(this,"information","call to about()");
}

void mainWidget::setupMenus() {
  menubar->clear();
  QMenu* file = menubar->addMenu("&File");
  file->addAction("&Load", this, SLOT(load()));
  file->addAction("&Save", this, SLOT(save()));
  file->addSeparator();
  file->addAction("&Quit", this, SLOT(close()));

  QMenu* view = menubar->addMenu("&View");
  view->addAction("h&ide Property dialog", this, SLOT(hidePropertyDialog()));
  view->addAction("&unhide Property dialog", this, SLOT(unhidePropertyDialog()));

  QMenu* help = menubar->addMenu("&Help");
  help->addAction("&About", this, SLOT(about()));
  help->addAction("&Documentation", this, SLOT(documentation()));
}

void mainWidget::hidePropertyDialog() {
  dockWidget->setVisible(false);
}

void mainWidget::unhidePropertyDialog() {
  dockWidget->setVisible(true);
}

void mainWidget::selectionChanged() {
  QList<QGraphicsItem *> sitems = scene->selectedItems();
  if (sitems.size() == 1) {
    QGraphicsItem* item = sitems[0];
    QString s = QString("module selected:\n %1").arg(item->data(0).toString());
//     ModuleWidget* item_moduleWidget = item->data(1).value<ModuleWidget* > ();
//     dockWidget->setWidget(item_moduleWidget);
    statusbar->showMessage(s,2000);
  } else {
    statusbar->showMessage("nothing selected",2000);
    dockWidget->setWidget(&moduleWidget);
  }
}
