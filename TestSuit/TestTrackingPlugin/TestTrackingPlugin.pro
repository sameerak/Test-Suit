#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T15:53:19
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testtrackingplugintest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testtrackingplugintest.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/BlobTrackingNode.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvtrack.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvlabel.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvcontour.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvcolor.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvblob.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvaux.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvtrack.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvlabel.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvcontour.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvcolor.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvblob.cpp \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvaux.cpp \
    nooba-plugin-tracking/TrackingPlugin/trackingplugin.cpp \
    nooba-plugin-tracking/TrackingPlugin/filewriternode.cpp \
    nooba-plugin-tracking/TrackingPlugin/featurenode.cpp \
    nooba-plugin-tracking/TrackingPlugin/detecedevent.cpp \
    package_tracking/cvblob/cvtrack.cpp \
    package_tracking/cvblob/cvlabel.cpp \
    package_tracking/cvblob/cvcontour.cpp \
    package_tracking/cvblob/cvcolor.cpp \
    package_tracking/cvblob/cvblob.cpp \
    package_tracking/cvblob/cvaux.cpp \
    package_tracking/BlobTrackingNode.cpp \
    package_tracking/cvblob/10.3/cvtrack.cpp \
    package_tracking/cvblob/10.3/cvlabel.cpp \
    package_tracking/cvblob/10.3/cvcontour.cpp \
    package_tracking/cvblob/10.3/cvcolor.cpp \
    package_tracking/cvblob/10.3/cvblob.cpp \
    package_tracking/cvblob/10.3/cvaux.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

OTHER_FILES +=

HEADERS += \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/BlobTrackingNode.h \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/cvblob.h \
    nooba-plugin-tracking/TrackingPlugin/package_tracking/cvblob/10.3/cvblob.h \
    nooba-plugin-tracking/TrackingPlugin/filewriternode.h \
    nooba-plugin-tracking/TrackingPlugin/featurenode.h \
    nooba-plugin-tracking/TrackingPlugin/detectedevent.h \
    package_tracking/cvblob/cvblob.h \
    package_tracking/BlobTrackingNode.h \
    package_tracking/cvblob/10.3/cvblob.h
