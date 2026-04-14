@echo off
setlocal

call "D:\Visual Studio\VC\Auxiliary\Build\vcvars64.bat" >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERROR] Cannot initialize MSVC environment.
    pause
    exit /b 1
)

set OBJ_DIR=%~dp0obj
set BIN_DIR=%~dp0bin

if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

cl /utf-8 /EHsc /I"%~dp0..\include" /Fo:"%OBJ_DIR%\\" /Fe:"%BIN_DIR%\test.exe" "%~dp0test.cpp"

if %errorlevel% neq 0 (
    echo.
    echo [BUILD FAILED]
) else (
    echo.
    echo [BUILD SUCCESS] bin\test.exe
)
pause
