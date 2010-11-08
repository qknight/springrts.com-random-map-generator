#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import os
import string
from string import Template 

#Utils NoiseMapBuilderPlane      1 0 0 
#Utils RendererImage             1 0 0
#Utils Image                     1 0 0
#Spring Mapgenerator             1 0 0

modules="""
Generator Perlin                0 0 1
Generator Billow                0 0 1
Generator RidgedMulti           0 0 1
Generator Checkerboard          0 0 1
Generator Const                 0 0 1
Generator Cylinders             0 0 1
Generator Spheres               0 0 1
Generator Voronoi               0 0 1

Combiner Add                    2 0 1
Combiner Max                    2 0 1
Combiner Min                    2 0 1
Combiner Multiply               2 0 1
Combiner Power                  2 0 1

Modifier Abs                    1 0 1
Modifier Clamp                  1 0 1
Modifier Curve                  1 0 1
Modifier Exponent               1 0 1
Modifier Invert                 1 0 1
Modifier ScaleBias              1 0 1
Modifier Terrace                1 0 1

Selector Blend                  2 1 1
Selector Select                 2 1 1

Transformer Displace            1 3 1
Transformer RotatePoint         1 0 1
Transformer ScalePoint          1 0 1
Transformer TranslatePoint      1 0 1
Transformer Turbulence          1 0 1
"""

myclass_h="""#ifndef $MYIFNDEF
#define $MYIFNDEF

#include <DataAbstractModule.h>
#include <noise.h>

#define ID "$MYMODULENAME"

// http://libnoise.sourceforge.net/docs/group__modules.html

/**
	@author Joachim Schiele <js@lastlog.de>
*/
class $MYCLASS : public DataAbstractModule {
public:
    $MYCLASS();
    ~$MYCLASS();

    QString identify();
    NoiseNetwork* network();
    bool ready();
};

#endif
"""

# testing code for the .h creation
#t = Template(myclass_h)
#s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myModuleName, MYIFNDEF=myIFNDEF)
#print s

myclass_cpp="""#include "$MYMODULENAME.h"
#include "ModuleFactory.h"
#include "NoiseNetwork.h"

#include "registermodule_macro.cpp"

M_REGISTER($MYCLASS);

$MYCLASS::$MYCLASS() : DataAbstractModule($IN,$MOD,$OUT) {
  setProperty("FIXME", 112); // FIXME setting properties should be done via makros
}

$MYCLASS::~$MYCLASS() {
}

NoiseNetwork* $MYCLASS::network() {
  // 0. query module for readieness
  if (ready()) {
  //   1. create a noiseNetwork (if generator module)
       NoiseNetwork* noiseNetwork = new NoiseNetwork;
  
  //   2. construct the local module (in this case Perlin)
       noise::module::$MYCLASS* m_$MYCLASS = new noise::module::$MYCLASS();
       noiseNetwork->addModule(m_$MYCLASS);

  //   3. assign all properties
  //   m_perlin->SetOctaveCount (property("OctaveCount"));
  //   ...
  
  //   4. connect all source modules (in case of a generator module: none) & merge the NoiseNetwork(s)
  
  //   foreach(input i)
  //       m_perlin->SetSourceModule(i->portnumber, i->topLevelModule);
  //       noiseNetwork->merge(i->network)
  //     OR IN SHORT:
  //       //noiseNetwork->setSourceNetwork(i, i->network)
  //   foreach(input m)
  //     m_perlin->SetControlModule(m->topLevelModule);
  //     noiseNetwork->merge(m->network)

    return noiseNetwork;
  }
  return NULL;
}

bool $MYCLASS::ready() {
  //   foreach(input i)
  //     if (i is unused)
  //       return false;
  //   foreach(modput m)
  //     if (m is unused)
  //       return false;
  return true;
}
"""
# testing code for the .cpp creation
#t = Template(myclass_cpp)
#s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myClassName,IN=portIN,MOD=portMOD,OUT=portOUT)
#print s

# this code will create directories, place cpp and h files into these directories
newlines=modules.split('\n')
for i in newlines:
 mylist=i.split()
 if len(mylist) > 0:
  myClassName=mylist[1]
  myCategoryName=mylist[0]
  myModuleName=myCategoryName + "::" + myClassName 
  myIFNDEF=myCategoryName.upper() + "_" + myClassName.upper() + "__HH"
  portIN=mylist[2]
  portMOD=mylist[3]
  portOUT=mylist[4]
  t = Template(myclass_h)
  s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myModuleName, MYIFNDEF=myIFNDEF)
  #print s
  
  # creating the directory for the module, based on it's class
  if not os.path.exists(myCategoryName.lower()):
   os.mkdir(myCategoryName.lower(), 0777)
  print "modules/" + myCategoryName.lower() + "/" + myClassName + ".cpp"
  
  # creating the .cpp file
  f = open(myCategoryName.lower() + "/" + myClassName + ".cpp", 'w')
  t = Template(myclass_cpp)
  s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myClassName,IN=portIN,MOD=portMOD,OUT=portOUT)
  f.write(s)
  
  print "modules/" + myCategoryName.lower() + "/" + myClassName + ".h"
  
  # creating the .h file
  f.close()
  f = open(myCategoryName.lower() + "/" + myClassName + ".h", 'w')
  t = Template(myclass_h)
  s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myModuleName, MYIFNDEF=myIFNDEF)
  f.write(s)
  f.close()
  
