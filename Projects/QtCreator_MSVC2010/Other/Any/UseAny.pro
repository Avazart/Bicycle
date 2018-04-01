TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Other/Any.h

SOURCES +=  $${EXAMPLES_DIR}/Other/UseAny.cpp \
            $${BICYCLE_DIR}/Other/Any.cpp


