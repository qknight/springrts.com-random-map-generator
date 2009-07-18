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
//     qDebug() << "created ModuleFactory::Instance()";
    privateInstance = new ModuleFactory();
//   } else  {
//     qDebug() << "error: duplicated attempt detected in creating a ModuleFactory instance which already existed but still graphicsScene* as arguemnt was given";
//     exit(0);
  }
  return privateInstance;
}

// ModuleFactory* ModuleFactory::Instance() {
//   if (privateInstance == NULL) {
//     qDebug() << "ModuleFactory::Instance() wasn't initialized yet, execution stopping!";
//     exit(0);
//   }
//   return privateInstance;
// }

// will only work if the ModuleFactory singleton is initialized already
// graphicsScene* ModuleFactory::scene() {
//   return m_scene;
// }

bool ModuleFactory::RegisterModule(QString ModuleId, CreateModuleCallback CreateFn) {
    // BUG add handles for duplicated Register attempts
    callbacks_.insert( ModuleId, CreateFn );
    // insert them into the menu
    emit appendToQMenuBox(ModuleId);
    return true; //todo fix that
}

bool ModuleFactory::UnregisterModule(QString ModuleId) {
    return callbacks_.remove(ModuleId) == 1;
}

void ModuleFactory::createModule(QString ModuleID, QPoint pos) {
    CreateModule(ModuleID, pos);
}

AbstractModule* ModuleFactory::CreateModule(QString ModuleID, QPoint pos) {
    CallbackMap::const_iterator i = callbacks_.find(ModuleID);
    if (i != callbacks_.end()) {
        AbstractModule* z = (i.value())(); // constructor call
        z->setProperty("scenePos", pos);
        loadedModules.append(z);
//         qDebug() << "CreateModule created a new Module::" << ModuleID;
        return z;
    }
    qDebug() << "weird error: can't find ModuleID to load a new module";
    return NULL;
}

void ModuleFactory::ListLoadableModules() {
    qDebug("%i module(s)", callbacks_.size());

    QMapIterator<QString,CreateModuleCallback> i(callbacks_);
    while (i.hasNext()) {
        i.next();
        qDebug() << "    " << i.key();
    }
}

void ModuleFactory::ListLoadedModules() {
    qDebug("%i module(s) loaded", loadedModules.size());
}
