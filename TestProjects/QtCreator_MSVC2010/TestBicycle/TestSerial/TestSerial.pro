TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

EXAMPLES_DIR = ../../../../Examples
BICYCLE_DIR =  ../../../../Bicycle

INCLUDEPATH+= $${BICYCLE_DIR}

SOURCES += $${EXAMPLES_DIR}/main_Serial.cpp \
    $${BICYCLE_DIR}/Serial/SerialPort.cpp \
    $${BICYCLE_DIR}/Serial/SerialPortInfo.cpp \
    $${BICYCLE_DIR}/Buffer.cpp \
    $${BICYCLE_DIR}/Global.cpp \
    $${BICYCLE_DIR}/IODevice.cpp \
    $${BICYCLE_DIR}/IOStream.cpp \
    $${BICYCLE_DIR}/NonCopyable.cpp \
    $${BICYCLE_DIR}/SystemException.cpp \
    $${BICYCLE_DIR}/Sync/AtomicCounter.cpp \
    $${BICYCLE_DIR}/Console.cpp

HEADERS += \
    $${BICYCLE_DIR}/Serial/SerialPort.h \
    $${BICYCLE_DIR}/Serial/SerialPortInfo.h \
    $${BICYCLE_DIR}/Buffer.h \
    $${BICYCLE_DIR}/Global.h \
    $${BICYCLE_DIR}/IODevice.h \
    $${BICYCLE_DIR}/IOStream.h \
    $${BICYCLE_DIR}/NonCopyable.h \
    $${BICYCLE_DIR}/SystemException.h \
    $${BICYCLE_DIR}/Sync/AtomicCounter.h \
    $${BICYCLE_DIR}/Algorithm/AsLiteral.h \
    $${BICYCLE_DIR}/Algorithm/Begin.h \
    $${BICYCLE_DIR}/Algorithm/End.h \
    $${BICYCLE_DIR}/Algorithm/IsAnyOf.h \
    $${BICYCLE_DIR}/Algorithm/IteratorRange.h \
    $${BICYCLE_DIR}/Algorithm/RangeConstIterator.h \
    $${BICYCLE_DIR}/Algorithm/RangeIterator.h \
    $${BICYCLE_DIR}/Algorithm/RangeMutableIterator.h \
    $${BICYCLE_DIR}/Algorithm/Split.h \
    $${BICYCLE_DIR}/Algorithm/Trim.h \
    $${BICYCLE_DIR}/Algorithm/Utils.h \
    $${BICYCLE_DIR}/Console.h

LIBS += User32.lib Setupapi.lib Advapi32.lib

include(deployment.pri)
qtcAddDeployment()



