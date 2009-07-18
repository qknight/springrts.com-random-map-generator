//
// C++ Interface: AbstractModule
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

// #include <QUuid>
#include <QObject>
#include "ModuleFactory.h"
#include "ModuleWidget.h"

class AbstractModule : public QObject {
  Q_OBJECT
  public:
    AbstractModule();
    ~AbstractModule();
    virtual QString identify()=0;

  private:
//     bool virtual setProperty(const char * name, const QVariant & value )=0;
    bool status; // this represents if the module is in ready state or not for further processing
  protected:
    ModuleWidget moduleWidget;
};

Q_DECLARE_METATYPE(AbstractModule*)
#endif
