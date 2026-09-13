@echo off
rem Build dpkget.exe / dpkput.exe / dpkraw.exe against the client's own
rem VirtualFileSystem, so archive decompression matches the game exactly.
rem
rem All paths are derived from this script's location (%~dp0), so the repo can
rem live anywhere. Visual Studio is located with vswhere rather than assumed.
setlocal

set "HERE=%~dp0"
if "%HERE:~-1%"=="\" set "HERE=%HERE:~0,-1%"
for %%I in ("%HERE%\..\..") do set "ROOT=%%~fI"

echo repo root : %ROOT%

rem --- locate Visual Studio -------------------------------------------------
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" set "VSWHERE=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" (
    echo ERROR: vswhere.exe not found -- is Visual Studio installed?
    exit /b 1
)

set "VSPATH="
for /f "usebackq tokens=*" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSPATH=%%I"
if "%VSPATH%"=="" (
    echo ERROR: no Visual Studio install with the C++ toolset.
    exit /b 1
)

set "VCVARS=%VSPATH%\VC\Auxiliary\Build\vcvars32.bat"
if not exist "%VCVARS%" (
    echo ERROR: vcvars32.bat not found under "%VSPATH%".
    exit /b 1
)
call "%VCVARS%" >nul

rem --- build ---------------------------------------------------------------
rem x86 to match the client (see the x86-only note in the repo docs).
set "INC=/I"%ROOT%\VirtualFileSystem" /I"%ROOT%\VirtualFileSystem\nFS" /I"%ROOT%\MZLib" /I"%ROOT%\SpriteLib""
set "LIBS="%ROOT%\Release\VirtualFileSystem.lib" "%ROOT%\Release\MZLib.lib""
set "OPTS=/nologo /MT /EHsc /D_CRT_SECURE_NO_WARNINGS /DWIN32 /D_WINDOWS"

if not exist "%ROOT%\Release\VirtualFileSystem.lib" (
    echo ERROR: %ROOT%\Release\VirtualFileSystem.lib is missing.
    echo        Build the VirtualFileSystem project first.
    exit /b 1
)

for %%T in (dpkget dpkput dpkraw) do (
    echo.
    echo --- %%T ---
    cl %OPTS% %INC% /Fo:"%HERE%\obj_%%T_" /Fe:"%HERE%\%%T.exe" "%HERE%\%%T.cpp" /link %LIBS%
    if errorlevel 1 (
        echo BUILD FAILED: %%T
        exit /b 1
    )
)

del /q "%HERE%\obj_*" 2>nul
echo.
echo built: %HERE%\dpkget.exe
echo        %HERE%\dpkput.exe
echo        %HERE%\dpkraw.exe
endlocal
