#include "RendererImage.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(RendererImage);

RendererImage::RendererImage() : DataAbstractModule(1,0,0) {
  setProperty("FIXME", 112);
}

RendererImage::~RendererImage() {
}

