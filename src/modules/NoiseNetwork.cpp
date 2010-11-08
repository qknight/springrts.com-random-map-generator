#include "NoiseNetwork.h"
#include <QDebug>

NoiseNetwork::~NoiseNetwork() {
  qDebug() << __PRETTY_FUNCTION__;
//     foreach(Module* m, all_modules)
//       delete m;
}

void NoiseNetwork::addModule(noise::module::Module* m) {
  modules += m;
}

noise::module::Module* NoiseNetwork::topLevelModule() {
  if (modules.size())
    return modules.back();
  return NULL;
}