#include the output of the configure script but provide
#default is it doesn't exist
!include ( conf.pri ) {
	PREFIX="/usr/local"
	BINDIR="$${PREFIX}/bin"
	DATADIR="$${PREFIX}/share"
	LIBDIR="$${PREFIX}/lib"
}
PLUGINDIR="$${LIBDIR}/inspirebrowser/plugins"

#define the organisation details
ORGANISATION_NAME='\\"InspireSoft\\"'
ORGANISATION_DOMAIN='\\"inspirebrowser.com\\"'
APPLICATION_NAME='\\"Inspire Browser\\"'

#define the version we are on
include ( version.pri )

VERSION = '$${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}'
VERSTR = '$${VERSION}'

isEqual(REVISION, "git") {
	REVISION = $$system(git rev-parse --verify HEAD)
}
!isEqual(REVISION, "") {
	VERSTR = '\\"$${VERSION}-git-$${REVISION}\\"'
}

#add the organsiation details and version info as DEFINES so they can be used by the program
DEFINES += VERSION=\"$${VERSTR}\"
DEFINES += ORGANISATION_NAME=\"$${ORGANISATION_NAME}\"
DEFINES += ORGANISATION_DOMAIN=\"$${ORGANISATION_DOMAIN}\"
DEFINES += APPLICATION_NAME=\"$${APPLICATION_NAME}\"

#now add the PREFIX, BINDIR and DATADIR defines so we can find plugins and shared files
DEFINES += PREFIX=\\\"$${PREFIX}\\\"
DEFINES += BINDIR=\\\"$${BINDIR}\\\"
DEFINES += DATADIR=\\\"$${DATADIR}\\\"
DEFINES += LIBDIR=\\\"$${LIBDIR}\\\"
DEFINES += PLUGINDIR=\\\"$${PLUGINDIR}\\\"
#DEFINES += FOO=\\\"$${FOO}\\\"
