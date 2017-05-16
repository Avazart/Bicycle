TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/WinInet/HttpClient.h \
    $${BICYCLE_DIR}/Win/WinInet/WinInetException.h \
    $${BICYCLE_DIR}/Win/TextStream/TextStream.h

SOURCES += $${EXAMPLES_DIR}/WinInet/UseHttpClient/UseHttpClient.cpp \
    $${BICYCLE_DIR}/Win/TextStream/Buffer.cpp \
    $${BICYCLE_DIR}/Win/TextStream/TextStream.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/WinInet/WinInetException.cpp \
    $${BICYCLE_DIR}/Win/WinInet/HttpClient.cpp

LIBS += -lwininet

include(deployment.pri)
qtcAddDeployment()

