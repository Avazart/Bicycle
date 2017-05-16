TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/Process/Process.h \
    $${BICYCLE_DIR}/Win/Process/Environment.h \
    $${BICYCLE_DIR}/Algorithm/Mismatch.h

SOURCES += $${EXAMPLES_DIR}/Process/GetSetEnvironment.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/Common/Event.cpp \
    $${BICYCLE_DIR}/Win/Process/Pipe.cpp \
    $${BICYCLE_DIR}/Win/Process/Process.cpp \
    $${BICYCLE_DIR}/Win/Process/Environment.cpp

LIBS += User32.lib

include(deployment.pri)
qtcAddDeployment()
