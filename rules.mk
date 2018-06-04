ifeq ($(ASM_LST_FILE_GEN),yes)	
	COPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.c=.lst))
endif	
ifeq ($(ASM_LST_FILE_GEN),yes)	
	CPPOPT += -Wa,-almsh=$(LSTDIR)/$(notdir $(<:.cpp=.lst))
endif	
ifeq ($(MAP_FILE_GEN),yes)	
	LDOPT += -Wl,-Map=$(BUILDDIR)/$(PROJECT).map
endif	
ifeq ($(ODFLAGS),)
	ODFLAGS	  = -x --syms --demangle --disassemble-all --line-numbers
	ODFLAGS += --disassemble-zeroes
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

SRCPATHS = $(sort $(dir $(CSRC)) $(dir $(CPPSRC)) $(dir $(ASSRC)))
# Object files groups
COBJS   = $(addprefix $(OBJDIR)/, $(notdir $(CSRC:.c=.o)))
CPPOBJS = $(addprefix $(OBJDIR)/, $(notdir $(CPPSRC:.cpp=.o)))
ASOBJS  = $(addprefix $(OBJDIR)/, $(notdir $(ASSRC:.S=.o)))
OBJS    = $(COBJS) $(CPPOBJS) $(ASOBJS)
#lib dir
#LIBDIR  = . #/usr/lib
LIBS    = $(addprefix -l, $(ULIBS))

# Paths
IINCDIR   = $(patsubst %,-I%,$(INCDIR))
LLIBDIR   = $(patsubst %,-L%,$(LIBDIR))


# Generate dependency information
COPT   += -MD -MP -MF .dep/$(@F).d
CPPOPT += -MD -MP -MF .dep/$(@F).d
ASOPT  += -MD -MP -MF .dep/$(@F).d
#ASOPT  += --MD .dep/$(@F).d


# Paths where to search for sources
VPATH = $(SRCPATHS)

#
# Makefile rules
#

.PHONY: all
all: PRE_MAKE_ALL_RULE_HOOK $(OBJS) $(OUTFILES) POST_MAKE_ALL_RULE_HOOK

PRE_MAKE_ALL_RULE_HOOK:

POST_MAKE_ALL_RULE_HOOK:


$(OBJS): | $(BUILDDIR) $(OBJDIR) $(LSTDIR)

$(BUILDDIR):
ifneq ($(USE_VERBOSE_COMPILE),yes)
	@echo asm Options
	@echo $(AS) -c $(ASOPT) $(IINCDIR)
	@echo C compiler Options
	@echo $(CC) -c $(COPT) $(IINCDIR)
	@echo C++ compiler options
	@echo $(CPPC) -c $(CPPOPT) $(IINCDIR)
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
	$(CPPC) -c $(CPPOPT) $(IINCDIR) $< -o $@
else
	@echo Compiling $(<F) 
	@$(CPPC) -c $(CPPOPT) $(IINCDIR) $< -o $@
endif

$(COBJS) : $(OBJDIR)/%.o : %.c Makefile
ifeq ($(USE_VERBOSE_COMPILE),yes)
	@echo 
	$(CC) -c $(COPT) $(IINCDIR) $< -o $@
else
	@echo Compiling $(<F) 
	@$(CC) -c $(COPT) $(IINCDIR) $< -o $@
endif

$(ASOBJS) : $(OBJDIR)/%.o : %.S Makefile
ifeq ($(USE_VERBOSE_COMPILE),yes)
	@echo 
	$(CPPC) -c $(ASOPT) $(IINCDIR) $< -o $@
else
	@echo Compiling $(<F) 
	@$(CPPC) -c $(ASOPT) $(IINCDIR) $< -o $@
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