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
    CommandServerPlugin.cpp

HEADERS += CommandServer.h \
    CommandSocket.h \
    CommandServerPlugin.h

INCLUDEPATH += ../inspirelib/
LIBS += -linspirelib
LIBS += -L../
DESTDIR = ../plugins
	
# INSTALL INFORMATION
unix {
	target.path = /usr/lib/inspirebrowser/plugins/
	INSTALLS += target
}

win32 {
	CONFIG(debug, release|debug) {
		LIBS += -L../debug/
	}
	CONFIG(release, release|debug) {
		LIBS += -L../release/
	}
}
