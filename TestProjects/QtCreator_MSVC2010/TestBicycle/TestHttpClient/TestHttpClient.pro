TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += $${BICYCLE_DIR}/Http/HttpClient.h \
           $${BICYCLE_DIR}/Http/WinInetException.h \
    $${BICYCLE_DIR}/Global.h \
    $${BICYCLE_DIR}/IODevice.h \
    $${BICYCLE_DIR}/NonCopyable.h \
    $${BICYCLE_DIR}/IOStream.h \
    $${BICYCLE_DIR}/Buffer.h

SOURCES += $${EXAMPLES_DIR}/main_TestHttpClient.cpp \
    $${BICYCLE_DIR}/Http/HttpClient.cpp \
    $${BICYCLE_DIR}/Http/WinInetException.cpp \
    $${BICYCLE_DIR}/Global.cpp \
    $${BICYCLE_DIR}/IOStream.cpp \
    $${BICYCLE_DIR}/Buffer.cpp

include(deployment.pri)
qtcAddDeployment()

LIBS+= -lwininet
