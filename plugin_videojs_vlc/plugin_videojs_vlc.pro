#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core webkit network

TARGET = $$qtLibraryTarget(videojs_vlc)
TEMPLATE = lib
CONFIG += warn_on silent qxt
CONFIG += plugin
QXT += core

include( ../shared.pri )

SOURCES += IVideoJSBinding.cpp \
    VideoWindow.cpp \
    VideoJSPlugin.cpp \
    VLC/QVlcPlayer.cpp

HEADERS += IVideoJSBinding.h \
    VideoWindow.h \
    VideoJSPlugin.h \
    VLC/QVlcPlayer.h

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

#define the win32 VLC includes and libs
win32 {
	INCLUDEPATH += ../dependencies\\win32\\vlc-1.1.9\\sdk\\include
	LIBS += -L../dependencies\\win32\\vlc-1.1.9\\sdk\\lib
	LIBS += -lvlc
	
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
