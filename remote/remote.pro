#-------------------------------------------------
#
# Project created by QtCreator 2010-11-21T12:22:37
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = inspireremote
TEMPLATE = app
CONFIG += console 
CONFIG += warn_on silent
CONFIG -= app_bundle

#define the organisation details
ORGANISATION_NAME='\\"InspireSoft\\"'
ORGANISATION_DOMAIN='\\"inspirebrowser.com\\"'
APPLICATION_NAME='\\"Inspire Browser\\"'

#define the version we are on
VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 1

VERSION = '$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}'

# if we are creating nightlies append the current date to the version
CONFIG(nightlies) {
	win32 {
		REVISION = $$system(%date:~10%%date:~4,2%%date:~7,2%)
	}
	!win32 {
		REVISION = $$system(date +%Y%m%d)
	}
	VERSTR = '\\"$${VERSION}.$${REVISION}\\"'
}
!CONFIG(nightlies) {
        VERSTR = '\\"$${VERSION}\\"'
}

#add the organsiation details and version info as DEFINES so they can be used by the program
DEFINES += VERSION=\"$${VERSTR}\"
DEFINES += ORGANISATION_NAME=\"$${ORGANISATION_NAME}\"
DEFINES += ORGANISATION_DOMAIN=\"$${ORGANISATION_DOMAIN}\"
DEFINES += APPLICATION_NAME=\"$${APPLICATION_NAME}\"

# now add the dash to the version so make dist creates the dir correctly
VERSION = '-$${VERSION}'

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
LIBS += -linspirelib

# INSTALL INFORMATION
unix {
	target.path = /usr/bin/
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
