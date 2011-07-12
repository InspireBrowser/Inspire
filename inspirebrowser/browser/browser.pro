#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = inspirebrowser
TEMPLATE = app
CONFIG += warn_on silent qxt
QXT += core

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
DISTFILES += license images/*
DISTFILES += packaging/*

SOURCES += main.cpp\
    GenericLayout.cpp \
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

RESOURCES += \
    InspireBrowser.qrc

INCLUDEPATH += .

# INSTALL INFORMATION
unix {
	executable.path = /usr/bin/
	executable.files = $$TARGET
	INSTALLS += executable
}

win32 {
	CONFIG(debug, release|debug) : DESTDIR = ../debug/
	CONFIG(release, release|debug) : DESTDIR = ../release/
} else {
	DESTDIR = ../
}
