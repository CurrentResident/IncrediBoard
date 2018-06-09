cmake_minimum_required(VERSION 3.1)

project (IB LANGUAGES C CXX ASM)

set(BOARD_NAME T3Test)

set(MCU MK20DX256)
string(TOLOWER ${MCU}.ld LINKER_SCRIPT)

# Uncomment the following to see the gory details during build.
#
#set(CMAKE_VERBOSE_MAKEFILE ON)

list (APPEND CONFIGURE_OPTIONS F_CPU=48000000 LAYOUT_US_ENGLISH USING_MAKEFILE)
list (APPEND ARDUINO_OPTIONS __${MCU}__ ARDUINO=10613 TEENSYDUINO=132)

list (APPEND COMPILE_FLAGS -Wall -g -Os -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections)

list (APPEND COMPILE_FLAGS_CXX -std=gnu++14 -felide-constructors -fno-exceptions -fno-rtti)

list (APPEND TEENSYDUINO_CORE_OPTIONS USB_DISABLED)

# Build a monolithic Teensyduino library rather than separate ones for each language because there are circular
# dependencies (i.e. C calling an extern-C'd CPP function that calls C), so the linker needs the offending code
# to be within a single library.
#
# Here we do that by compiling the CPP code as an "object library" which can be included via source into the
# monolithic library.

add_library (TeensyduinoCore_CPP OBJECT
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
    ${TEENSYDUINO_LIB_PATH}/WString.cpp)

target_include_directories (TeensyduinoCore_CPP PUBLIC  ${TEENSYDUINO_LIB_PATH})
target_compile_options     (TeensyduinoCore_CPP PRIVATE ${COMPILE_FLAGS} ${COMPILE_FLAGS_CXX})
target_compile_definitions (TeensyduinoCore_CPP PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS} ${TEENSYDUINO_CORE_OPTIONS})

add_library (TeensyduinoCore STATIC
    $<TARGET_OBJECTS:TeensyduinoCore_CPP>
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
    ${TEENSYDUINO_LIB_PATH}/memcpy-armv7m.S
    ${TEENSYDUINO_LIB_PATH}/memset.S)

target_include_directories (TeensyduinoCore PUBLIC  ${TEENSYDUINO_LIB_PATH})
target_compile_options     (TeensyduinoCore PRIVATE ${COMPILE_FLAGS})
target_compile_definitions (TeensyduinoCore PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS} ${TEENSYDUINO_CORE_OPTIONS})

add_library (TeensyduinoUsb_C OBJECT
    ../../Platforms/Teensy3Teensyduino/USB/usb_desc.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_dev.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_joystick.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_keyboard.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_mem.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_midi.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_mouse.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_mtp.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_rawhid.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_seremu.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_serial.c
    ../../Platforms/Teensy3Teensyduino/USB/usb_touch.c)

target_include_directories (TeensyduinoUsb_C PUBLIC  ../../Platforms/Teensy3Teensyduino
                                                     ../../Platforms/Teensy3Teensyduino/USB
                                                     ${TEENSYDUINO_LIB_PATH})
target_compile_options     (TeensyduinoUsb_C PRIVATE ${COMPILE_FLAGS})
target_compile_definitions (TeensyduinoUsb_C PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})

add_library (TeensyduinoUsb STATIC
                           $<TARGET_OBJECTS:TeensyduinoUsb_C>
                           ../../Platforms/Teensy3Teensyduino/USB/usb_audio.cpp
                           ../../Platforms/Teensy3Teensyduino/USB/usb_flightsim.cpp)
                       #                           ../../Platforms/Teensy3Teensyduino/USB/usb_inst.cpp)

target_include_directories (TeensyduinoUsb PUBLIC  ../../Platforms/Teensy3Teensyduino
                                                   ../../Platforms/Teensy3Teensyduino/USB
                                                   ${TEENSYDUINO_LIB_PATH})
target_compile_options     (TeensyduinoUsb PRIVATE ${COMPILE_FLAGS} ${COMPILE_FLAGS_CXX})
target_compile_definitions (TeensyduinoUsb PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})

add_executable (${BOARD_NAME}.elf ../../Core/main.cpp
                           ../../Platforms/Teensy3Teensyduino/PlatformSpecific.cpp
                           ../../Platforms/Teensy3Teensyduino/UsbInterface.cpp)

target_compile_definitions (${BOARD_NAME}.elf PRIVATE ${CONFIGURE_OPTIONS} ${ARDUINO_OPTIONS})
target_compile_options     (${BOARD_NAME}.elf PRIVATE ${COMPILE_FLAGS} ${COMPILE_FLAGS_CXX})
target_include_directories (${BOARD_NAME}.elf PUBLIC  .
                                           ../../Core
                                           ../../Platforms/Teensy3Teensyduino
                                           ../../libs/boost_headers)

set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs")

target_link_libraries (${BOARD_NAME}.elf
    TeensyduinoUsb
    TeensyduinoCore
    -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 -mcpu=cortex-m4 -mthumb -T${TEENSYDUINO_LIB_PATH}/${LINKER_SCRIPT})

# Stupid Cmake bug requires us to make a "front-end" custom target that our worker custom targets must depend on
# to inhibit parallel build jobs from running the same commands simultaneously.
#
# See the following:
#
# https://samthursfield.wordpress.com/2015/11/21/cmake-dependencies-between-targets-and-files-and-custom-commands/
# https://cmake.org/Bug/view.php?id=10082
#
add_custom_target (${BOARD_NAME}.elf.complete
                   DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.elf)

# ---------------------------------------------------------------
# Hex file
add_custom_command (OUTPUT ${BOARD_NAME}.hex
                    COMMAND ${COMPILER_PATH}/arm-none-eabi-objcopy -O ihex -R .eeprom ${BOARD_NAME}.elf ${BOARD_NAME}.hex
                    DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.elf)

add_custom_target (${BOARD_NAME}_hex_file
                   ALL
                   DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.hex ${BOARD_NAME}.elf.complete)

# ---------------------------------------------------------------
# Final assembly file
add_custom_command (OUTPUT ${BOARD_NAME}.lss
                    COMMAND ${COMPILER_PATH}/arm-none-eabi-objdump -S ${BOARD_NAME}.elf > ${BOARD_NAME}.lss
                    DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.elf)

add_custom_target (${BOARD_NAME}_lss_file
                   ALL
                   DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.lss ${BOARD_NAME}.elf.complete)

# ---------------------------------------------------------------
# Size
# We don't want this to execute in parallel, and we want it to not run until the hex and lss
# targets are finished, so we only have the command depend on those two targets...
add_custom_command (OUTPUT ${BOARD_NAME}.size.txt
                    COMMAND ${COMPILER_PATH}/arm-none-eabi-size ${BOARD_NAME}.elf > ${BOARD_NAME}.size.txt
                    COMMAND ${COMPILER_PATH}/arm-none-eabi-size ${BOARD_NAME}.elf
                    DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.lss ${CMAKE_BINARY_DIR}/${BOARD_NAME}.hex)

add_custom_target (${BOARD_NAME}_size_file
                   ALL
                   DEPENDS ${CMAKE_BINARY_DIR}/${BOARD_NAME}.size.txt)
