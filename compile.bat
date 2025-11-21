@echo off
REM Wrapper batch: invoke the PowerShell compile script (handles paths/quoting reliably)
pushd "%~dp0"
powershell -ExecutionPolicy Bypass -File "%~dp0\compile.ps1"
set "RC=%ERRORLEVEL%"
popd
exit /b %RC%
@echo off
REM Simple compile helper for Windows (uses g++ in PATH)
REM Compiles all .cpp files found under the project (recursively) and outputs main.exe

setlocal enabledelayedexpansion

:: collect source files
set "SRCS="
for /r %%f in (*.cpp) do (
  if defined SRCS (
    @echo off
    REM Simple compile helper for Windows (uses g++ in PATH)
    REM Compiles all .cpp files found under the project (recursively) and outputs main.exe

    setlocal enabledelayedexpansion

    :: collect source files
    set "SRCS="
    for /r %%f in (*.cpp) do (
      if defined SRCS (
        set "SRCS=!SRCS! ""%%~f"""
      ) else (
        set "SRCS=""%%~f"""
      )
    )

    if "%SRCS%"=="" (
      echo No .cpp files found.
      endlocal
      exit /b 1
    )

    :: detect g++: prefer PATH, fallback to common MSYS2 MinGW location
    where g++ >nul 2>&1
    if %errorlevel% neq 0 (
      if exist "C:\\msys64\\mingw64\\bin\\g++.exe" (
        set "GPP=C:\\msys64\\mingw64\\bin\\g++.exe"
      ) else (
        echo g++ non trovato in PATH e nessun g++ predefinito trovato.
        endlocal
        exit /b 1
      )
    ) else (
      set "GPP=g++"
    )

    "%GPP%" -fdiagnostics-color=always -g %SRCS% -Iinclude -o main.exe
    if %errorlevel% neq 0 (
      echo Compilation failed with exit code %errorlevel%.
      endlocal
      exit /b %errorlevel%
    )

    echo Compiled to main.exe
    endlocal