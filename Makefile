ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif
CROSS_COMPILE=~/soft/gcc-arm-none-eabi/bin/arm-none-eabi-
#STARTUP_FILE=~/soft/gcc-arm-none-eabi/share/gcc-arm-none-eabi/samples/startup/startup_ARMCM4.S
#STARTUP_FILE=startup_ARMCM4.S
#LDSCRIPTS=-L~/soft/gcc-arm-none-eabi/share/gcc-arm-none-eabi/samples/ldscripts -T gcc.ld
LDSCRIPTS=-L. -T gcc.ld
MCPU=cortex-m4
#DISABLE_ASSERTS		= yes
#GPROF_EN = yes
#LST_FILE_GEN = yes
DMP_FILE_GEN = yes
ASM_LST_FILE_GEN = yes
MAP_FILE_GEN     = yes
USE_VERBOSE_COMPILE = yes

#include dirs
INCDIR = .\
         src \

# C source files
CSRC = $(wildcard src/*.c) \
       $(wildcard ./*.c) \

# CPP source files
CPPSRC = $(wildcard ./*.cpp) \
         $(wildcard src/*.cpp) \

#asm source files
ASSRC = $(wildcard ./*.S)


ifeq ($(LIBDIR),)
    LIBDIR  = .
endif

#used libs
#ULIBS = config++ pthread
ifeq ($(ULIBS),)
	ULIBS =
endif	


CPPC = $(CCACHE) $(CROSS_COMPILE)g++
CC   = $(CCACHE) $(CROSS_COMPILE)gcc
AS   = $(CCACHE) $(CROSS_COMPILE)as
LD   = $(CCACHE) $(CROSS_COMPILE)g++
OD   = $(CCACHE) $(CROSS_COMPILE)objdump
SZ   = $(CCACHE) $(CROSS_COMPILE)size
AR   = $(CCACHE) $(CROSS_COMPILE)ar


#c specific options
ifeq ($(COPT),)
	COPT = -O0 -g3 -Wall -fmessage-length=0 -mcpu=$(MCPU)
endif	

#c++ specific options
ifeq ($(CPPOPT),)
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0 -fno-rtti -fno-exceptions -mcpu=$(MCPU)
endif	

#asm options
ifeq ($(ASOPT),)
	ASOPT = 
endif	


#linker options
ifeq ($(LDOPT),)
	LDOPT = -mcpu=$(MCPU) $(LDSCRIPTS)
endif	
	 


include rules.mk
