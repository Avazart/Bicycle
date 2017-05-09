TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/WinSocks/TcpClient/TcpClient.h

SOURCES += $${EXAMPLES_DIR}/WinSocks/HttpRequest.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/Common/Buffer.cpp \
    $${BICYCLE_DIR}/Win/Common/TextStream.cpp \
    $${BICYCLE_DIR}/Win/WinSocks/TcpClient/TcpClient.cpp \
    $${BICYCLE_DIR}/Win/WinSocks/WsaException.cpp \
    $${BICYCLE_DIR}/Win/WinSocks/Sockets.cpp

LIBS += Ws2_32.lib

include(deployment.pri)
qtcAddDeployment()

