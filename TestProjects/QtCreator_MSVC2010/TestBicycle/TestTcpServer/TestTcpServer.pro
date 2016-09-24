TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

SOURCES += $${EXAMPLES_DIR}/main_TcpServer.cpp \
    $${BICYCLE_DIR}/Tcp/ClientThread.cpp \
    $${BICYCLE_DIR}/Tcp/SocketException.cpp \
    $${BICYCLE_DIR}/Tcp/TcpClient.cpp \
    $${BICYCLE_DIR}/Tcp/TcpServer.cpp \
    $${BICYCLE_DIR}/Tcp/TcpSockets.cpp \
    $${BICYCLE_DIR}/Buffer.cpp \
    $${BICYCLE_DIR}/Global.cpp \
    $${BICYCLE_DIR}/IODevice.cpp \
    $${BICYCLE_DIR}/IOStream.cpp \
    $${BICYCLE_DIR}/NonCopyable.cpp \
    $${BICYCLE_DIR}/SystemException.cpp \
    $${BICYCLE_DIR}/Thread.cpp \
    $${BICYCLE_DIR}/Sync/AtomicCounter.cpp

HEADERS += \
    $${BICYCLE_DIR}/Tcp/SocketException.h \
    $${BICYCLE_DIR}/Buffer.h \
    $${BICYCLE_DIR}/Global.h \
    $${BICYCLE_DIR}/IODevice.h \
    $${BICYCLE_DIR}/IOStream.h \
    $${BICYCLE_DIR}/NonCopyable.h \
    $${BICYCLE_DIR}/Tcp/ClientThread.h \
    $${BICYCLE_DIR}/Tcp/TcpClient.h \
    $${BICYCLE_DIR}/Tcp/TcpServer.h \
    $${BICYCLE_DIR}/Tcp/TcpSockets.h \
    $${BICYCLE_DIR}/Thread.h \
    $${BICYCLE_DIR}/Sync/AtomicCounter.h

LIBS += Ws2_32.lib

include(deployment.pri)
qtcAddDeployment()

