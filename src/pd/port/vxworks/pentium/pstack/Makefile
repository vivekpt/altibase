# Makefile generated by the project manager
#


## core information

PRJ_FILE       = pstack.wpj
ifeq ($(wildcard Makefile),)
PRJ_DIR        = ..
else
PRJ_DIR        = .
endif
PRJ_TYPE       = vxApp
PRJ_OBJS       = pstack.o
BUILD_SPEC     = PENTIUMgnu
TGT_DIR        = $(WIND_BASE)/target




## build-configuration info

ifeq ($(BUILD_SPEC),PENTIUMgnu)
CPU              = PENTIUM
TOOL             = gnu
TOOL_FAMILY      = gnu
DEFAULT_RULE     = pstack.out
endif

include $(TGT_DIR)/h/make/defs.project

## build-configuration info

ifeq ($(BUILD_SPEC),PENTIUMgnu)
AR               = arpentium
AS               = ccpentium
CC               = ccpentium
CC_ARCH_SPEC     = -mcpu=pentium -march=pentium
CFLAGS           = -g -mcpu=pentium -march=pentium -ansi -nostdlib -fno-builtin -fno-defer-pop -I. -I$(WIND_BASE)/target/h/ -DCPU=PENTIUM -DTOOL_FAMILY=gnu -DTOOL=gnu
CFLAGS_AS        = -g -mcpu=pentium -march=pentium -ansi -nostdlib -fno-builtin -fno-defer-pop -P -xassembler-with-cpp -I. -I$(WIND_BASE)/target/h/ -DCPU=PENTIUM -DTOOL_FAMILY=gnu -DTOOL=gnu
CPP              = ccpentium -E -P
LD               = ldpentium
LDFLAGS          = -X -N
LD_PARTIAL       = ccpentium -r -nostdlib -Wl,-X
LD_PARTIAL_FLAGS = -X -r
NM               = nmpentium -g
OPTION_DEFINE_MACRO = -D
OPTION_DEPEND    = -M -w
OPTION_GENERATE_DEPENDENCY_FILE = -MD
OPTION_INCLUDE_DIR = -I
OPTION_LANG_C    = -xc
OPTION_UNDEFINE_MACRO = -U
SIZE             = sizepentium
TOOL_FAMILY      = gnu
POST_BUILD_RULE  = 
PRJ_LIBS         = 
endif

# override make definitions only below this line


# override make definitions only above this line
include $(TGT_DIR)/h/make/rules.project



## build-configuration info

ifeq ($(BUILD_SPEC),PENTIUMgnu)
pstack.o:
	$(CC) -g -mcpu=pentium -march=pentium -ansi -nostdlib -fno-builtin -fno-defer-pop -I. -I$(WIND_BASE)/target/h/ -DCPU=PENTIUM -DTOOL_FAMILY=gnu -DTOOL=gnu -c $(PRJ_DIR)/pstack.cpp
endif


## dependencies

pstack.o: $(PRJ_DIR)/pstack.cpp \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/i586-wrs-vxworks/2.9-PentiumIII-010221/include/stddef.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/i586-wrs-vxworks/2.9-PentiumIII-010221/include/stdarg.h


## user defined rules

