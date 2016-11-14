TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Experimental/Library.h \
    $${BICYCLE_DIR}/Experimental/Library.h \
    $${BICYCLE_DIR}/Global.h \
    $${BICYCLE_DIR}/NonCopyable.h \
    $${BICYCLE_DIR}/SystemException.h\
    $${BICYCLE_DIR}/Console.h

SOURCES += $${EXAMPLES_DIR}/main_Library.cpp \
    $${BICYCLE_DIR}/Experimental/Library.cpp \
    $${BICYCLE_DIR}/Global.cpp \
    $${BICYCLE_DIR}/SystemException.cpp\
    $${BICYCLE_DIR}/Console.cpp

include(deployment.pri)
qtcAddDeployment()
