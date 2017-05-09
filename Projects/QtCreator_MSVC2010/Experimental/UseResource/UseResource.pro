TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = ./Dest

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

HEADERS += \
    $${BICYCLE_DIR}/Win/Experimental/Resource.h \
    $${BICYCLE_DIR}/Win/Fs/Path.h \
    $${BICYCLE_DIR}/Win/Process/Process.h

SOURCES += $${EXAMPLES_DIR}/Experimental/UseResource.cpp \
    $${BICYCLE_DIR}/Win/Common/Global.cpp \
    $${BICYCLE_DIR}/Win/Common/Exception.cpp \
    $${BICYCLE_DIR}/Win/Common/Event.cpp \
    $${BICYCLE_DIR}/Win/Common/WaitFor.cpp \
    $${BICYCLE_DIR}/Win/Fs/Path.cpp \
    $${BICYCLE_DIR}/Win/Experimental/Resource.cpp \
    $${BICYCLE_DIR}/Win/Process/Process.cpp \
    $${BICYCLE_DIR}/Win/Process/Pipe.cpp \
    $${BICYCLE_DIR}/Win/Process/Environment.cpp

LIBS+= User32.lib  Shlwapi.lib

include(deployment.pri)
qtcAddDeployment()


