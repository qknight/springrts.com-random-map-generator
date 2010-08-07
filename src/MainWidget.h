#ifndef MYQGRAPHICSSCENE__HH__
#define MYQGRAPHICSSCENE__HH__

#include <QDialog>
#include <QMainWindow>
#include <QPointF>
#include <QMessageBox>
#include <QDebug>

#include "ui_GraphicsView.h"
#include "Document.h"
#include "FilterProxyModel.h"

class MainWidget : public QMainWindow, private Ui::GraphicsViewWidget {
    Q_OBJECT
public:
    MainWidget(QMainWindow* parent=0);
    ~MainWidget();

private:
    void setupMenus();
    Document* doc;
    /*! this project has multi document support and this function call will change the document in use*/
    void changeActiveDocument(Document* doc);

private Q_SLOTS:
    void save();
    void load();
    void documentation();
    void about();
    void hidePropertyDialog();
    void unhidePropertyDialog();
    void clickRelay ( const QModelIndex & );

public Q_SLOTS:
    void selectionChanged();
  Q_SIGNALS:
    void clickRelaySig ( const QModelIndex & );
};

#endif
