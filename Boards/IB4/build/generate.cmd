@echo off

call tools.cmd

:: Shamelessly lifted from https://stackoverflow.com/questions/4781772/how-to-test-if-an-executable-exists-in-the-path-from-a-windows-batch-file
::
for %%X in (sh.exe)            do (set FOUND_SH=%%~$PATH:X)
for %%X in (make.exe)          do (set FOUND_MAKE=%%~$PATH:X)
for %%X in (mingw32-make.exe)  do (set FOUND_MAKE=%%~$PATH:X)
for %%X in (cmake.exe)         do (set FOUND_CMAKE=%%~$PATH:X)

if not defined FOUND_CMAKE goto NO_CMAKE
if not defined FOUND_MAKE  goto NO_MAKE

if defined FOUND_SH (set CMAKE_GENERATOR="MSYS Makefiles") else (set CMAKE_GENERATOR="MinGW Makefiles")

@echo on
cmake .. -G %CMAKE_GENERATOR% -DCMAKE_TOOLCHAIN_FILE=../teensyduino.cmake
@echo off

goto END

:NO_CMAKE
echo CMake not found in path!  Bailing out.
goto END

:NO_MAKE
echo make not found in path!  Bailing out.
goto END

:END
pause
