TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

SOURCES += $${EXAMPLES_DIR}/main_Format.cpp \

HEADERS += $${BICYCLE_DIR}/Experimental/Format.h

include(deployment.pri)
qtcAddDeployment()

