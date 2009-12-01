cmake_minimum_required(VERSION 2.6)

find_package(Qt4)

project(srmg CXX)

SET( my_MOC_SOURCES
  AbstractModule.cpp
  Model.cpp
  ModuleFactory.cpp
  ModuleWidget.cpp
  graphicsScene.cpp
  mainWidget.cpp
)

SET( my_SOURCES
  DataStorage.cpp
  ModuleFactorySingleton.cpp
  NoiseGenBillow.cpp
  NoiseGenPerlin.cpp
  NoiseGenPerlinInterface.cpp
  NoiseGenRidgedMulti.cpp
  UtilsNoiseMap.cpp
  main.cpp
  modulePort.cpp
  modulePortConnection.cpp
  registermodule_macro.cpp
  visualModuleItem.cpp
)

SET( my_HEADERS
  AbstractModule.h
  DataStorage.h
  Model.h
  ModuleFactory.h
  ModuleFactorySingleton.h
  ModuleWidget.h
  NoiseGenBillow.h
  NoiseGenPerlin.h
  NoiseGenPerlinInterface.h
  NoiseGenRidgedMulti.h
  UtilsNoiseMap.h
  graphicsScene.h
  mainWidget.h
  modulePort.h
  modulePortConnection.h
  visualModuleItem.h
)

SET( my_UI
 ui/GraphicsView.ui
 ui/moduleWidget.ui
)

INCLUDE_DIRECTORIES(
  ${QT_INCLUDE_DIR}
  ${QT_QTNETWORK_INCLUDE_DIR}
  ${QT_QTXML_INCLUDE_DIR}
   "/usr/include/noise/"
   "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/"
)

set (my_UIC_DIR="${CMAKE_CURRENT_SOURCE_DIR}/ui")

QT4_WRAP_UI(my_UI ${my_UIC_DIR})

QT4_WRAP_CPP(my_MOC_SRCS ${foo_MOC_HDRS})

ADD_EXECUTABLE(srmg ${my_SOURCES} ${my_MOC_SOURCES} ${my_UIC_DIR})

TARGET_LINK_LIBRARIES(
  srmg
  ${QT_LIBRARIES}
#   ${QT_QTNETWORK_LIBRARIES}
  ${QT_QTXML_LIBRARIES}
   "-lnoise"
)
