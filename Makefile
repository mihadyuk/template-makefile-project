ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif

ifeq ($(CROSS_COMPILE),)
ifeq ($(OS),Windows_NT)
CROSS_COMPILE=/cygdrive/c/gcc-arm-none-eabi/bin/arm-none-eabi-
else
CROSS_COMPILE=~/soft/gcc-arm-none-eabi/bin/arm-none-eabi-
endif
endif

#STARTUP_FILE=~/soft/gcc-arm-none-eabi/share/gcc-arm-none-eabi/samples/startup/startup_ARMCM4.S
#STARTUP_FILE=startup_ARMCM4.S
#LDSCRIPTS=-L~/soft/gcc-arm-none-eabi/share/gcc-arm-none-eabi/samples/ldscripts -T gcc.ld
LDSCRIPTS=-L. -T gcc.ld
MCPU = -mcpu=cortex-m4 -mfloat-abi=softfp -mthumb -mfpu=fpv4-sp-d16
#DISABLE_ASSERTS		= yes
#GPROF_EN = yes
#LST_FILE_GEN = yes
DMP_FILE_GEN = yes
ASM_LST_FILE_GEN = yes
MAP_FILE_GEN     = yes
#USE_VERBOSE_COMPILE = yes
USE_LTO = yes

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
AS   = $(CCACHE) $(CROSS_COMPILE)g++
LD   = $(CCACHE) $(CROSS_COMPILE)g++
OD   = $(CCACHE) $(CROSS_COMPILE)objdump
SZ   = $(CCACHE) $(CROSS_COMPILE)size
AR   = $(CCACHE) $(CROSS_COMPILE)ar

ifeq ($(USE_LTO),yes)
	LTO = -flto
endif

#c specific options
ifeq ($(COPT),)
	COPT = -O2 -g3 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections $(MCPU) $(LTO) -pedantic
	COPT += --specs=nano.specs -u _printf_float
	#COPT += --specs=rdimon.specs 
endif	

#c++ specific options
ifeq ($(CPPOPT),)
	CPPOPT = -std=c++0x -O2 -g3 -Wall -fmessage-length=0 -fno-rtti -fno-exceptions -ffunction-sections -fdata-sections -pedantic $(MCPU) $(LTO)
	CPPOPT += --specs=nano.specs -u _printf_float
	#CPPOPT += --specs=rdimon.specs
endif	

#asm options
ifeq ($(ASOPT),)
	ASOPT = $(MCPU) -D__NO_SYSTEM_INIT
endif	


#linker options
ifeq ($(LDOPT),)
	LDOPT = $(MCPU) $(LDSCRIPTS) $(LTO) 
	LDOPT += --specs=nano.specs -u _printf_float
	LDOPT += --specs=rdimon.specs  
	#LDOPT += --specs=nosys.specs
endif	
	 


include rules.mk
