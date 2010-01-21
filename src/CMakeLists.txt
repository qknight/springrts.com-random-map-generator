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
# SET (QT_USE_QTOPENGL 1)
# SET (QT_USE_QTXML 1) 

project(srmg CXX)

SET( srmg_SOURCES 
  # core gui/code
  main.cpp
  MainWidget.cpp
  ModuleFactory.cpp
  Model.cpp
  Document.cpp
  registermodule_macro.cpp

  # main backend data structure
  backend/DataAbstractItem.cpp 
  backend/DataRoot.cpp 
  backend/DataAbstractModule.cpp
  backend/DataConnection.cpp 

  # libnoise module frontends -> QGraphicsScene items
  frontend/GraphicsScene.cpp
  frontend/ItemView.cpp
  frontend/Module.cpp
  frontend/Port.cpp
  frontend/Connection.cpp

  # libnoise module backends
  modules/NoiseGenBillow.cpp
  modules/NoiseGenPerlin.cpp
  modules/NoiseGenRidgedMulti.cpp
  modules/UtilsNoiseMap.cpp
)

SET( srmg_MOC_HEADERS
  MainWidget.h
  ModuleFactory.h
  Document.h

# main backend data structure
  backend/DataAbstractItem.h
  backend/DataRoot.h 
  backend/DataAbstractModule.h
  backend/DataConnection.h 

# frontend 
  frontend/GraphicsScene.h
  frontend/ItemView.h
)

SET( srmg_UIs
  ui/GraphicsView.ui
)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
  # src/NoiseGenBillow.h lives here (that is './')
  ${CMAKE_SOURCE_DIR}
  # modules
  "${CMAKE_CURRENT_SOURCE_DIR}/modules"
  # backend 
  "${CMAKE_CURRENT_SOURCE_DIR}/backend"
  # frontend
  "${CMAKE_CURRENT_SOURCE_DIR}/frontend"
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
