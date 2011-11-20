#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core webkit network

TARGET = $$qtLibraryTarget(systemjs)
TEMPLATE = lib
CONFIG += warn_on silent qxt
CONFIG += plugin
QXT += core

include( ../shared.pri )

SOURCES += SystemJSPlugin.cpp \
    ISystemJSBinding.cpp

HEADERS += SystemJSPlugin.h \
    ISystemJSBinding.h

INCLUDEPATH += ../inspirelib
LIBS += -linspirelib

# INSTALL INFORMATION
unix {
	target.path = $$PLUGINDIR
	INSTALLS += target
}

DESTDIR = ../plugins
win32 {
	CONFIG(debug, release|debug) {
		LIBS += -L../debug/
	}
	CONFIG(release, release|debug) {
		LIBS += -L../release/
	}
} else {
	LIBS += -L../
}
