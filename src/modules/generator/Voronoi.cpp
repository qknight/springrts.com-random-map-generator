
#include "Voronoi.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Voronoi);

Voronoi::Voronoi() : DataAbstractModule(0,0,1) {
  setProperty("FIXME", 112);
}

Voronoi::~Voronoi() {
}

QString Voronoi::identify() {
    return ID;
}
