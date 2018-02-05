set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(TEENSYDUINO_LIB_PATH      $ENV{ARDUINOPATH}/hardware/teensy/avr/cores/teensy3)
set(TEENSYDUINO_COMPILER_PATH $ENV{ARDUINOPATH}/hardware/tools/arm/bin)

#set(CMAKE_C_COMPILER   d:\\arduino-1.6.13\\hardware\\tools\\arm\\bin\\arm-none-eabi-gcc)
set(CMAKE_C_COMPILER   ${TEENSYDUINO_COMPILER_PATH}/arm-none-eabi-gcc.exe)
set(CMAKE_ASM_COMPILER ${TEENSYDUINO_COMPILER_PATH}/arm-none-eabi-gcc.exe)
set(CMAKE_CXX_COMPILER ${TEENSYDUINO_COMPILER_PATH}/arm-none-eabi-g++.exe)
set(CMAKE_OBJCOPY      ${TEENSYDUINO_COMPILER_PATH}/arm-none-eabi-objcopy.exe)# CACHE INTERNAL "objcopy tool")
set(CMAKE_SIZE         ${TEENSYDUINO_COMPILER_PATH}/arm-none-eabi-size.exe)# CACHE INTERNAL "size tool")

# Skip the horrible compiler test that's actually a compiler plus linker test.
# It fails for Teensyduino because _exit is defined in a specific file that we intend to compile.
set(CMAKE_C_COMPILER_WORKS 1)

#set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nano.specs")

set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")

#set(CMAKE_FIND_ROOT_PATH ${BINUTILS_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
