@echo off
REM Simple compile helper for Windows (uses g++ in PATH)
REM Compiles all .cpp files found under the project (recursively) and outputs main.exe















echo Compiled to main.exe)  exit /b %errorlevel%  echo Compilation failed with exit code %errorlevel%.if %errorlevel% neq 0 (
ng++ -fdiagnostics-color=always -g %SRCS% -Iinclude -o main.exe)  exit /b 1  echo No .cpp files found.
nif "%SRCS%"=="" ()  if defined SRCS (set "SRCS=!SRCS! "%%f"") else (set "SRCS=%%f")for /r %%f in (*.cpp) do (n:: collect source files
nset "SRCS="