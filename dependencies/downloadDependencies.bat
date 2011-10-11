@echo off
@setlocal

REM -- Batch file to download and setup the Windows Dependencies --

if not defined RELEASE (
	call ../packaging/environment.bat
) else (
	set INNER_SCRIPT=true
)

set BASE=http://www.inspirebrowser.org/files/%RELEASE%/dependencies

set VLC_ARCHIVE=%VLC_VERSION%-win32.7z
set VLC_URL=%BASE%/win32/%VLC_ARCHIVE%

set LIBQXT_ARCHIVE=%LIBQXT_VERSION%.tar.gz
set LIBQXT_URL=%BASE%/%LIBQXT_ARCHIVE%

set UNRAR_EXE=%ProgramFiles%/WinRAR/WinRAR.exe

REM -- Check to see if winrar is installed for extracting the archives
if NOT EXIST "%UNRAR_EXE%" (
	echo Checking for unrar executable...
	echo **************************** ERROR ***************************************
	echo *   WinRAR needs to be installed in order to download the dependencies   *
	echo **************************************************************************
	ECHO 1 | CHOICE /C:1234567890 /N > NUL
	goto End
) else (
	echo Checking for unrar executable... found.
)

REM -- See if VLC SDK is extracted
if NOT EXIST win32\%VLC_VERSION% (
	REM -- Check if the archive exists
	if NOT EXIST win32\%VLC_ARCHIVE% (
		REM -- Nope then download it
		echo Check for VLC Archive... not found. Downloading!
		echo.
		win32\wget.exe -O win32\%VLC_ARCHIVE% %VLC_URL%
		if ERRORLEVEL 1 (
			echo.
			echo **************************** ERROR ***************************************
			echo *   Error downloading VLC Archive.                                    *
			echo **************************************************************************
			echo.
			ECHO 1 | CHOICE /C:1234567890 /N > NUL
			goto End
		) else (
			echo.
			echo VLC Archive Downloaded
		)
	) else (
		echo Check for VLC Archive... found.
	)

	REM -- Now extract the VLC archive
	echo Extract VLC Archive...
	mkdir win32\%VLC_VERSION%
	"%UNRAR_EXE%" X win32\%VLC_ARCHIVE% win32\
) else (
	echo Checking for VLC SDK... found.
)

for /f "delims=" %%a in ('where qmake') do @set QMAKE_PATH=%%a 

for %%F in (%QMAKE_PATH%) do set SIMULATOR_QMAKE_PATH=%%~dpF
set SIMULATOR_QMAKE_PATH=%SIMULATOR_QMAKE_PATH%..\..\..\..\..\Simulator\Qt\mingw\bin\qmake.exe
for %%F in (%SIMULATOR_QMAKE_PATH%) do set SIMULATOR_QMAKE_PATH=%%~fF

call:setupLibQxt %QMAKE_PATH%
IF EXIST %SIMULATOR_QMAKE_PATH% (
	call:setupLibQxt %SIMULATOR_QMAKE_PATH%
)

echo.
echo *********************************************************
echo *                                                       *
echo *  Dependencies downloaded and installed successfully.  *
echo *                                                       *
echo *********************************************************
echo.

:End
if not defined INNER_SCRIPT pause
GOTO:EOF

:setupLibQxt
echo Checking for libQxt with qmake executable %~1
REM -- Find the path the mkspecs are stored
for /f "delims=" %%a in ('%~1 -query QMAKE_MKSPECS') do @set SPECS_PATH=%%a 

REM -- Take the last character away as it's a space or a tab or something
set SPECS_PATH=%SPECS_PATH:~0,-1%
IF NOT EXIST %SPECS_PATH%\features\qxt.prf (
	echo Checking if libQXT is installed... not found. Building.
	
	REM -- Check to see if libqxt source dir exists
	if NOT EXIST win32\libqxt (
		echo Checking for Lib QXT Source...
		REM -- Check if the archive exists
		if NOT EXIST win32\%LIBQXT_ARCHIVE% (
			REM -- Nope then download it
			echo Check for libQXT Archive... not found. Downloading!
			echo.
			win32\wget.exe -O win32\%LIBQXT_ARCHIVE% %LIBQXT_URL%
			if ERRORLEVEL 1 (
				echo.
				echo **************************** ERROR ***************************************
				echo *   Error downloading libQXT Archive.                                    *
				echo **************************************************************************
				echo.
				ECHO 1 | CHOICE /C:1234567890 /N > NUL
				goto End
			) else (
				echo.
				echo libQXT Archive Downloaded
			)
		) else (
			echo Check for libQXT Archive... found.
		)
		
		REM -- Now extract the libQXT archive
		echo Extract libQXT Archive...
		"%UNRAR_EXE%" X win32\%LIBQXT_ARCHIVE% win32\
	) else (
		echo Checking for Lib QXT Source... found.
	)

	REM -- Now it's downloaded and extracted, configure it and then install it
	echo Configuring libQXT...
	echo.
	cd win32\libqxt
	IF EXIST Makefile (
		mingw32-make distclean
	)
	call configure.bat -qmake-bin %~1 -debug_and_release -nomake berkeley -nomake designer -nomake gui -nomake network -nomake sql -nomake web -nomake zeroconf
	
	echo Compiling libQXT...
	echo.
	mingw32-make
	mingw32-make install
	cd ..\..
	echo.
	echo libQXT has been installed.
) else (
	echo Checking if libQXT is installed... found.
)
GOTO:EOF