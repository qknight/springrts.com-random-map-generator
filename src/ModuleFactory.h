//
// C++ Interface: ModuleFactory
//
// Description:
//   This class implements a object factory pattern. It's use is obvious: saving/loading states.
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

#include <QDebug>
#include <QMap>
#include <QMenu>
#include <QPoint>
#include <QVector>

#include "DataAbstractModule.h"

class DataAbstractModule;

/*! this class may only be used from Model.cpp/Model.h and if you try to use it outside here, then
you won't be able to add modules to the backend since this is done using insertRows only! */
class ModuleFactory : public QObject {
    friend class Model;

    Q_OBJECT
    typedef DataAbstractModule* (*CreateModuleCallback)();
    typedef QMap<QString, CreateModuleCallback> CallbackMap;
protected:
    // this two Instance functions are allowed to call the constructor
    static ModuleFactory* Instance();

    bool RegisterModule(QString ModuleId, CreateModuleCallback CreateFn);
    bool UnregisterModule(QString ModuleID);

    QVector<QString> LoadableModuleNames();
    int  LoadableModulesCount();
    int  LoadedModulesCount();

    void save();
    void load();
    void createModule(QString ModuleID/*, QPoint pos*/);
    void ListLoadableModules();
    void ListLoadedModules();
// protected:
    ModuleFactory();
    ModuleFactory(const ModuleFactory&);
    ModuleFactory& operator = (const ModuleFactory&);
    ~ModuleFactory();
private:
    QMap<QString, CreateModuleCallback> loadableModules;  // modules which could be loaded
    QList<DataAbstractModule*> loadedModules;                 // modules which are already loaded
    static ModuleFactory* privateInstance;
    DataAbstractModule* CreateModule(QString ModuleID/*, QPoint pos*/);
//     unsigned int DestroyModule(QUuid Id); // todo add that on demand
signals:
    void appendToQMenuBox(QString ModuleID);
};
#endif
