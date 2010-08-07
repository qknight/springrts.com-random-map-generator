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
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER(NoiseGenPerlin);

NoiseGenPerlin::NoiseGenPerlin() : DataAbstractModule(0,0,1) {
  setProperty("frequency", 0.234f);
  setProperty("lacunarity", 0.2f);
  setProperty("Octave count", 8);
  setProperty("Persistence",22);
  setProperty("Seed",3);
  setProperty("Noise quality",3);
}

NoiseGenPerlin::~NoiseGenPerlin() {
//     qDebug() << __PRETTY_FUNCTION__;
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
