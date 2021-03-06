# platform_sunos5_kcc.GNU,v 4.5 2000/02/14 18:57:00 oci Exp  -*- Makefile -*-

# SunOS 5.x (Solaris 2.x) with KAI C++ 3.3e, *not* using Orbix.
#

debug = 1
distrib = 0
threads = 1
exceptions = 1

ifeq ($(threads),1)
  CFLAGS += --thread_safe
  LDFLAGS += --thread_safe
  ARFLAGS = --thread_safe
else
  ARFLAGS =
  CCFLAGS += -DPDL_HAS_THREADS=0
endif # threads

CC              = KCC
CXX             = KCC

DCFLAGS         += +K0 -g
CDLD            = $(CC)
DLD             = $(CXX)
LD              = $(CXX)

ifdef exceptions
  ifneq ($exceptions,0)
    CCFLAGS += --exceptions
  endif # ! exceptions
else
  CCFLAGS   += --no_exceptions
  LDFLAGS   += --no_exceptions
endif



LIBS        += -Bdynamic -lsocket -lnsl -lgen -ldl -lposix4
MATHLIB	     = -lm
CPPFLAGS    += $(CFLAGS)
OCFLAGS     += +K3 -o $(added_optimizer_flag)
APIC         = -K PIC
PIC          = -KPIC
AR           = KCC
ARFLAGS     += -Bstatic -o
RANLIB       = echo
SOFLAGS      = -G $(CPPFLAGS)


ifdef static_libs_only
  ifneq ($(static_libs_only),0)
    static_libs=1
  endif
endif
# Kind of a hack since LDFLAGS is used for both non-static
# library generation and binary generation.  LD is only used for
# binary generation.
ifneq ($(static_libs),0)
  CCFLAGS   += --one_instantiation_per_object
  LD        += -Bstatic
  #
  # If we want static libs, we must put -Bstatic it at the end of
  # the library list.  This insures that the KCC libraries
  # are linked in statically.
  #
  LIBS      += -Bstatic
endif



#### Create template repository to avoid compiler warning.
TEMPLATE_REPOSITORY = Templates.DB

ifdef BIN
  #### Builds .shobj/$*.o file, then .shobj/$*.so file.  The .o files
  #### are used for building libraries and executables.  But, it seems
  #### to be necessary to build the .so files (with -G) in order to get
  #### all template instantiations.
  SOBUILD = $(COMPILE.cc) $(PIC) -o $(VSHDIR)$*.o $<; \
            $(SOLINK.cc) -o $@ -h $@ $(LDFLAGS) $(VSHDIR)$*.o
else
  #### Optimize builds when no executables are built in the current
  #### directory.  Only a library is being created, and -G is used
  #### in that step.  Therefore, all templates instantations are
  #### included in the library.  This optimization saves almost 11 Mb
  #### (2.6 percent) and 27 minutes (22 percent) on the entire PDL
  #### build on a 168 MHz Sun Ultra2.
  ####
  #### Sun C++ won't allow the output from a compile to be named with
  #### a .so extension.  Rather than muck with the PDL build rules and
  #### risk upsetting builds on other platforms, just ln the output
  #### after building it.
  SOBUILD = $(RM) $@; $(COMPILE.cc) $(PIC) -o $(VSHDIR)$*.o $< && \
                      /bin/ln $(VSHDIR)$*.o $@
endif # BIN

#### The following macro overrides enable creation of fast executables.
#### They _don't_ support fast compilation :-)
#### To use, add fast=1 to your "make" invocation.
####
#### -g is incompatible with -fast.  If you need -g, you can
#### use "-fast -O3".
####
ifdef fast
  CFLAGS += -fast +K3
  DCFLAGS =
  LDFLAGS += -fast +K3
endif # fast
