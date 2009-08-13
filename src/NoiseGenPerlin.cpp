//
// C++ Implementation: NoiseGenPerlin
//
// Description:
//
//
// Author: Joachim Schiele <js@lastlog.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
// http://libnoise.sourceforge.net/docs/classnoise_1_1module_1_1Perlin.html

#include "NoiseGenPerlin.h"
#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenPerlin);

NoiseGenPerlin::NoiseGenPerlin() : AbstractModule() {
  noise::module::Perlin myModule;
//   addVisualRepresentation();
// 1. [done] create primary graphical module
// 2. create delegate exports for properties:
//      - all module specific paramters
//      - xpos/ypos
//      - static: module ID, module name
// 3. create in/out/mod ports

// interface for generic property access
//   register(double,GetFrequency(), SetFrequency());

//   double   GetFrequency () const
//      Returns the frequency of the first octave.
//   void   SetFrequency (double frequency)
//      Sets the frequency of the first octave.


/*
  double   GetLacunarity () const
     Returns the lacunarity of the Perlin noise.
  noise::NoiseQuality   GetNoiseQuality () const
     Returns the quality of the Perlin noise.
  int   GetOctaveCount () const
     Returns the number of octaves that generate the Perlin noise.
  double   GetPersistence () const
     Returns the persistence value of the Perlin noise.
  int   GetSeed () const
     Returns the seed value used by the Perlin-noise function.
  virtual int   GetSourceModuleCount () const
     Returns the number of source modules required by this noise module.
  virtual double   GetValue (double x, double y, double z) const
     Generates an output value given the coordinates of the specified input value.


  void   SetLacunarity (double lacunarity)
     Sets the lacunarity of the Perlin noise.

  void   SetNoiseQuality (noise::NoiseQuality noiseQuality)
     Sets the quality of the Perlin noise.

  void   SetOctaveCount (int octaveCount)
     Sets the number of octaves that generate the Perlin noise.

  void   SetPersistence (double persistence)
     Sets the persistence value of the Perlin noise.

  void   SetSeed (int seed)
     Sets the seed value used by the Perlin-noise function.
*/
}

NoiseGenPerlin::~NoiseGenPerlin() {
  // delete all Ports
  // delete graphical module
}

QString NoiseGenPerlin::identify() {
  return ID;
}

// void NoiseGenPerlin::addVisualRepresentation() {
//   visualModuleItem* vn = new visualModuleItem();
//   QPoint scenePos = property("scenePos").toPoint();
//   vn->moveBy(scenePos.x(), scenePos.y());
//   vn->setData(0,ID);
//   vn->setData(1,this);
//   ModuleFactory::Instance()->scene()->addItem(vn);
// }

// void ModuleFactory::addVisualRepresentation() {
// //   visualModuleItem* vn = new visualModuleItem();
// //   vn->moveBy(-110,0);
// //   scene->addItem(vn);
//
// //   modulePort* mod0 = new modulePort;
// //   mod0->setParentItem(vn);
// //   mod0->moveBy(230,30);
// //   scene->addItem(mod0);
//   //
// //   visualModuleItem* vn2 = new visualModuleItem();
// //   vn2->moveBy(200,90);
// //   scene->addItem(vn2);
//   //
// //   modulePort* mod1 = new modulePort;
// //   mod1->setParentItem(vn2);
// //   mod1->moveBy(90,30);
//   //
// //   modulePortConnection* a = new modulePortConnection(mod1,mod0);
// //   a->setZValue(100);
// //   scene->addItem(a);
//   //
// //   for (int i=0; i < 4; ++i) {
// //     modulePort* m = new modulePort;
// //     m->setParentItem(vn);
// //     m->moveBy(200,30+i*30);
// //     m->setParentItem(vn2);
// //   }
// }
