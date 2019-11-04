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
         exceptions \
         mem_alloc \
         classes \
         aggregateInit \
         templates \
         utilits \
         cross_references \
         smart_pointers \
         virtual_inheritance

# C source files
CSRC = $(wildcard ./*.c)


# CPP source files
CPPSRC = $(wildcard ./*.cpp) \
         $(wildcard exceptions/*.cpp) \
         $(wildcard mem_alloc/*.cpp) \
         $(wildcard classes/*.cpp) \
         $(wildcard aggregateInit/*.cpp) \
         $(wildcard templates/*.cpp) \
         $(wildcard utilits/*.cpp) \
         $(wildcard cross_references/*.cpp) \
         $(wildcard smart_pointers/*.cpp) \
         $(wildcard virtual_inheritance/*.cpp)

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
	COPT = -O0 -g3 -Wall -fmessage-length=0 -pedantic
endif	

#c++ specific options
ifeq ($(CPPOPT),)
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0 -pedantic
endif	

#asm options
ifeq ($(ASOPT),)
	ASOPT = 
endif	


#linker options
ifeq ($(LDOPT),)
	LDOPT =
endif	
	 


include rules.mk