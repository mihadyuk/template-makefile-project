ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif
#DISABLE_ASSERTS		= yes
#GPROF_EN = yes
#LST_FILE_GEN = yes
#DMP_FILE_GEN = yes
#ASM_LST_FILE_GEN = yes
#MAP_FILE_GEN     = yes

ifeq ($(VERBOSE_COMPILE),yes)
	USE_VERBOSE_COMPILE = yes
else
	USE_VERBOSE_COMPILE = 
endif

ifeq ($(ARCH),arm)
	USE_X86 = no
else
	USE_X86	= yes
endif	

ifeq ($(DISABLE_ASSERTS),yes)
	DISABLE_ASSERTS = yes
else
	DISABLE_ASSERTS	= no
endif

ifeq ($(CROSS_COMPILE),)
	CROSS_COMPILE = arm-buildroot-linux-gnueabihf-
endif

ifeq ($(CCACHE),)
     CCACHE =
endif


ifeq ($(USE_X86),yes)         
	#lib dir
	LIBDIR = /usr/lib
else
	#lib dir
	LIBDIR = .
endif

#used libs
#_LIBS = config++ pthread
_LIBS =
LIBS = $(addprefix -l, $(_LIBS))


#include dirs
INCDIR = .\
         src \

# C source files
CSRC = $(wildcard src/*.c) \
       $(wildcard ./*.c) \

# CPP source files
CPPSRC = $(wildcard ./*.cpp) \
         $(wildcard src/*.cpp) \




ifeq ($(USE_X86),yes)
	CPPC = $(CCACHE) g++
	CC   = $(CCACHE) gcc
	LD   = $(CCACHE) g++
	OD   = $(CCACHE) objdump
	SZ   = $(CCACHE) size
	AR   = $(CCACHE) ar
	#c specific options
	COPT = -O0 -g3 -Wall -fmessage-length=0
	
	#c++ specific options
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0
	
	#linker options
	LDOPT = 

else
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
	 
endif


include rules.mk