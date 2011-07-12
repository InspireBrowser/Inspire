#-------------------------------------------------
#
# Project created by QtCreator 2010-11-13T15:03:25
#
#-------------------------------------------------

QT       += core webkit network
CONFIG   += warn_on silent qxt
QXT      += core

TEMPLATE = lib
TARGET = $$qtLibraryTarget(systemjs)
CONFIG += plugin

SOURCES += SystemJSPlugin.cpp \
    ISystemJSBinding.cpp

HEADERS += SystemJSPlugin.h \
    ISystemJSBinding.h

INCLUDEPATH += ../../browser/
DESTDIR = ../../plugins
	
# INSTALL INFORMATION
unix {
	plugin.path = /usr/share/inspirebrowser/plugins/
	plugin.files = $$TARGET
	INSTALLS += plugin
}
