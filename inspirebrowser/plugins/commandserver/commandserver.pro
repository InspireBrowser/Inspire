#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core webkit network
CONFIG   += warn_on silent qxt
QXT      += core

TEMPLATE = lib
TARGET = $$qtLibraryTarget(commandserver)
CONFIG += plugin

SOURCES += CommandServer.cpp \
    CommandSocket.cpp \
    RemoteCommand.cpp \
    CommandServerPlugin.cpp

HEADERS += CommandServer.h \
    CommandSocket.h \
    RemoteCommand.h \
    CommandServerPlugin.h

INCLUDEPATH += ../../browser/
DESTDIR = ../../plugins
	
# INSTALL INFORMATION
unix {
	plugin.path = /usr/share/inspirebrowser/plugins/
	plugin.files = $$TARGET
	INSTALLS += plugin
}