#-------------------------------------------------
#
# Project created by QtCreator 2015-08-19T09:06:08
#
#-------------------------------------------------

QT       += core gui network widgets multimedia multimediawidgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FPiVRx
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tcpclient.cpp

HEADERS  += mainwindow.h \
    tcpclient.h

FORMS    += mainwindow.ui

INCLUDEPATH += /Library/Frameworks/GStreamer.framework/Versions/1.0/Headers
/Library/Frameworks/GStreamer.framework/Versions/1.0/include
/Library/Frameworks/GStreamer.framework/Versions/1.0/lib
/Library/Frameworks/GStreamer.framework/Versions/1.0/Libraries
/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/glib-2.0
/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/glib-2.0/include
/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/gstreamer-1.0
/Library/Frameworks/GStreamer.framework/Versions/1.0/lib/gstreamer-1.0/include

LIBS += -L /Library/Frameworks/GStreamer.framework/Libraries -lgstreamer-1.0 -lglib-2.0
