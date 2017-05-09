TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
   $${BICYCLE_DIR}/Win/Fs/File.h

SOURCES += $${EXAMPLES_DIR}/Fs/ReadFile.cpp \
   $${BICYCLE_DIR}/Win/Common/Global.cpp \
   $${BICYCLE_DIR}/Win/Common/Exception.cpp \
   $${BICYCLE_DIR}/Win/Common/Buffer.cpp \
   $${BICYCLE_DIR}/Win/Common/TextStream.cpp \
   $${BICYCLE_DIR}/Win/Fs/File.cpp

LIBS += User32.lib Setupapi.lib Advapi32.lib

include(deployment.pri)
qtcAddDeployment()
