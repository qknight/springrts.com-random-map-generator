#include "Image.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(Image);

Image::Image() : DataAbstractModule(1,0,0) {
  setProperty("FIXME", 112);
}

Image::~Image() {
}

