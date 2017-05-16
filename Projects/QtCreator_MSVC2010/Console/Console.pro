TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../Examples
BICYCLE_DIR =  ../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/Console/Console.h

SOURCES += $${EXAMPLES_DIR}/Console/main.cpp \
    $${BICYCLE_DIR}/Win/Console/Console.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp

include(deployment.pri)
qtcAddDeployment()

