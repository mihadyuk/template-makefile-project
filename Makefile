PROJECT     		= exec-module-name
#USE_VERBOSE_COMPILE = yes
USE_X86			= yes
DISABLE_ASSERTS		= yes


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

ifeq ($(CROSS_COMPILE),)
	CROSS_COMPILE = /home/user/build/output-saturn/host/usr/bin/arm-buildroot-linux-gnueabihf-
endif

ifeq ($(CCACHE),)
     CCACHE =
endif

ifeq ($(USE_X86),yes)
	CPPC = $(CCACHE) g++
	CC   = $(CCACHE) gcc
	LD   = $(CCACHE) g++
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
	
	#c specific options
	COPT = -O2 -g3 -Wall -fmessage-length=0

	#c++ specific options
	CPPOPT = -std=c++0x -O2 -g3 -Wall -fmessage-length=0

	#linker options
	LDOPT = 
endif

ifeq ($(DISABLE_ASSERTS),yes)
	CPPOPT += -D NDEBUG
	COPT   += -D NDEBUG
endif



# Various directories
BUILDDIR  = build
OBJDIR    = $(BUILDDIR)/obj
LSTDIR    = $(BUILDDIR)/lst

# Output directory and files
OUTFILES = $(BUILDDIR)/$(PROJECT).elf

SRCPATHS = $(sort $(dir $(CSRC)) $(dir $(CPPSRC)))
# Object files groups
COBJS   = $(addprefix $(OBJDIR)/, $(notdir $(CSRC:.c=.o)))
CPPOBJS = $(addprefix $(OBJDIR)/, $(notdir $(CPPSRC:.cpp=.o)))
OBJS    = $(COBJS) $(CPPOBJS)

# Paths
IINCDIR   = $(patsubst %,-I%,$(INCDIR))
LLIBDIR   = $(patsubst %,-L%,$(LIBDIR))

ifeq ($(USE_X86),yes)
	# Generate dependency information
	COPT   += -MD -MP -MF .dep/$(@F).d
	CPPOPT += -MD -MP -MF .dep/$(@F).d
else
	# Generate dependency information
	COPT   += -MD -MP -MF .dep/$(@F).d
	CPPOPT += -MD -MP -MF .dep/$(@F).d
endif


# Paths where to search for sources
VPATH = $(SRCPATHS)

#
# Makefile rules
#

all: $(OBJS) $(OUTFILES)

$(OBJS): | $(BUILDDIR) $(OBJDIR) $(LSTDIR)

$(BUILDDIR):
ifneq ($(USE_VERBOSE_COMPILE),yes)
	@echo C compiler Options
	@echo $(CC) -c $(COPT) -I. $(IINCDIR)
	@echo C++ compiler options
	@echo $(CPPC) -c $(CPPOPT) -I. $(IINCDIR)
endif
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LSTDIR):
	mkdir -p $(LSTDIR)

$(CPPOBJS) : $(OBJDIR)/%.o : %.cpp Makefile
ifeq ($(USE_VERBOSE_COMPILE),yes)
	@echo 
	$(CPPC) -c $(CPPOPT) -I. $(IINCDIR) $< -o $@
else
	@echo Compiling $(<F) 
	@$(CPPC) -c $(CPPOPT) -I. $(IINCDIR) $< -o $@
endif

$(COBJS) : $(OBJDIR)/%.o : %.c Makefile
ifeq ($(USE_VERBOSE_COMPILE),yes)
	@echo 
	$(CC) -c $(COPT) -I. $(IINCDIR) $< -o $@
else
	@echo Compiling $(<F) 
	@$(CC) -c $(COPT) -I. $(IINCDIR) $< -o $@
endif

%.elf: $(OBJS)
ifeq ($(USE_VERBOSE_COMPILE),yes)
	@echo 
	$(LD) $(OBJS) $(LDOPT) -L$(LIBDIR) $(LIBS) -o $@
else
	@echo Linking $@
	@$(LD) $(OBJS) $(LDOPT) -L$(LIBDIR) $(LIBS) -o $@
endif



.PHONY: clean
clean:
	rm -fR $(BUILDDIR) .dep 


#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
