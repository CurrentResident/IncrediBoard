cmake_minimum_required(VERSION 3.1)

project (IB LANGUAGES C CXX ASM)
set(MCU MK20DX256)

set(CMAKE_VERBOSE_MAKEFILE ON)

list (APPEND CONFIGURE_OPTIONS F_CPU=48000000 USB_SERIAL LAYOUT_US_ENGLISH USING_MAKEFILE)
list (APPEND ARDUINO_OPTIONS __${MCU}__ ARDUINO=10613 TEENSYDUINO=132)

list (APPEND COMPILE_FLAGS -Wall -g -Os -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections)

list (APPEND COMPILE_FLAGS_CXX -std=gnu++11 -felide-constructors -fno-exceptions -fno-rtti)

add_library (TeensyduinoCore_C STATIC
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
    ${TEENSYDUINO_LIB_PATH}/usb_touch.c)

add_library (TeensyduinoCore_CPP STATIC
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
    ${TEENSYDUINO_LIB_PATH}/yield.cpp)

add_library (TeensyduinoCore_ASM STATIC
    ${TEENSYDUINO_LIB_PATH}/memcpy-armv7m.S
    ${TEENSYDUINO_LIB_PATH}/memset.S)
#    TeensyduinoCore_C
#    TeensyduinoCore_CPP

target_include_directories (TeensyduinoCore_ASM PUBLIC ${TEENSYDUINO_LIB_PATH})
target_include_directories (TeensyduinoCore_C PUBLIC ${TEENSYDUINO_LIB_PATH})
target_include_directories (TeensyduinoCore_CPP PUBLIC ${TEENSYDUINO_LIB_PATH})

target_compile_options (TeensyduinoCore_ASM PRIVATE ${COMPILE_FLAGS})
target_compile_options (TeensyduinoCore_C PRIVATE ${COMPILE_FLAGS})
target_compile_options (TeensyduinoCore_CPP PRIVATE ${COMPILE_FLAGS} ${COMPILE_FLAGS_CXX})

target_compile_definitions (TeensyduinoCore_ASM PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})
target_compile_definitions (TeensyduinoCore_C PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})
target_compile_definitions (TeensyduinoCore_CPP PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})
