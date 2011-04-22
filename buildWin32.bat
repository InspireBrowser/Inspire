@echo off
@setlocal

REM -- Batch file to build all components

REM -- Include environment settings
cd inspirebrowser/packaging/
call environment.bat
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)
cd ../../

where candle.exe > NUL
if ERRORLEVEL 1 (
	echo Checking for wix executable...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *  In order to create the InspireBrowser package WiX 3.5 or later needs  *
	echo *  to be installed and the executables candle.exe and light.exe need to  *
	echo *  be in the PATH                                                        *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
 ) else (
 	echo Checking for qmake executable... found.
)

REM -- Check the dependencies are downloaded and setup
cd inspirebrowser/dependencies/
call downloadDependencies.bat
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)
cd ../../

REM -- Compile the programs
echo Creating Makefile...
qmake
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)
echo Compiling Inspire...
mingw32-make release
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)

REM -- Remove an old packaging dir if it's there
if exist packaging (
	rmdir /Q /S packaging
)

REM -- Create the packaging dir and copy the created executables in
mkdir packaging
xcopy /Y inspirebrowser\release\inspirebrowser.exe packaging
xcopy /Y inspireremote\release\inspireremote.exe packaging
xcopy /Y inspirebrowser\packaging\InspireBrowser.wxs packaging
xcopy /Y inspirebrowser\packaging\InspireLicense.rtf packaging

REM -- Copy in the VLC dependencies
xcopy /Y inspirebrowser\dependencies\win32\%VLC_VERSION%\libvlc.dll packaging
xcopy /Y inspirebrowser\dependencies\win32\%VLC_VERSION%\libvlccore.dll packaging
mkdir packaging\plugins
xcopy /S /Y inspirebrowser\dependencies\win32\%VLC_VERSION%\plugins packaging\plugins

REM -- Copy in the Ming dependencies
xcopy /Y %QTDIR%\bin\libgcc_s_dw2-1.dll packaging
xcopy /Y %QTDIR%\bin\mingwm10.dll packaging

REM -- Copy in the Qt dependencies
xcopy /Y %QTDIR%\bin\QtCore4.dll packaging
xcopy /Y %QTDIR%\bin\QtGui4.dll packaging
xcopy /Y %QTDIR%\bin\QtNetwork4.dll packaging
xcopy /Y %QTDIR%\bin\QtWebKit4.dll packaging
xcopy /Y %QTDIR%\bin\phonon4.dll packaging

REM -- Now use WiX to create the install package
cd packaging
candle.exe InspireBrowser.wxs
if ERRORLEVEL 1 (
	echo Processing WiX XML File...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *                 Processing the WiX XML File failed.                    *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
) else (
	echo Processing WiX XML File... OK!
)

light.exe -ext WixUIExtension InspireBrowser.wixobj
if ERRORLEVEL 1 (
	echo Creating MSI Executable...
	echo.
 	echo **************************** ERROR ***************************************
 	echo *              Creation of the MSI Executable failed.                    *
 	echo **************************************************************************
	echo.
	echo 1 | CHOICE /C:1234567890 /N > NUL
 	goto End
)

REM -- move the created MSI up a level and tidy up
move inspirebrowser.msi ../
cd ../
rmdir /Q /S packaging

echo.
echo ****************************************************************
echo *                                                              *
echo *  Inspire Browser and tools successfully build and packaged   *
echo *                                                              *
echo ****************************************************************
echo.

:End
pause