//
// C++ Implementation: registermodule_macro
//
// Description:
//  this is a macro which helps to register all modules
//  the trick is we do that in the global namespace so we do NOT
//  have to include all modules headers in the mainWidget.cpp code
//  nor do we have to instantiate a object there.
//
//  if not done this way this would result in a major recompile
//  one minor changes in the modules
//
//  RMI is the RegisterModuleInterface
//
// Usage:
//  in a module one has to call this macro which then registers the
//  module in the ModuleFactory singleton
//  -> therefore create a class c you want to register
//  -> class c must inherit from DataAbstractModule()
//  -> class c is named 'myClassFoo' then use the M_REGISTER(myClassFoo); macro
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
// thanks for help from
//   Chrisoph Behle
//   Konstantin Alexandrovich Olkhovskij
//   http://www.ebyte.it/library/codesnippets/WritingCppMacros.html#1

#define M_REGISTER(CLASSNAME)                                                        \
                                                                                     \
class RMI_##_##CLASSNAME {                                                           \
  public:                                                                            \
    RMI_##_##CLASSNAME();                                                            \
    static DataAbstractModule* CreateModule();                                       \
    const QString Id;                                                                \
};                                                                                   \
                                                                                     \
RMI_##_##CLASSNAME::RMI_##_##CLASSNAME() {                                           \
  const QString Id = ID;                                                             \
  ModuleFactory::Instance()->RegisterModule(Id, RMI_##_##CLASSNAME::CreateModule);   \
}                                                                                    \
                                                                                     \
DataAbstractModule* RMI_##_##CLASSNAME::CreateModule() {                             \
  return new CLASSNAME();                                                            \
}                                                                                    \
                                                                                     \
QString CLASSNAME::identify() {                                                      \
    return ID;                                                                       \
}                                                                                    \
                                                                                     \
static RMI_##_##CLASSNAME f = RMI_##_##CLASSNAME();
