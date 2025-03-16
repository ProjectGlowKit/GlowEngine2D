@echo off
:: VISUAL STUDIO
for /f "usebackq tokens=*" %%i in (`"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do set "VS_PATH=%%i"
:: Verify the VS_PATH
if not defined VS_PATH (
    echo Visual Studio installation not found.
) else (
    echo Found Visual Studio at %VS_PATH%
    :: Set Visual Studio executable path and MSBuild path
    set "VS_EXE=%VS_PATH%\Common7\IDE\devenv.exe"
    set "MSBUILD_PATH=%VS_PATH%\MSBuild\Current\Bin\MSBuild.exe"
    :: Export environment variables
    setx VS_PATH "%VS_PATH%"
    setx VS_EXE "%VS_EXE%"
    setx MSBUILD_PATH "%MSBUILD_PATH%"
    :: Debug
    echo Visual Studio path - VS_PATH: %VS_PATH%
    echo Visual Studio executable - VS_EXE: %VS_EXE%
    echo MSBuild path - MSBUILD_PATH: %MSBUILD_PATH%
)

:: Define the glow command
set PATH=%CD%\..\tools\windows;%PATH%
cd /d "%~dp0\.."

:: Run the tools init.py
python ".\setup\init\config.py"
cmd