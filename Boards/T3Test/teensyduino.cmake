set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

#set(TEENSYDUINO_LIB_PATH      $ENV{ARDUINOPATH}/hardware/teensy/avr/cores/teensy3)
set(TEENSYDUINO_LIB_PATH      ${CMAKE_SOURCE_DIR}/../../Platforms/Teensy3Teensyduino/cores/teensy3)

set(TEENSYDUINO_COMPILER_PATH $ENV{ARDUINOPATH}/hardware/tools/arm/bin)

set(COMPILER_PATH ${TEENSYDUINO_COMPILER_PATH})

if (IS_DIRECTORY $ENV{COMPILERPATH})
    set(COMPILER_PATH $ENV{COMPILERPATH})
endif()

set(CMAKE_C_COMPILER   ${COMPILER_PATH}/arm-none-eabi-gcc.exe)
set(CMAKE_ASM_COMPILER ${COMPILER_PATH}/arm-none-eabi-gcc.exe)
set(CMAKE_CXX_COMPILER ${COMPILER_PATH}/arm-none-eabi-g++.exe)
set(CMAKE_OBJCOPY      ${COMPILER_PATH}/arm-none-eabi-objcopy.exe)
set(CMAKE_SIZE         ${COMPILER_PATH}/arm-none-eabi-size.exe)

set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
