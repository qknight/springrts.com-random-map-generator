
#include "TranslatePoint.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(TranslatePoint);

TranslatePoint::TranslatePoint() : DataAbstractModule(1,0,1) {
  setProperty("FIXME", 112);
}

TranslatePoint::~TranslatePoint() {
}

QString TranslatePoint::identify() {
    return ID;
}
