RELEASE=nightlies
VLC_VERSION=vlc-1.1.9
LIBQXT_VERSION=libqxt-v0.6.1
QT_VERSION=4.7.0
BUILD_DIRECTORY=build

# check for qmake executable
echo -n Checking for qmake...
QMAKE_EXE=`which qmake`
if [ "x${QMAKE_EXE}" == "x" ]; then
	QMAKE_EXE=`ls ~/QtSDK/Desktop/Qt/*/gcc/bin/qmake 2> /dev/null | tail -n 1`
fi

if [ "x${QMAKE_EXE}" == "x" ]; then
	echo ""
	echo "*******************************************************"
	echo "*   Cannot find qmake executable. Can not continue    *"
	echo "*******************************************************"

	exit 1
else
	echo "found."
fi

CURRENT_QT_VERSION=`${QMAKE_EXE} -query QT_VERSION`

echo -n Checking for make...
MAKE_EXE=`which make`
if [ "x${MAKE_EXE}" == "x" ]; then
	echo "******************************************************"
	echo "*   Cannot find make executable. Can not continue    *"
	echo "******************************************************"

	exit 1
else
	echo "found."
fi
