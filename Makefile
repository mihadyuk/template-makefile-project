ifeq ($(PROJECT),)
	PROJECT	= exec-module-name
endif
#USE_CCACHE 			= yes
#USE_VERBOSE_COMPILE = yes
#USE_X86				= yes
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
	
ifeq ($(ASM_LST_FILE_GEN),yes)	
	COPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.c=.lst))
endif	

	#c++ specific options
	CPPOPT = -std=c++0x -O0 -g3 -Wall -fmessage-length=0
	
ifeq ($(ASM_LST_FILE_GEN),yes)	
	CPPOPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.cpp=.lst))
endif	

	#linker options
	LDOPT = 

ifeq ($(MAP_FILE_GEN),yes)	
	LDOPT += -Wl,-Map=$(BUILDDIR)/$(PROJECT).map
endif	
	
	ODFLAGS	  = -x --syms
else
	CPPC = $(CCACHE) $(CROSS_COMPILE)g++
	CC   = $(CCACHE) $(CROSS_COMPILE)gcc
	LD   = $(CCACHE) $(CROSS_COMPILE)g++
	OD   = $(CCACHE) $(CROSS_COMPILE)objdump
	SZ   = $(CCACHE) $(CROSS_COMPILE)size
	AR   = $(CCACHE) $(CROSS_COMPILE)ar
	#c specific options
	COPT = -O2 -g3 -Wall -fmessage-length=0
	
ifeq ($(ASM_LST_FILE_GEN),yes)	
	COPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.c=.lst))
endif	

	#c++ specific options
	CPPOPT = -std=c++0x -O2 -g3 -Wall -fmessage-length=0
	
ifeq ($(ASM_LST_FILE_GEN),yes)	
	CPPOPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.cpp=.lst))
endif	

	#linker options
	LDOPT =
	 
ifeq ($(MAP_FILE_GEN),yes)	
	LDOPT += -Wl,-Map=$(BUILDDIR)/$(PROJECT).map
endif	
	
	ODFLAGS	  = -x --syms
endif

ifeq ($(GPROF_EN),yes)
     CPPOPT += -pg
     COPT   += -pg
     LDOPT  += -pg 
endif

ifeq ($(DISABLE_ASSERTS),yes)
	CPPOPT += -D NDEBUG
	COPT   += -D NDEBUG
endif



# Various directories
ifeq ($(BUILDDIR),)
BUILDDIR  = build
endif
OBJDIR    = $(BUILDDIR)/obj
LSTDIR    = $(BUILDDIR)/lst

# Output directory and files
OUTFILES = $(BUILDDIR)/$(PROJECT).elf
ifeq ($(DMP_FILE_GEN),yes)
	OUTFILES += $(BUILDDIR)/$(PROJECT).dmp
endif	
ifeq ($(LST_FILE_GEN),yes)
    OUTFILES += $(BUILDDIR)/$(PROJECT).list
endif           

SRCPATHS = $(sort $(dir $(CSRC)) $(dir $(CPPSRC)))
# Object files groups
COBJS   = $(addprefix $(OBJDIR)/, $(notdir $(CSRC:.c=.o)))
CPPOBJS = $(addprefix $(OBJDIR)/, $(notdir $(CPPSRC:.cpp=.o)))
OBJS    = $(COBJS) $(CPPOBJS)

# Paths
IINCDIR   = $(patsubst %,-I%,$(INCDIR))
LLIBDIR   = $(patsubst %,-L%,$(LIBDIR))


# Generate dependency information
COPT   += -MD -MP -MF .dep/$(@F).d
CPPOPT += -MD -MP -MF .dep/$(@F).d


# Paths where to search for sources
VPATH = $(SRCPATHS)

#
# Makefile rules
#

.PHONY: all
all: $(OBJS) $(OUTFILES)

$(OBJS): | $(BUILDDIR) $(OBJDIR) $(LSTDIR)

$(BUILDDIR):
ifneq ($(USE_VERBOSE_COMPILE),yes)
	@echo C compiler Options
	@echo $(CC) -c $(COPT) -I. $(IINCDIR)
	@echo C++ compiler options
	@echo $(CPPC) -c $(CPPOPT) -I. $(IINCDIR)
	@echo Linker options
	@echo $(LD) $(LDOPT) -L$(LIBDIR) $(LIBS) 
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

%.dmp: %.elf
ifeq ($(USE_VERBOSE_COMPILE),yes)
	$(OD) $(ODFLAGS) $< > $@
	$(SZ) $<
else
	@echo Creating $@
	@$(OD) $(ODFLAGS) $< > $@
	@echo
	@$(SZ) $<
endif

%.list: %.elf
ifeq ($(USE_VERBOSE_COMPILE),yes)
	$(OD) -S $< > $@
else
	@echo Creating $@
	@$(OD) -S $< > $@
	@echo
	@echo Done
endif

.PHONY: lib
lib: $(OBJS) $(BUILDDIR)/lib$(PROJECT).a

$(BUILDDIR)/lib$(PROJECT).a: $(OBJS)
ifeq ($(USE_VERBOSE_COMPILE),yes)
	$(AR) -r $@ $^
else
	@$(AR) -r $@ $^
	@echo
	@echo Done
endif

.PHONY: clean
clean:
	rm -fR $(BUILDDIR) .dep 


#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
