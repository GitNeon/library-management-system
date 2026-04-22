@echo off
setlocal

set OBJ_DIR=%~dp0obj
set BIN_DIR=%~dp0bin

if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

g++ -std=c++11 -Wall -Wextra -I"%~dp0..\include" -o "%BIN_DIR%\test.exe" "%~dp0test.cpp"

if %errorlevel% neq 0 (
    echo.
    echo [BUILD FAILED]
) else (
    echo.
    echo [BUILD SUCCESS] bin\test.exe
)
pause
