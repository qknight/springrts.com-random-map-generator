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
  FilterProxyModel.cpp
  Document.cpp
  registermodule_macro.cpp

  # main backend data structure
  backend/DataAbstractItem.cpp 
  backend/DataRoot.cpp 
  backend/DataAbstractModule.cpp
  backend/DataProperty.cpp 
  backend/DataPort.cpp 
  backend/DataConnection.cpp 

  # libnoise module frontends -> QGraphicsScene items
  frontend/GraphicsScene.cpp
  frontend/GraphicsView.cpp
  frontend/ItemView.cpp
  frontend/Module.cpp
  frontend/Port.cpp
  frontend/Connection.cpp
  frontend/GraphicsItemModelExtension.cpp

  # libnoise module backends
  modules/utils/NoiseMapBuilderPlane.cpp
  modules/utils/RendererImage.cpp
  modules/utils/Image.cpp
  modules/generator/Perlin.cpp
  modules/generator/Billow.cpp
  modules/generator/RidgedMulti.cpp
  modules/generator/Checkerboard.cpp
  modules/generator/Const.cpp
  modules/generator/Cylinders.cpp
  modules/generator/Spheres.cpp
  modules/generator/Voronoi.cpp
  modules/combiner/Add.cpp
  modules/combiner/Max.cpp
  modules/combiner/Min.cpp
  modules/combiner/Multiply.cpp
  modules/combiner/Power.cpp
  modules/modifier/Abs.cpp
  modules/modifier/Clamp.cpp
  modules/modifier/Curve.cpp
  modules/modifier/Exponent.cpp
  modules/modifier/Invert.cpp
  modules/modifier/ScaleBias.cpp
  modules/modifier/Terrace.cpp
  modules/selector/Blend.cpp
  modules/selector/Select.cpp
  modules/transformer/Displace.cpp
  modules/transformer/RotatePoint.cpp
  modules/transformer/ScalePoint.cpp
  modules/transformer/TranslatePoint.cpp
  modules/transformer/Turbulence.cpp
  modules/spring/Mapgenerator.cpp

)

SET( srmg_MOC_HEADERS
  MainWidget.h
  ModuleFactory.h
  Document.h
  FilterProxyModel.h

# frontend 
  frontend/GraphicsScene.h
  frontend/GraphicsView.h
  frontend/ItemView.h
)

SET( srmg_UIs
  ui/GraphicsView.ui
)

SET( srmg_RESOURCES
  resources/resources.qrc
)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
  # src/NoiseGenBillow.h lives here (that is './')
  ${CMAKE_SOURCE_DIR}
  # modules
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/selector"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/generator"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/utils"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/combiner"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/modifier"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/spring"
  "${CMAKE_CURRENT_SOURCE_DIR}/modules/transformer"
  # backend 
  "${CMAKE_CURRENT_SOURCE_DIR}/backend"
  # frontend
  "${CMAKE_CURRENT_SOURCE_DIR}/frontend"
  # AbstractModule.h lives here (that is 'src/')
  ${CMAKE_CURRENT_SOURCE_DIR}
  # QT4_WRAP_UI writes ui_whatever.h here (that is './' and uic is used)
  ${CMAKE_CURRENT_BINARY_DIR}
  # this is the external library used (includes of libnoise live here)
#   "/usr/include/noise/"
)

# QT4_WRAP_UI(outfiles inputfile ... OPTIONS ...)
QT4_WRAP_UI(srmg_SOURCES ${srmg_UIs})

# macro QT4_WRAP_CPP(outfiles inputfile ... )
QT4_WRAP_CPP (srmg_SOURCES ${srmg_MOC_HEADERS})

QT4_ADD_RESOURCES(srmg_SOURCES ${srmg_RESOURCES})

ADD_EXECUTABLE(srmg ${srmg_SOURCES} ${srmg_RESOURCES})

# -lnoise if for the external library
# TARGET_LINK_LIBRARIES( srmg ${QT_LIBRARIES} "-lnoise" )
TARGET_LINK_LIBRARIES( srmg ${QT_LIBRARIES} )

INSTALL ( TARGETS srmg DESTINATION bin )
