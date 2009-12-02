cmake_minimum_required(VERSION 2.6)

# a high quality example
# http://github.com/marcbowes/mxitc

# http://cmake.org/cmake/help/cmake2.6docs.html#command:qt_wrap_ui
# http://da-crystal.net/GCMS/blog/cmake-amp-qt4-modules/
# http://www.qtforum.de/forum/viewtopic.php?p=47193&sid=5b4e0e82a754b33492fb9e8a1909aa9d

# i would to see more projects using these defaults
ADD_DEFINITIONS( "-Wall -ansi" )
# ADD_DEFINITIONS( "-Wall -ansi -pedantic" )

find_package(Qt4)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4
SET (QT_USE_QTOPENGL 1)
SET (QT_USE_QTXML 1) 

project(srmg CXX)

SET( srmg_SOURCES
  AbstractModule.cpp
  Model.cpp
  ModuleFactory.cpp
  ModuleWidget.cpp
  graphicsScene.cpp
  mainWidget.cpp
  main.cpp
  DataStorage.cpp
  NoiseGenBillow.cpp
  NoiseGenPerlin.cpp
  NoiseGenPerlinInterface.cpp
  NoiseGenRidgedMulti.cpp
  UtilsNoiseMap.cpp
  modulePort.cpp
  modulePortConnection.cpp
  registermodule_macro.cpp
  visualModuleItem.cpp
)

SET( srmg_MOC_HEADERS
  mainWidget.h
  graphicsScene.h
  ModuleWidget.h
  ModuleFactory.h
  AbstractModule.h
)

SET( srmg_UIs
  ui/moduleWidget.ui
  ui/GraphicsView.ui
)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
  # src/NoiseGenBillow.h lives here (that is './')
  ${CMAKE_SOURCE_DIR}
  # AbstractModule.h lives here (that is 'src/')
  ${CMAKE_CURRENT_SOURCE_DIR}
  # QT4_WRAP_UI writes ui_whatever.h here (that is './' and uic is used)
  ${CMAKE_CURRENT_BINARY_DIR}
  # this is the external library used (includes of libnoise live here)
  "/usr/include/noise/"
)

# QT4_WRAP_UI(outfiles inputfile ... OPTIONS ...)
QT4_WRAP_UI(srmg_SOURCES ${srmg_UIs})

# macro QT4_WRAP_CPP(outfiles inputfile ... )
QT4_WRAP_CPP (srmg_SOURCES ${srmg_MOC_HEADERS}) 

ADD_EXECUTABLE(srmg ${srmg_SOURCES} )

# -lnoise if for the external library
TARGET_LINK_LIBRARIES( srmg ${QT_LIBRARIES} "-lnoise" )

INSTALL ( TARGETS srmg DESTINATION bin )