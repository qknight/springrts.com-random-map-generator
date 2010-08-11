#!/usr/bin/python
# -*- coding: iso-8859-1 -*-
import os
import string
from string import Template 

modules="""
Utils NoiseMapBuilderPlane      1 0 0 
Utils RendererImage             1 0 0
Utils Image                     1 0 0

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

Spring Mapgenerator             1 0 0
"""

#myClassName="Perlin"
#myCategoryName="Generator"
#myModuleName=myCategoryName + "::" + myClassName 
#myIFNDEF=myCategoryName.upper() + "_" + myClassName.upper() + "__HH"
#
#portIN=1
#portMOD=1
#portOUT=3





myclass_h="""
#ifndef $MYIFNDEF
#define $MYIFNDEF

#include <DataAbstractModule.h>

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
};

#endif
"""


#t = Template(myclass_h)
#s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myModuleName, MYIFNDEF=myIFNDEF)
#print s



myclass_cpp="""
#include "$MYMODULENAME.h"
#include "ModuleFactory.h"

#include "registermodule_macro.cpp"

M_REGISTER($MYCLASS);

$MYCLASS::$MYCLASS() : DataAbstractModule($IN,$MOD,$OUT) {
  setProperty("FIXME", 112);
}

$MYCLASS::~$MYCLASS() {
}

QString $MYCLASS::identify() {
    return ID;
}
"""


#t = Template(myclass_cpp)
#s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myClassName,IN=portIN,MOD=portMOD,OUT=portOUT)
#print s


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
  if not os.path.exists(myCategoryName.lower()):
   os.mkdir(myCategoryName.lower(), 0777)
  print "modules/" + myCategoryName.lower() + "/" + myClassName + ".cpp"
  f = open(myCategoryName.lower() + "/" + myClassName + ".cpp", 'w')
  t = Template(myclass_cpp)
  s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myClassName,IN=portIN,MOD=portMOD,OUT=portOUT)
  f.write(s)
  f.close()
  f = open(myCategoryName.lower() + "/" + myClassName + ".h", 'w')
  t = Template(myclass_h)
  s = t.substitute(MYCLASS=myClassName, MYMODULENAME=myModuleName, MYIFNDEF=myIFNDEF)
  f.write(s)
  f.close()








