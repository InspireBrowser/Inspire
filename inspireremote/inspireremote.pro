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

REVISION = $$system(svnversion)
VERSION = '$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}'
VERSTR = '\\"$${VERSION}.$${REVISION}\\"'

#if we are a packaged version then there is no svn revision
equals(REVISION, exported){
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

INCLUDEPATH += ../inspirebrowser/inspirelib
LIBS += -L../inspirebrowser/
LIBS += -linspirelib

# INSTALL INFORMATION
unix {
	executable.path = /usr/bin/
	executable.files = $$TARGET
	INSTALLS += executable
}
