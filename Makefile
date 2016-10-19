ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif
#DISABLE_ASSERTS		= yes
#GPROF_EN = yes
#LST_FILE_GEN = yes
#DMP_FILE_GEN = yes
#ASM_LST_FILE_GEN = yes
#MAP_FILE_GEN     = yes
#USE_VERBOSE_COMPILE = yes

#include dirs
INCDIR = .\
         src \

# C source files
CSRC = $(wildcard src/*.c) \
       $(wildcard ./*.c) \

# CPP source files
CPPSRC = $(wildcard ./*.cpp) \
         $(wildcard src/*.cpp) \

#used libs
#ULIBS = config++ pthread
ULIBS =


CPPC = $(CCACHE) $(CROSS_COMPILE)g++
CC   = $(CCACHE) $(CROSS_COMPILE)gcc
LD   = $(CCACHE) $(CROSS_COMPILE)g++
OD   = $(CCACHE) $(CROSS_COMPILE)objdump
SZ   = $(CCACHE) $(CROSS_COMPILE)size
AR   = $(CCACHE) $(CROSS_COMPILE)ar
#c specific options
COPT = -O2 -g3 -Wall -fmessage-length=0

#c++ specific options
CPPOPT = -std=c++0x -O2 -g3 -Wall -fmessage-length=0

#linker options
LDOPT =
	 


include rules.mk