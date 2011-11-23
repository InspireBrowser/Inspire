#!/bin/bash

source version.pri

VERSION="${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"

#if it's a git release convert the revision into the git hash
if [ $REVISION == "git" ]; then
	REVISION=`git rev-parse --verify HEAD`
fi

#if we're doing a proper release clear the revision flag
if [ "x$1" == "x-r" ]; then
	REVISION=""
fi

#if it's a git release append the hash to the version string
if [ $REVISION != "" ]; then
	VERSION="${VERSION}-git"
fi

PACKAGE_NAME="inspire-${VERSION}"

rm -rf ${PACKAGE_NAME}
mkdir ${PACKAGE_NAME}

FILES=" \
	browser/ \
	remote/ \
	inspirelib/ \
	plugin_* \
	resources/ \
	license \
	README \
	inspire.pro \
	shared.pri \
	configure"

cp -ar ${FILES} ${PACKAGE_NAME}

echo "VERSION_MAJOR=${VERSION_MAJOR}" > ${PACKAGE_NAME}/version.pri
echo "VERSION_MINOR=${VERSION_MINOR}" >> ${PACKAGE_NAME}/version.pri
echo "VERSION_PATCH=${VERSION_PATCH}" >> ${PACKAGE_NAME}/version.pri
echo "REVISION=${REVISION}" >> ${PACKAGE_NAME}/version.pri

tar zcf ${PACKAGE_NAME}.tar.gz ${PACKAGE_NAME}
rm -rf ${PACKAGE_NAME}
