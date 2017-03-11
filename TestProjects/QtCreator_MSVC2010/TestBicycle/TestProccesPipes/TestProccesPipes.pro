TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Process/Pipe.h \
    $${BICYCLE_DIR}/Process/Process.h \
    $${BICYCLE_DIR}/Process/Environment.h \
    $${BICYCLE_DIR}/Buffer.h \
    $${BICYCLE_DIR}/Console.h \
    $${BICYCLE_DIR}/Global.h \
    $${BICYCLE_DIR}/IODevice.h \
    $${BICYCLE_DIR}/IOStream.h \
    $${BICYCLE_DIR}/NonCopyable.h \
    $${BICYCLE_DIR}/SystemException.h

SOURCES += $${EXAMPLES_DIR}/main_ProcessPipes.cpp \
    $${BICYCLE_DIR}/Process/Pipe.cpp \
    $${BICYCLE_DIR}/Process/Process.cpp \
    $${BICYCLE_DIR}/Process/Environment.cpp \
    $${BICYCLE_DIR}/Buffer.cpp \
    $${BICYCLE_DIR}/Console.cpp \
    $${BICYCLE_DIR}/Global.cpp \
    $${BICYCLE_DIR}/IOStream.cpp \
    $${BICYCLE_DIR}/SystemException.cpp

LIBS += User32.lib

include(deployment.pri)
qtcAddDeployment()

