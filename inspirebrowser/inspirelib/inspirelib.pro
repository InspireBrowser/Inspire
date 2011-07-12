#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = inspirelib
TEMPLATE = lib
CONFIG += warn_on silent qxt
QXT += core

SOURCES += GenericLayout.cpp \
    MainWindow.cpp \
    InspireWebView.cpp \
    JSBinding/IJSBinding.cpp \
    PluginManager.cpp

HEADERS  += MainWindow.h \
    GenericLayout.h \
    InspireWebView.h \
    JSBinding/IJSBinding.h \
    GenericPlugin.h \
    PluginManager.h

INCLUDEPATH += .

win32 {
	CONFIG(debug, release|debug) : DESTDIR = ../debug/
	CONFIG(release, release|debug) : DESTDIR = ../release/
} else {
	DESTDIR = ../
}
