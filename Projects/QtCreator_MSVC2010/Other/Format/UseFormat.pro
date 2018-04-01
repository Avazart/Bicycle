TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Other/Format.h

SOURCES += $${EXAMPLES_DIR}/Other/UseFormat.cpp

include(deployment.pri)
qtcAddDeployment()
