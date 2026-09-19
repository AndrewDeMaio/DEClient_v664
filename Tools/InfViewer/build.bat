@echo off
rem Build InfViewer.exe with the VS C++ toolset (no solution needed).
rem Paths derive from this script's location. Visual Studio is located by
rem scanning the standard install folders for vcvars32.bat.
setlocal

set "HERE=%~dp0"
if "%HERE:~-1%"=="\" set "HERE=%HERE:~0,-1%"

set "VCVARS="
for %%Y in (2022 2019 2017) do (
    for %%E in (Enterprise Professional Community BuildTools Preview) do (
        if not defined VCVARS if exist "%ProgramFiles%\Microsoft Visual Studio\%%Y\%%E\VC\Auxiliary\Build\vcvars32.bat" set "VCVARS=%ProgramFiles%\Microsoft Visual Studio\%%Y\%%E\VC\Auxiliary\Build\vcvars32.bat"
        if not defined VCVARS if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\%%Y\%%E\VC\Auxiliary\Build\vcvars32.bat" set "VCVARS=%ProgramFiles(x86)%\Microsoft Visual Studio\%%Y\%%E\VC\Auxiliary\Build\vcvars32.bat"
    )
)
if not defined VCVARS (
    echo ERROR: no Visual Studio C++ toolset found ^(vcvars32.bat^).
    exit /b 1
)
echo using %VCVARS%
call "%VCVARS%" >nul

if not exist "%HERE%\obj" mkdir "%HERE%\obj"
set "OPTS=/nologo /std:c++17 /O2 /MT /EHsc /W3 /DUNICODE /D_UNICODE /DWIN32 /D_WINDOWS /D_CRT_SECURE_NO_WARNINGS"

cl %OPTS% /Fo"%HERE%\obj\\" /Fe"%HERE%\InfViewer.exe" "%HERE%\main.cpp" "%HERE%\InfParser.cpp" "%HERE%\InfEdit.cpp" /link /SUBSYSTEM:WINDOWS comctl32.lib comdlg32.lib shell32.lib user32.lib gdi32.lib
if errorlevel 1 (
    echo BUILD FAILED
    exit /b 1
)

echo.
echo built: %HERE%\InfViewer.exe
endlocal
