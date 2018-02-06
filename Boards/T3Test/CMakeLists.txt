cmake_minimum_required(VERSION 3.1)

project (IB LANGUAGES C CXX ASM)

set(MCU MK20DX256)
string(TOLOWER ${MCU}.ld LINKER_SCRIPT)

set(CMAKE_VERBOSE_MAKEFILE ON)

list (APPEND CONFIGURE_OPTIONS F_CPU=48000000 USB_SERIAL LAYOUT_US_ENGLISH USING_MAKEFILE)
list (APPEND ARDUINO_OPTIONS __${MCU}__ ARDUINO=10613 TEENSYDUINO=132)

list (APPEND COMPILE_FLAGS -Wall -g -Os -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections)

list (APPEND COMPILE_FLAGS_CXX -std=gnu++11 -felide-constructors -fno-exceptions -fno-rtti)

# In the cmake-ideal world, we'd have one lib for each language and assign the language-specific
# options to each lib accordingly.
#
# In the Teensyduino-real world, we have yield.cpp which implements a C namespace function that calls
# CPP code but is itself called by C - a circular dependency.  So we have to make a monolithic library,
# within which GCC tolerates internal circular dependencies just fine.
#
# The problem is that cmake doesn't make it easy to have mixed-language libraries whose compile options
# vary by language type, so we brute-force it here.
#
set (CMAKE_CXX_FLAGS "-std=gnu++11 -felide-constructors -fno-exceptions -fno-rtti")

add_library (TeensyduinoCore STATIC
    ${TEENSYDUINO_LIB_PATH}/analog.c
    ${TEENSYDUINO_LIB_PATH}/eeprom.c
    ${TEENSYDUINO_LIB_PATH}/keylayouts.c
    ${TEENSYDUINO_LIB_PATH}/math_helper.c
    ${TEENSYDUINO_LIB_PATH}/mk20dx128.c
    ${TEENSYDUINO_LIB_PATH}/nonstd.c
    ${TEENSYDUINO_LIB_PATH}/pins_teensy.c
    ${TEENSYDUINO_LIB_PATH}/ser_print.c
    ${TEENSYDUINO_LIB_PATH}/serial1.c
    ${TEENSYDUINO_LIB_PATH}/serial2.c
    ${TEENSYDUINO_LIB_PATH}/serial3.c
    ${TEENSYDUINO_LIB_PATH}/serial4.c
    ${TEENSYDUINO_LIB_PATH}/serial5.c
    ${TEENSYDUINO_LIB_PATH}/serial6.c
    ${TEENSYDUINO_LIB_PATH}/serial6_lpuart.c
    ${TEENSYDUINO_LIB_PATH}/touch.c
    ${TEENSYDUINO_LIB_PATH}/usb_desc.c
    ${TEENSYDUINO_LIB_PATH}/usb_dev.c
    ${TEENSYDUINO_LIB_PATH}/usb_joystick.c
    ${TEENSYDUINO_LIB_PATH}/usb_keyboard.c
    ${TEENSYDUINO_LIB_PATH}/usb_mem.c
    ${TEENSYDUINO_LIB_PATH}/usb_midi.c
    ${TEENSYDUINO_LIB_PATH}/usb_mouse.c
    ${TEENSYDUINO_LIB_PATH}/usb_mtp.c
    ${TEENSYDUINO_LIB_PATH}/usb_rawhid.c
    ${TEENSYDUINO_LIB_PATH}/usb_seremu.c
    ${TEENSYDUINO_LIB_PATH}/usb_serial.c
    ${TEENSYDUINO_LIB_PATH}/usb_touch.c
    ${TEENSYDUINO_LIB_PATH}/yield.cpp
    ${TEENSYDUINO_LIB_PATH}/AudioStream.cpp
    ${TEENSYDUINO_LIB_PATH}/avr_emulation.cpp
    ${TEENSYDUINO_LIB_PATH}/DMAChannel.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial1.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial2.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial3.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial4.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial5.cpp
    ${TEENSYDUINO_LIB_PATH}/HardwareSerial6.cpp
    ${TEENSYDUINO_LIB_PATH}/IntervalTimer.cpp
    ${TEENSYDUINO_LIB_PATH}/IPAddress.cpp
    ${TEENSYDUINO_LIB_PATH}/new.cpp
    ${TEENSYDUINO_LIB_PATH}/Print.cpp
    ${TEENSYDUINO_LIB_PATH}/Stream.cpp
    ${TEENSYDUINO_LIB_PATH}/Tone.cpp
    ${TEENSYDUINO_LIB_PATH}/usb_audio.cpp
    ${TEENSYDUINO_LIB_PATH}/usb_flightsim.cpp
    ${TEENSYDUINO_LIB_PATH}/usb_inst.cpp
    ${TEENSYDUINO_LIB_PATH}/WMath.cpp
    ${TEENSYDUINO_LIB_PATH}/WString.cpp
    ${TEENSYDUINO_LIB_PATH}/memcpy-armv7m.S
    ${TEENSYDUINO_LIB_PATH}/memset.S)

target_include_directories (TeensyduinoCore PUBLIC  ${TEENSYDUINO_LIB_PATH})
target_compile_options     (TeensyduinoCore PRIVATE ${COMPILE_FLAGS})
target_compile_definitions (TeensyduinoCore PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})

add_executable (T3Test.elf
    ../../Core/main.cpp
    ../../Platforms/Teensy3Teensyduino/PlatformSpecific.cpp
    ../../Platforms/Teensy3Teensyduino/UsbInterface.cpp)

target_compile_definitions (T3Test.elf PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})
target_compile_options     (T3Test.elf PRIVATE ${COMPILE_FLAGS} ${COMPILE_FLAGS_CXX})
target_include_directories (T3Test.elf PUBLIC  .
                                           ../../Core
                                           ../../Platforms/Teensy3Teensyduino
                                           ../../libs/boost_headers)

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs")

target_link_libraries (T3Test.elf
    TeensyduinoCore
    -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 -mcpu=cortex-m4 -mthumb -T${TEENSYDUINO_LIB_PATH}/${LINKER_SCRIPT})

