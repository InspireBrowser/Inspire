#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = inspirelib
TEMPLATE = lib
CONFIG += warn_on silent qxt
QXT += core

SOURCES += GenericLayout.cpp \
    MainWindow.cpp \
    InspireWebView.cpp \
    PluginManager.cpp \
    RemoteCommand.cpp \
    OsUtils.cpp \
    CommandSystem.cpp

HEADERS  += MainWindow.h \
    GenericLayout.h \
    InspireWebView.h \
    GenericPlugin.h \
    PluginManager.h \
    RemoteCommand.h \
    OsUtils.h \
    CommandSystem.h \
    JavascriptBinding.h

INCLUDEPATH += .

win32 {
	CONFIG(debug, release|debug) : DESTDIR = ../debug/
	CONFIG(release, release|debug) : DESTDIR = ../release/
} else {
	DESTDIR = ../
}

# INSTALL INFORMATION
unix {
	executable.path = /usr/lib/
	executable.files = $$TARGET
	INSTALLS += executable
}
