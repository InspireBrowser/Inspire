#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = inspirebrowser
TEMPLATE = app
CONFIG += warn_on silent qxt
CONFIG -= app_bundle
QXT += core

include( ../shared.pri )

#setup the files that we want added to the distribution package
DISTFILES += license images/*
DISTFILES += packaging/*

SOURCES += main.cpp

RESOURCES += \
    InspireBrowser.qrc

INCLUDEPATH += ../inspirelib
LIBS += -linspire

# INSTALL INFORMATION
unix {
	target.path = $$BINDIR
	INSTALLS += target
}

win32 {
	CONFIG(debug, release|debug) {
		DESTDIR = ../debug/
		LIBS += -L../debug/
	}
	CONFIG(release, release|debug) {
		DESTDIR = ../release/
		LIBS += -L../release/
	}
} else {
	DESTDIR = ../
	LIBS += -L../
}
