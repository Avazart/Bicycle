TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/Serial/SerialPortInfo.h \
    $${BICYCLE_DIR}/Algorithm/Trim.h \
    $${BICYCLE_DIR}/Algorithm/IsAnyOf.h

SOURCES += $${EXAMPLES_DIR}/Serial/GetSeiralInfo.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/Serial/SerialPortInfo.cpp

LIBS += User32.lib Setupapi.lib Advapi32.lib

include(deployment.pri)
qtcAddDeployment()

