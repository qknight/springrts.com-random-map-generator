#ifndef MYQGRAPHICSSCENE__HH__
#define MYQGRAPHICSSCENE__HH__

#include <QDialog>
#include <QMainWindow>
#include <QPointF>
#include <QMessageBox>

#include "ui_GraphicsView.h"
#include "modulePortConnection.h"
#include "graphicsScene.h"
#include "ModuleFactory.h"
#include "ModuleWidget.h"

#include "NoiseGenPerlinInterface.h"

// qRegisterMetaType(AbstractModule*);

class mainWidget : public QMainWindow, private Ui::GraphicsViewWidget {
  Q_OBJECT
  public:
    mainWidget(QMainWindow *parent=0);
    ~mainWidget();

  private:
    ModuleFactory* moduleFactory;
    graphicsScene* scene;
    ModuleWidget moduleWidget;
    void setupMenus();
    void load_modules();

  private slots:
    void save();
    void load();
    void documentation();
    void about();
    void hidePropertyDialog();
    void unhidePropertyDialog();

  public slots:
    void selectionChanged();
};

#endif
