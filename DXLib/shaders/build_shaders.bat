@echo off
rem Compiles present.hlsl into C headers with the shader bytecode so the
rem client needs no D3DX runtime. Run after editing present.hlsl and commit
rem the generated ps_*.h files.
setlocal
set FXC=
for /d %%d in ("%ProgramFiles(x86)%\Windows Kits\10\bin\10.*") do if exist "%%~d\x64\fxc.exe" set FXC=%%~d\x64\fxc.exe
if "%FXC%"=="" (echo fxc.exe not found - install a Windows 10 SDK & exit /b 1)
cd /d "%~dp0"
"%FXC%" /nologo /T ps_2_0 /E PS_Sharp /Fh ps_sharp.h /Vn g_psSharp present.hlsl || exit /b 1
"%FXC%" /nologo /T ps_2_0 /E PS_Cas   /Fh ps_cas.h   /Vn g_psCas   present.hlsl || exit /b 1
"%FXC%" /nologo /T vs_3_0 /E VS_Pass  /Fh vs_pass.h  /Vn g_vsPass  present.hlsl || exit /b 1
"%FXC%" /nologo /T ps_3_0 /E PS_Xbr   /Fh ps_xbr.h   /Vn g_psXbr   present.hlsl || exit /b 1
echo shaders built.
