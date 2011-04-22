REM -- Batch file to download and setup the Windows Dependencies --
@echo off

set RELEASE=nightlies
set VLC_VERSION=vlc-1.1.9
set LIBQXT_VERSION=libqxt-v0.6.1
set QT_VERSION=4.7.0

REM -- Check QTDIR Environment variable is set
if not defined QTDIR (
	echo Checking for Qt...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *   Environment variable QTDIR needs to be defined in order to build and *
 	echo *   package Inspire Browser                                              *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
)

REM -- Check to see if qmake exists
where qmake.exe > NUL
if ERRORLEVEL 1 (
	echo Checking for qmake executable...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *   QtSDK needs to be installed in order to install the dependencies     *
 	echo *   downloadDependencies.bat needs to be run from the Qt Command Line    *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
 ) else (
 	echo Checking for qmake executable... found.
)

REM -- Check the Qt version we have
for /f "delims=" %%a in ('qmake -query QT_VERSION') do @set CURRENT_QT_VERSION=%%a 
set CURRENT_QT_VERSION=%CURRENT_QT_VERSION:~0,-1%
if not %CURRENT_QT_VERSION% geq %QT_VERSION% (
	echo Checking Qt Version...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *   A Qt version of at least %QT_VERSION% is needed however you have            *
 	echo *   %CURRENT_QT_VERSION% installed                                                      *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
	goto End
) else (
	echo Checking Qt Version... OK!
)

REM -- Check to see if mingw32-make exists
where mingw32-make.exe > NUL
if ERRORLEVEL 1 (
	echo Checking for mingw32-make executable...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *   QtSDK needs to be installed in order to install the dependencies     *
 	echo *   downloadDependencies.bat needs to be run from the Qt Command Line    *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
 ) else (
 	echo Checking for mingw32-make executable... found.
)

:End
