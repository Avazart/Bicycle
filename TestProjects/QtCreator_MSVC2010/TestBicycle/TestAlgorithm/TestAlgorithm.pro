TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Algorithm/IsAnyOf.h \
           $${BICYCLE_DIR}/Algorithm/Trim.h \
           $${BICYCLE_DIR}/Algorithm/Split.h \
           $${BICYCLE_DIR}/Algorithm/SplitEx.h \
           $${BICYCLE_DIR}/Algorithm/SearchEx.h \
           $${BICYCLE_DIR}/Algorithm/Join.h \
           $${BICYCLE_DIR}/Algorithm/Filter.h \
           $${BICYCLE_DIR}/Algorithm/Wrap.h \
           $${BICYCLE_DIR}/Algorithm/EndsWith.h \
           $${BICYCLE_DIR}/Algorithm/StartsWith.h

SOURCES += $${EXAMPLES_DIR}/main_Algorithm.cpp

include(deployment.pri)
qtcAddDeployment()
