@echo off
@setlocal

REM -- Batch file to build all components

REM -- Include environment settings
cd resources/
call environment.bat
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)
cd ../

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
cd dependencies/
call downloadDependencies.bat
if ERRORLEVEL 1 (
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
)
cd ../

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

REM -- Remove an old %BUILD_DIRECTORY% dir if it's there
if exist %BUILD_DIRECTORY% (
	rmdir /Q /S %BUILD_DIRECTORY%
)

REM -- Create the %BUILD_DIRECTORY% dir and copy the created executables in
mkdir %BUILD_DIRECTORY%
xcopy /Y release\inspirebrowser.exe %BUILD_DIRECTORY%
xcopy /Y release\inspirelib.dll %BUILD_DIRECTORY%
xcopy /Y release\inspireremote.exe %BUILD_DIRECTORY%
xcopy /Y resources\InspireBrowser.wxs %BUILD_DIRECTORY%
xcopy /Y resources\InspireLicense.rtf %BUILD_DIRECTORY%

REM -- Copy in the plugins
mkdir %BUILD_DIRECTORY%\plugins
xcopy /Y plugins\systemjs.dll %BUILD_DIRECTORY%\plugins
xcopy /Y plugins\browserjs.dll %BUILD_DIRECTORY%\plugins
xcopy /Y plugins\commandserver.dll %BUILD_DIRECTORY%\plugins

REM -- Copy in the Ming dependencies
xcopy /Y %QTDIR%\bin\libgcc_s_dw2-1.dll %BUILD_DIRECTORY%
xcopy /Y %QTDIR%\bin\mingwm10.dll %BUILD_DIRECTORY%

REM -- Copy in the Qt dependencies
xcopy /Y %QTDIR%\bin\QtCore4.dll %BUILD_DIRECTORY%
xcopy /Y %QTDIR%\bin\QtGui4.dll %BUILD_DIRECTORY%
xcopy /Y %QTDIR%\bin\QtNetwork4.dll %BUILD_DIRECTORY%
xcopy /Y %QTDIR%\bin\QtWebKit4.dll %BUILD_DIRECTORY%
xcopy /Y %QTDIR%\bin\phonon4.dll %BUILD_DIRECTORY%

REM -- Find the path the mkspecs are stored
for /f "delims=" %%a in ('qmake -query QMAKE_MKSPECS') do @set SPECS_PATH=%%a 
REM -- Take the last character away as it's a space or a tab or something
set SPECS_PATH=%SPECS_PATH:~0,-1%
REM -- Now extract the QXT Variables and merge them into the global namespace
for /f "delims=" %%x in (%SPECS_PATH%\features\qxtvars.prf) do (
	set x=%x:~1,-1%
	for /f "tokens=1,2,3" %%a in ("%%x") do (
		set %%a=%%c
	)
)

REM -- Copy in the Qxt dependencies
set QXT_INSTALL_LIBS=%QXT_INSTALL_LIBS:/=\%
xcopy /Y %QXT_INSTALL_LIBS%\QxtCore.dll %BUILD_DIRECTORY%

REM -- Now use WiX to create the install package
cd %BUILD_DIRECTORY%
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
REM rmdir /Q /S %BUILD_DIRECTORY%

echo.
echo ****************************************************************
echo *                                                              *
echo *  Inspire Browser and tools successfully built and packaged   *
echo *                                                              *
echo ****************************************************************
echo.

:End
pause
