TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/Serial/SerialPort.h \
    $${BICYCLE_DIR}/Win/TextStream/TextStream.h

SOURCES += $${EXAMPLES_DIR}/Serial/WorkWithSerial.cpp \
    $${BICYCLE_DIR}/Win/TextStream/Buffer.cpp \
    $${BICYCLE_DIR}/Win/TextStream/TextStream.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/Common/Event.cpp \
    $${BICYCLE_DIR}/Win/Serial/SerialPort.cpp

include(deployment.pri)
qtcAddDeployment()

