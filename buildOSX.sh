#!/bin/bash

# Shell script to build all components

source packaging/environment.sh

# check for macdeployqt executable
echo -n Checking for macdeployqt...
MAC_DEPLOY_EXE=`which macdeployqt`
if [ "x${MAC_DEPLOY_EXE}" == "x" ]; then
	MAC_DEPLOY_EXE=`ls ~/QtSDK/Desktop/Qt/*/gcc/bin/macdeployqt 2> /dev/null | tail -n 1`
fi

if [ "x${MAC_DEPLOY_EXE}" == "x" ]; then
	echo ""
	echo "************************************************************"
	echo "*   Cannot find macdeplyqt executable. Can not continue    *"
	echo "************************************************************"

	exit 1
else
	echo "found."
fi

# Check the dependencies are downloaded and setup
cd dependencies/
./downloadDependenciesOSX.sh
if [ $? != 0 ]; then
	exit 1;
fi
cd ../../

# Compile the programs
echo "Creating Makefile..."
${QMAKE_EXE} -spec macx-g++ -config release
if [ $? != 0 ]; then
	exit 1;
fi

echo "Compiling Inspire..."
make
if [ $? != 0 ]; then
	exit 1;
fi

# Clear out any old dir and create the new one
rm -rf ${BUILD_DIRECTORY}
mkdir ${BUILD_DIRECTORY}

# Move the compiled app into the build dir
echo -n "Copying executable to ${BUILD_DIRECTORY} directory... "
mv inspirebrowser.app ${BUILD_DIRECTORY}/
if [ $? != 0 ]; then
	exit 1;
else
	echo "OK"
fi

# Now copy all the needed frameworks in
echo -n "Copying frameworks to ${BUILD_DIRECTORY} directory... "
mkdir -p ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/Frameworks
LIB_DIR=`${QMAKE_EXE} -query QT_INSTALL_LIBS`
for i in QtCore QtGui QtWebkit QtNetwork phonon; do
	cp -R ${LIB_DIR}/${i}.framework ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/Frameworks/
	if [ $? != 0 ]; then
		exit 1;
	fi
done

# Also copy in the Qxt frameworks
for i in QxtCore; do
	cp -R /Library/Frameworks/${i}.framework ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/Frameworks/
	if [ $? != 0 ]; then
		exit 1;
	fi
done

# Now remove all of the debug frameworks
rm -rf ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/Frameworks/Qt*.framework/Qt*debug
echo "OK"

echo -n "Updating references in frameworks... "
LIBRARIES=`otool -L ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/MacOS/inspirebrowser | grep Q | awk '{print $1}'`;
for i in ${LIBRARIES}; do
	FRAMEWORK=`basename $i`

	# Change where the dynamic linker will look for the library
	install_name_tool -id @executable_path/../Frameworks/${FRAMEWORK}.framework/Versions/Current/${FRAMEWORK} \
		${BUILD_DIRECTORY}/inspirebrowser.app/Contents/MacOS/inspirebrowser
	if [ $? != 0 ]; then
		exit 1;
	fi

	# Change where the application looks for the framework
	install_name_tool -change ${i} \
		@executable_path/../Frameworks/${FRAMEWORK}.framework/Versions/Current/${FRAMEWORK} \
		${BUILD_DIRECTORY}/inspirebrowser.app/Contents/MacOS/inspirebrowser
	if [ $? != 0 ]; then
		exit 1;
	fi

	# Now update the references for the frameworks dependencies
	FRAMEWORK_PATH="${BUILD_DIRECTORY}/inspirebrowser.app/Contents/Frameworks/${FRAMEWORK}.framework/Versions/Current/${FRAMEWORK}"
	FRAMEWORK_LIBRARIES=`otool -L ${FRAMEWORK_PATH} | grep Q | grep -v ${FRAMEWORK} | awk '{print $1}'`;
	for j in ${FRAMEWORK_LIBRARIES}; do
		INNER_FRAMEWORK=`basename $j`
		install_name_tool -change ${j} \
			@executable_path/../Frameworks/${INNER_FRAMEWORK}.framework/Versions/Current/${INNER_FRAMEWORK} \
			${FRAMEWORK_PATH}
		if [ $? != 0 ]; then
			exit 1;
		fi
	done
done
echo "OK"

echo -n "Copying VLC libraries to ${BUILD_DIRECTORY} directory... "
cp -R dependencies/osx/${VLC_VERSION}/Contents/MacOS/lib ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/MacOS/
if [ $? != 0 ]; then
	exit 1;
fi
cp -R dependencies/osx/${VLC_VERSION}/Contents/MacOS/plugins ${BUILD_DIRECTORY}/inspirebrowser.app/Contents/MacOS
if [ $? != 0 ]; then
	exit 1;
fi
echo "OK"

# Now create the dmg package
echo -n "Creating Inspire Browser DMG... "
${MAC_DEPLOY_EXE} ${BUILD_DIRECTORY}/inspirebrowser.app -no-plugins -dmg
if [ $? != 0 ]; then
	exit 1;
fi
mv ${BUILD_DIRECTORY}/inspirebrowser.dmg .
echo "OK"

echo -n "Tidying up.... "
rm -rf ${BUILD_DIRECTORY}
echo "OK"

echo ""
echo "****************************************************************"
echo "*                                                              *"
echo "*  Inspire Browser and tools successfully built and packaged   *"
echo "*                                                              *"
echo "****************************************************************"
echo ""
