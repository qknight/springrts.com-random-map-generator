
//
// C++ Interface: ModuleFactory
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef MODULEFACTORY_H
#define MODULEFACTORY_H

/**
  @author Joachim Schiele <js@lastlog.de>
*/

class ModuleFactorySingleton {
  public:
    ModuleFactory* instance(graphicsScene* scene); // only called once
    //ModuleFactory* instance(); // todo: add for initialized use
  private:
    static ModuleFactorySingleton* moduleFactorySingleton;
  protected:
    ModuleFactorySingleton();
    ModuleFactorySingleton(const ModuleFactorySingleton&);
    ModuleFactorySingleton& operator = (const ModuleFactorySingleton&);

};

#endif
