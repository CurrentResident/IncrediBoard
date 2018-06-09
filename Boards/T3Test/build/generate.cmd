
set ARDUINOPATH=D:/arduino-1.6.13

set COMPILERPATH=D:/gcc-arm-none-eabi-7-2017-q4-major-win32/bin

cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=../teensyduino.cmake

pause
