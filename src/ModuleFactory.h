//
// C++ Interface: ModuleFactory
//
// Description:
//   This class implements a object factory pattern. It's use is obvious: saving/loading states.
//   This class connects the modules with the QGraphicsScene to represent:
//     - the module itself
//     - in/out/mod connections to the module
//   Properties are exported to the QTreeView using delegates.
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MODULEFACTORY_H
#define MODULEFACTORY_H

/**
	@author Joachim Schiele <js@lastlog.de>
*/
#include <QMap>
#include <QMenu>
#include <QPoint>
#include <QDebug>
#include "AbstractModule.h"
#include "graphicsScene.h"

class graphicsScene;
class AbstractModule;

class ModuleFactory : public QObject {
  Q_OBJECT
  typedef AbstractModule* (*CreateModuleCallback)();
  typedef QMap<QString, CreateModuleCallback> CallbackMap;

  public:
    // this two Instance functions are allowed to call the constructor
    static ModuleFactory* Instance(graphicsScene* scene);
    static ModuleFactory* Instance();
    graphicsScene* scene();

    bool RegisterModule(QString ModuleId, CreateModuleCallback CreateFn);
    bool UnregisterModule(QString ModuleID);
    void ListLoadableModules();
    void ListLoadedModules();
    void save();
    void load();
  protected:
    ModuleFactory();
    ModuleFactory(const ModuleFactory&);
    ModuleFactory& operator = (const ModuleFactory&);
    ~ModuleFactory();
  private:
    QMap<QString, CreateModuleCallback> callbacks_;
    QList<AbstractModule*> loadedModules;
    graphicsScene* m_scene;
    static ModuleFactory* privateInstance;
  private:
    AbstractModule* CreateModule(QString ModuleID, QPoint pos);
//     unsigned int DestroyModule(QUuid Id); // todo add that on demand
  signals:
    void appendToQMenuBox(QString ModuleID);
  public slots:
    void createModule(QString ModuleID, QPoint pos);
};
#endif