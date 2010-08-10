//
// C++ Implementation: ModuleFactory
//
// Description:
//  this is an object factory used for save/load functionality in cpp.
//  it is realized in form of a singleton pattern
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ModuleFactory.h"

ModuleFactory* ModuleFactory::privateInstance = NULL;

ModuleFactory::ModuleFactory() {
//     qDebug("constructor ModuleFactory");
}

ModuleFactory::~ModuleFactory() { }

ModuleFactory* ModuleFactory::Instance() {
    if (privateInstance == NULL) {
//         qDebug() << "created ModuleFactory::Instance()";
        privateInstance = new ModuleFactory();
    }
    return privateInstance;
}

bool ModuleFactory::RegisterModule(QString ModuleId, CreateModuleCallback CreateFn) {
    //TODO fix false case
    //TODO add handles for duplicated Register attempts meaning if one wants to register 'mymodule' a second time
    loadableModules.insert( ModuleId, CreateFn );
    return true;
}

bool ModuleFactory::UnregisterModule(QString ModuleId) {
    return loadableModules.remove(ModuleId) == 1;
}

// private
void ModuleFactory::createModule(QString ModuleID/*, QPoint pos*/) {
    CreateModule(ModuleID/*, pos*/);
}

// public
DataAbstractModule* ModuleFactory::CreateModule(QString ModuleID) {
    CallbackMap::const_iterator i = loadableModules.find(ModuleID);
    if (i != loadableModules.end()) {
        DataAbstractModule* z = (i.value())(); // constructor call
//         z->setProperty("scenePos", pos);
        loadedModules.append(z);
//         qDebug() << "CreateModule created a new Module::" << ModuleID;
        return z;
    }
    // FIXME this is just for debugging, could be removed later
    qDebug() << __PRETTY_FUNCTION__ <<" weird error: can't find ModuleID to load a new module";
    return NULL;
}

void ModuleFactory::ListLoadableModules() {
    qDebug("%i module(s)", loadableModules.size());

    QMapIterator<QString,CreateModuleCallback> i(loadableModules);
    while (i.hasNext()) {
        i.next();
        qDebug() << "    " << i.key();
    }
}

void ModuleFactory::ListLoadedModules() {
    qDebug("%i module(s) loaded", loadedModules.size());
}

int ModuleFactory::LoadableModulesCount() {
    return loadableModules.size();
}

int ModuleFactory::LoadedModulesCount() {
    return loadedModules.size();
}

QVector<QString> ModuleFactory::LoadableModuleNames() {
    return loadableModules.keys().toVector();
}


