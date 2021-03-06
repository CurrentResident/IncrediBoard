# set your MCU type here, or make command line `make MCU=MK20DX256`
MCU=MK20DX256

# make it lower case
LOWER_MCU := $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$(MCU)))))))))))))))))))))))))))
MCU_LD = $(LOWER_MCU).ld

# The name of your project (used to name the compiled .hex file)
TARGET = main_test

# Those that specify a NO_ARDUINO environment variable will
# be able to use this Makefile with no Arduino dependency.
# Please note that if ARDUINOPATH was set, it will override
# the NO_ARDUINO behaviour.
ifndef NO_ARDUINO
# Path to your arduino installation
ARDUINOPATH ?= ../../../../..
#ARDUINOPATH ?= ../../../..
endif

# configurable options
OPTIONS = -DF_CPU=48000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE

# options needed by many Arduino libraries to configure for Teensy 3.0
OPTIONS += -D__$(MCU)__ -DARDUINO=10613 -DTEENSYDUINO=132


# Other Makefiles and project templates for Teensy 3.x:
#
# https://github.com/apmorton/teensy-template
# https://github.com/xxxajk/Arduino_Makefile_master
# https://github.com/JonHylands/uCee


#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Arduino Libraries.
# To use this makefile without Arduino, copy the resources from these
# locations and edit the pathnames.  The rest of Arduino is not needed.
#************************************************************************

ifdef ARDUINOPATH

TEENSYCOREPATH = $(abspath $(ARDUINOPATH)/hardware/teensy/avr/cores/teensy3)
LINKERSCRIPT = $(TEENSYCOREPATH)/$(MCU_LD)

# path location for Teensy Loader, teensy_post_compile and teensy_reboot (on Linux)
TOOLSPATH = $(abspath $(ARDUINOPATH)/hardware/tools)

# path location for Arduino libraries (currently not used)
LIBRARYPATH = $(abspath $(ARDUINOPATH)/libraries)

# path location for the arm-none-eabi compiler
COMPILERPATH = $(abspath $(ARDUINOPATH)/hardware/tools/arm/bin)

else
# Default to the normal GNU/Linux compiler path if NO_ARDUINO
# and ARDUINOPATH was not set.
COMPILERPATH ?= /usr/bin

endif

#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -Os -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections $(OPTIONS) \
		   -I. \
		   -I$(TEENSYCOREPATH) \
		   -I../../Core \
		   -I../../Platforms/Teensy3Teensyduino \
		   -I../../libs/boost_headers

# compiler options for C++ only
CXXFLAGS = -std=gnu++11 -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS =

# linker options
#LDFLAGS = -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=cortex-m4 -mthumb -T$(LINKERSCRIPT)
LDFLAGS = -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=cortex-m4 -mthumb -T$(LINKERSCRIPT)

# additional libraries to link
LIBS = -lm


# names for the compiler programs
AS = $(COMPILERPATH)/arm-none-eabi-as
CC = $(COMPILERPATH)/arm-none-eabi-gcc
CPP = $(COMPILERPATH)/arm-none-eabi-cpp
CXX = $(COMPILERPATH)/arm-none-eabi-g++
OBJCOPY = $(COMPILERPATH)/arm-none-eabi-objcopy
OBJDUMP = $(COMPILERPATH)/arm-none-eabi-objdump
SIZE = $(COMPILERPATH)/arm-none-eabi-size

# Automatically create lists of the sources and objects.

TEENSYCORESOURCES_ASM := $(wildcard $(TEENSYCOREPATH)/*.S)
TEENSYCORESOURCES_C   := $(wildcard $(TEENSYCOREPATH)/*.c)
TEENSYCORESOURCES_CPP := $(subst $(TEENSYCOREPATH)/main.cpp,,$(wildcard $(TEENSYCOREPATH)/*.cpp))

TOTAL_SRC := $(wildcard *.cpp) \
			$(wildcard ../../Core/*.cpp) \
			$(wildcard ../../Platforms/Teensy3Teensyduino/*.cpp) \
			$(TEENSYCORESOURCES_ASM) \
			$(TEENSYCORESOURCES_C) \
			$(TEENSYCORESOURCES_CPP)

VPATH += $(dir $(TOTAL_SRC))

OBJS := $(addprefix objs/,$(addsuffix .o,$(notdir $(basename $(TOTAL_SRC)))))

# the actual makefile rules (all .o files built by GNU make's default implicit rules)
objs/%.d : %.c | objs
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -MM -MF $@ -MT objs/$(*F).o
objs/%.d : %.S | objs
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -MM -MF $@ -MT objs/$(*F).o
objs/%.d : %.cpp | objs
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -MM -MF $@ -MT objs/$(*F).o
objs/%.o : %.c objs/%.d | objs
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
objs/%.o : %.cpp objs/%.d | objs
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
objs/%.o : %.S objs/%.d | objs
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: all

all: $(TARGET).hex

$(OBJS) : | objs

objs:
	mkdir objs

$(TARGET).elf: $(OBJS) $(LINKERSCRIPT)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.hex: %.elf
	$(SIZE) $<
	$(OBJDUMP) -S $< > $(notdir $@).lss
	$(OBJCOPY) -O ihex -R .eeprom $< $@
ifneq (,$(wildcard $(TOOLSPATH)))
#	$(TOOLSPATH)/teensy_post_compile -file=$(basename $@) -path=$(shell pwd) -tools=$(TOOLSPATH)
#	-$(TOOLSPATH)/teensy_reboot
endif

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET).elf $(TARGET).hex $(TARGET).hex.lss
