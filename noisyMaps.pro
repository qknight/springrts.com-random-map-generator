######################################################################
# Automatically generated by qmake (2.01a) Wed Sep 19 14:28:14 2007
######################################################################

TEMPLATE = app

# Input
HEADERS += src/graphicsScene.h \
 src/modulePort.h \
 src/modulePortConnection.h \
 src/mainWidget.h \
 src/visualModuleItem.h \
 src/AbstractModule.h \
 src/NoiseGenPerlin.h \
 src/ModuleFactory.h \
 src/ModuleWidget.h \
 src/NoiseGenRidgedMulti.h \
 src/Model.h \
 src/DataStorage.h
SOURCES += src/main.cpp src/graphicsScene.cpp \
 src/modulePort.cpp \
 src/modulePortConnection.cpp \
 src/visualModuleItem.cpp \
 src/AbstractModule.cpp \
 src/NoiseGenPerlin.cpp \
 src/ModuleFactory.cpp \
 src/mainWidget.cpp \
 src/ModuleWidget.cpp \
 src/registermodule_macro.cpp \
 src/NoiseGenRidgedMulti.cpp \
 src/Model.cpp \
 src/DataStorage.cpp
FORMS += ui/GraphicsView.ui \
 ui/moduleWidget.ui

TARGET =debug/noisyMaps
CONFIG += debug/
CONFIG += warn_on \
 debug

INCLUDEPATH += /usr/include/noise/ src/

LIBS += -lnoise

UI_DIR = ui
UI_HEADERS_DIR = tmp
UI_SOURCES_DIR = tmp
MOC_DIR = tmp
OBJECTS_DIR = tmp
QMAKE_CLEAN = debug/*
DISTFILES += TODO \
 README

CONFIG -= release

QT += xml \
opengl \
webkit
