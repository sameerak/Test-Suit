#-------------------------------------------------
#
# Project created by QtCreator 2013-11-22T06:29:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testnoobavssadtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testnoobavssadtest.cpp \
    NoobaVSSAD/speednode.cpp \
    NoobaVSSAD/readernode.cpp \
    NoobaVSSAD/filewriternode.cpp \
    NoobaVSSAD/featurenode.cpp \
    NoobaVSSAD/distancenode.cpp \
    NoobaVSSAD/distancechange.cpp \
    NoobaVSSAD/detecedevent.cpp \
    NoobaVSSAD/delaynode.cpp \
    NoobaVSSAD/abandonedobjectnode.cpp \
    testdatanode.cpp \
    speedmismatchnode.cpp \
    configuration.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OTHER_FILES += \
    NoobaVSSAD/README.md \
    NoobaVSSAD/NoobaVSSAD.pro

HEADERS += \
    NoobaVSSAD/speednode.h \
    NoobaVSSAD/readernode.h \
    NoobaVSSAD/filewriternode.h \
    NoobaVSSAD/featurenode.h \
    NoobaVSSAD/distancenode.h \
    NoobaVSSAD/distancechange.h \
    NoobaVSSAD/detectedevent.h \
    NoobaVSSAD/delaynode.h \
    NoobaVSSAD/abandonedobjectnode.h \
    testdatanode.h \
    speedmismatchnode.h \
    configuration.h
