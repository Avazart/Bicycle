TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Other/Matrix.h \
           $${BICYCLE_DIR}/Other/Rational.h

SOURCES +=  $${EXAMPLES_DIR}/Other/UseMatrix.cpp \
            $${BICYCLE_DIR}/Other/Rational.cpp


