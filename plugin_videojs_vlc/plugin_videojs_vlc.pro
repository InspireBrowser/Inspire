#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core webkit
CONFIG   += warn_on silent qxt
QXT      += core

TEMPLATE = lib
TARGET = $$qtLibraryTarget(videojs_vlc)
CONFIG += plugin

SOURCES += IVideoJSBinding.cpp \
    VideoWindow.cpp \
    VideoJSPlugin.cpp \
    VLC/QVlcPlayer.cpp

HEADERS += IVideoJSBinding.h \
    VideoWindow.h \
    VideoJSPlugin.h \
    VLC/QVlcPlayer.h

INCLUDEPATH += ../inspirelib/
LIBS += -linspirelib
LIBS += -L../
DESTDIR = ../plugins
	
# INSTALL INFORMATION
unix {
	plugin.path = /usr/lib/inspirebrowser/plugins/
	plugin.files = $$TARGET
	INSTALLS += plugin
}

#define the win32 VLC includes and libs
win32 {
	INCLUDEPATH += ../dependencies\\win32\\vlc-1.1.9\\sdk\\include
	LIBS += -L../dependencies\\win32\\vlc-1.1.9\\sdk\\lib
	LIBS += -lvlc
	
	CONFIG(debug, release|debug) {
		LIBS += -L../debug/
	}
	CONFIG(release, release|debug) {
		LIBS += -L../release/
	}
}

#define the unix VLC includes and libs
unix {
	LIBS += -lvlc
}

#define the OSX VLC includes and libs
macx {
	INCLUDEPATH += ../dependencies/osx/vlc-1.1.9/Contents/MacOS/include
	LIBS += -L../dependencies/osx/vlc-1.1.9/Contents/MacOS/lib
	LIBS += -lvlc
}
