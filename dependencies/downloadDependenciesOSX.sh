#!/bin/bash

source ../packaging/environment.sh

BASE=http://www.inspirebrowser.org/files/${RELEASE}/dependencies

VLC_ARCHIVE=${VLC_VERSION}.dmg
VLC_URL=${BASE}/osx/${VLC_ARCHIVE}

LIBQXT_ARCHIVE=${LIBQXT_VERSION}.tar.gz
LIBQXT_URL=${BASE}/${LIBQXT_ARCHIVE}

# Check VLC is extracted properly
if [ ! -e osx/${VLC_VERSION} ]; then
	# Check if the archive exists
	if [ ! -e osx/${VLC_ARCHIVE} ]; then
		# Nope then download it
		echo Check for VLC Archive... not found. Downloading!
		echo
		cd osx
		curl -OL ${VLC_URL}
		if [ $? != 0 ]; then
			echo ""
			echo "**************************** ERROR ***************************************"
			echo "*   Error downloading VLC Archive.                                       *"
			echo "**************************************************************************"
			echo ""
			exit 1
		else
			echo
			echo VLC Archive Downloaded
		fi
		cd ..
	else
		echo Check for VLC Archive... found.
	fi

	# Now extract the VLC archive
	hdiutil attach osx/${VLC_ARCHIVE}
	cp -r /Volumes/${VLC_VERSION}/VLC.app osx/${VLC_VERSION}
	umount /Volumes/${VLC_VERSION}
else
	echo Checking for VLC SDK... found.
fi

# Find the path the mkspecs are stored
SPECS_PATH=`${QMAKE_EXE} -query QMAKE_MKSPECS`

echo -n "Checking if libQXT is installed... "
if [ ! -e ${SPECS_PATH}/features/qxt.prf ]; then
	echo "not found. Building."
	
	# Check to see if libqxt source dir exists
	echo -n Checking for Lib QXT Source...
	if [ ! -e osx/libqxt ]; then
		echo "not found."
		
		echo -n "Check if the Lib QXT archive exists..."
		if [ ! -e osx/${LIBQXT_ARCHIVE} ]; then
			echo "not found. Downloading!"
			echo ""
			cd osx
			curl -OL ${LIBQXT_URL}
			if [ $? != 0 ]; then
				echo ""
				echo "**************************** ERROR ***************************************"
				echo "*   Error downloading libQXT Archive.                                    *"
				echo "**************************************************************************"
				echo ""
				exit 1;
			else
				echo ""
				echo libQXT Archive Downloaded
			fi
			cd ..
		else
			echo "found."
		fi
		
		echo "Extract libQXT Archive..."
		cd osx
		tar zxf ${LIBQXT_ARCHIVE}
		patch -p0 < qxtglobalshortcut_mac.cpp.diff
		cd ..
	else
		echo found.
	fi

	# Now it's downloaded and extracted, configure it and then install it
	echo Configuring and compiling libQXT...
	echo
	cd osx/libqxt
	./configure -release -qmake-bin ${QMAKE_EXE} -nomake berkeley -nomake designer -nomake gui -nomake network -nomake sql -nomake web -nomake zeroconf
	make
	sudo make install
	echo
	echo libQXT has been installed.
else
	echo found.
fi
