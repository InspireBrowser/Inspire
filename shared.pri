#include the output of the configure script but provide
#default is it doesn't exist
!include ( conf.pri ) {
	PREFIX = /usr/local
	BINDIR = /usr/local/bin
	DATADIR = /usr/local/share
}

#define the organisation details
ORGANISATION_NAME='\\"InspireSoft\\"'
ORGANISATION_DOMAIN='\\"inspirebrowser.com\\"'
APPLICATION_NAME='\\"Inspire Browser\\"'

#define the version we are on
include ( version.pri )

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

