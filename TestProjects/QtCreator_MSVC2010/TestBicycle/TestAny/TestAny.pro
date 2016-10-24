TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Experimental/Any.h \
    $${BICYCLE_DIR}/Experimental/Value.h

SOURCES += $${EXAMPLES_DIR}/main_Any.cpp

include(deployment.pri)
qtcAddDeployment()

