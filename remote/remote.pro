#-------------------------------------------------
#
# Project created by QtCreator 2010-11-21T12:22:37
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = inspireremote
TEMPLATE = app
CONFIG += warn_on silent qxt console 
CONFIG -= app_bundle
QXT += core

include( ../shared.pri )

#setup the files that we want added to the distribution package
DISTFILES += license
DISTFILES += packaging/*

SOURCES += main.cpp \
    CommandSendingSocket.cpp \
    CommandSender.cpp

HEADERS += \
    CommandSendingSocket.h \
    CommandSender.h

INCLUDEPATH += ../inspirelib
LIBS += -L../
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
}
