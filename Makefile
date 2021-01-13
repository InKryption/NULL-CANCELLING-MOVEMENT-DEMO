# A generic C++ Makefile made to work with MinGW on WSL, for building executables.

.ONESHELL: # Make everything happen in the same shell

# DEFINITION REQUISITES:

# 'COMPILER': Compiler path
# 'ROOT': Root directory of the project
# 'BIN': Bin folder relative to $(ROOT)/
# 'SRC': Source files folder relative to $(ROOT)/
# 'BUILD': Name of the build
# 'NAME': Name of the project / resulting executable


# OTHER DEFINITIONS

# 'INCLUDE': List of include search paths
# 'LIBRARY': List of library search paths
# 'LIBNAME': List of library names to be used in the project
# 'LFLAG': linker flags
# 'CFLAG': compiler flags

ifeq ("$(CFG)","")

ifneq ("$(Cfg)","")
CFG=$(Cfg)
else ifneq ("$(cfg)","")
CFG=$(cfg)
endif

endif

ifeq ("$(CFG)$(Cfg)$(cfg)","")
include .make/Debug.mk
else
$(eval include .make/$(CFG).mk)
endif

# default definitions

ifeq ("$(COMPILER)","")
COMPILER:=g++
endif

ifeq ("$(ROOT)","")
ROOT:=$(CURDIR)
endif

ifeq ("$(BIN)","")
BIN:=bin
endif

ifeq ("$(SRC)","")
SRC:=src
endif

ifeq ("$(BUILD)","")
BUILD:=Debug
endif

ifeq ("$(NAME)","")
NAME:=PROJECT
endif

# Internal definitions

define All_Files_Inside
$(foreach file,$(wildcard $(1)/*),$(if $(wildcard $(file)/*),$(call All_Files_Inside,$(file)),$(file)))
endef

define Compile_Source
$(OBJDIR)/$(notdir $(firstword $(subst ., ,$(1)))).o: $(1) $(filter %$(notdir $(firstword $(subst ., ,$(1)))).hpp,$(call All_Files_Inside,$(SRC_FOLDER)))
	$(COMPILER) -c $(1) -o $(OBJDIR)/$(notdir $(firstword $(subst ., ,$(1)))).o $(COMPILER_FLAGS)
endef

SRC_FOLDER:=$(ROOT)/$(SRC)
BIN_FOLDER:=$(ROOT)/$(BIN)

ODIR:=$(BIN_FOLDER)/$(BUILD)
OBJDIR:=$(ODIR)/obj
EXECUTABLE:=$(ODIR)/$(NAME).exe

INCLUDE_PATH:=$(foreach path,$(INCLUDE),-I$(path))
LIBRARY_PATH:=$(foreach path,$(LIBRARY),-L$(path))
LIBS:=$(foreach name,$(LIBNAME),-l$(name))

SOURCE_FILES:=$(filter %.cpp,$(call All_Files_Inside,$(SRC_FOLDER)))
OBJECT_FILES:=$(foreach src,$(SOURCE_FILES),$(OBJDIR)/$(firstword $(subst ., ,$(notdir $(src)))).o)
DIRTY_OBJECTS=$(foreach pdo,$(wildcard $(OBJDIR)/*),$(if $(filter $(pdo),$(OBJECT_FILES)),,$(pdo))) $(filter-out $(EXECUTABLE),$(wildcard $(ODIR)/*.exe))

LINKER_FLAGS:=$(LFLAG) $(LIBRARY_PATH) $(LIBS)
COMPILER_FLAGS:=$(CFLAG) $(INCLUDE_PATH)

# Main Targets

$(EXECUTABLE): $(OBJECT_FILES)
	-$(COMPILER) $(OBJECT_FILES) -o $(EXECUTABLE) $(LINKER_FLAGS)

$(foreach src,$(SOURCE_FILES),$(eval $(call Compile_Source,$(src))))

# Utility Targets:
.PHONY: clean dir run help

# Run the executable via powershell
run: $(EXECUTABLE)
	@powershell.exe $(EXECUTABLE) $(ARG)

# Create directory for the output if it doesn't exist
dir:
	-mkdir -p $(OBJDIR)

# Clean output
clean:
	@rm $(DIRTY_OBJECTS)
	@echo Removed $(if $(foreach do,$(DIRTY_OBJECTS),'$(do)'),$(foreach do,$(DIRTY_OBJECTS),'$(do)'),nothing)

# Delete all object files and executables
reset: clean
	@rm $(wildcard $(ODIR)/.exe*)
	@rm $(wildcard $(ODIR)/*.exe)
	@rm $(wildcard $(OBJDIR)/*.o)

# Help command
help:
	@echo 'make CFG=<CFG Makfile in .make folder>'
	@echo 'make [...] run' to run program
	@echo 'make [...] dir' to create necessary directories
	@echo 'make [...] clean' to clean target build
	@echo 'make [...] reset' to delete all object files and executables in target build
