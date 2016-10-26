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
ifeq ($(ULIBS),)
	ULIBS =
endif	


CPPC = $(CCACHE) $(CROSS_COMPILE)g++
CC   = $(CCACHE) $(CROSS_COMPILE)gcc
LD   = $(CCACHE) $(CROSS_COMPILE)g++
OD   = $(CCACHE) $(CROSS_COMPILE)objdump
SZ   = $(CCACHE) $(CROSS_COMPILE)size
AR   = $(CCACHE) $(CROSS_COMPILE)ar

#c specific options
ifeq ($(COPT),)
	COPT = -O0 -g3 -Wall -fmessage-length=0
endif	

#c++ specific options
ifeq ($(CPPOPT),)
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0
endif	

#linker options
ifeq ($(LDOPT),)
	LDOPT =
endif	
	 


include rules.mk