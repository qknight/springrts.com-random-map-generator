#ifndef MYQGRAPHICSSCENE__HH__
#define MYQGRAPHICSSCENE__HH__

#include <QDialog>
#include <QMainWindow>
#include <QPointF>
#include <QMessageBox>
#include <QDebug>

#include "ui_GraphicsView.h"
#include "GraphicsScene.h"
#include "ModuleWidget.h"

#include "Document.h"

class MainWidget : public QMainWindow, private Ui::GraphicsViewWidget {
    Q_OBJECT
public:
    MainWidget(QMainWindow *parent=0);
    ~MainWidget();

private:
    GraphicsScene* scene;
    ModuleWidget moduleWidget;
    void setupMenus();
    Document doc;

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
