#ifndef NOISENETWORK_H
#define NOISENETWORK_H

#include <QVector>
#include <noise.h>

class NoiseNetwork {
  public:
    ~NoiseNetwork();
    void addModule(noise::module::Module* m);
    noise::module::Module* topLevelModule();
    
    
  private:
    QVector<noise::module::Module*> modules;
};

#endif