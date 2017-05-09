TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/WinInet/FtpClient.h \
    $${BICYCLE_DIR}/Win/WinInet/WinInetException.h \

SOURCES += $${EXAMPLES_DIR}/WinInet/UseFtpClient/UseFtpClient.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/WinInet/WinInetException.cpp \
    $${BICYCLE_DIR}/Win/WinInet/FtpClient.cpp

LIBS += -lwininet

include(deployment.pri)
qtcAddDeployment()

