#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core gui webkit network

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

REVISION = $$system(svnversion)
VERSION = '$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}'
VERSTR = '\\"$${VERSION}.$${REVISION}\\"'

#if we are a packaged version then there is no svn revision
equals(REVISION, exported) | equals(REVISION, ''){
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
    JSBinding/ISystemJSBinding.cpp \
    JSBinding/IBrowserJSBinding.cpp \
    JSBinding/IVideoJSBinding.cpp \
    JSBinding/IJSBinding.cpp \
    JSBinding/VideoWindow.cpp \
    VLC/QVlcPlayer.cpp \
    RemoteCommand.cpp \
    CommandServer.cpp \
    CommandSocket.cpp

HEADERS  += MainWindow.h \
    GenericLayout.h \
    InspireWebView.h \
    JSBinding/ISystemJSBinding.h \
    JSBinding/IBrowserJSBinding.h \
    JSBinding/IVideoJSBinding.h \
    JSBinding/IJSBinding.h \
    JSBinding/VideoWindow.h \
    VLC/QVlcPlayer.h \
    RemoteCommand.h \
    CommandServer.h \
    CommandSocket.h

RESOURCES += \
    InspireBrowser.qrc

INCLUDEPATH += .
	
#define the win32 VLC includes and libs
win32 {
	INCLUDEPATH += dependencies\\win32\\vlc-1.1.9\\sdk\\include
	LIBS += -Ldependencies\\win32\\vlc-1.1.9\\sdk\\lib
	LIBS += -lvlc
}

#define the unix VLC includes and libs
unix {
	LIBS += -lvlc
}

#define the OSX VLC includes and libs
macx {
	INCLUDEPATH += dependencies/osx/vlc-1.1.9/Contents/MacOS/include
	LIBS += -Ldependencies/osx/vlc-1.1.9/Contents/MacOS/lib
	LIBS += -lvlc
}

# INSTALL INFORMATION
unix {
	executable.path = /usr/bin/
	executable.files = $$TARGET
	INSTALLS += executable
}
