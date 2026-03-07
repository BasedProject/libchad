HELP_ME += \
"10-object.mk\n" \
"Critical makefile that provides all building and source location for C/C++.\n" \
"Provides SOURCE.orig.cxx, SOURCE.orig.c, SOURCE.orig\n" \
"Includes OBJECT.dir in CPPFLAGS\n" \
"\n"

SOURCE.orig.cxx := $(call search, cpp C c++)
SOURCE.orig.c   := $(call search, c)
SOURCE.orig := $(SOURCE.orig.c) $(SOURCE.orig.cxx)
$(call flatten,SOURCE.orig)
$(call convert,SOURCE.orig, c cpp c++ C)
OBJECT.orig += $(addprefix ${OBJECT.dir}/, ${SOURCE.orig})

CPPFLAGS += -I${OBJECT.dir}

vpath %.c   ${SEARCH.dir}
vpath %.cpp ${SEARCH.dir}
vpath %.c++ ${SEARCH.dir}
vpath %.C   ${SEARCH.dir}

# this file / 99-all.mk is designed for a single target executable object, not library generation.
# Therefore, we'll call linkage exactly once and I can avoid touching Bourne Shell.
${TARGET}: ${OBJECT.orig}
	$(call quiet_echo,LD	$@)
ifeq (${SOURCE.orig.cxx},)
	${QUIET}${LINK.c} -o "$@" $+
else
	${QUIET}${LINK.cpp} -o "$@" $+
endif

${OBJECT.dir}/%.o: %.c
	$(call quiet_echo,CC	$<)
	${QUIET}${COMPILE.c} -o $@ $<

# C++

${OBJECT.dir}/%.o: %.cpp
	$(call quiet_echo,CPP	$<)
	${QUIET}${COMPILE.cpp} -o $@ $<

${OBJECT.dir}/%.o: %.c++
	$(call quiet_echo,CPP	$<)
	${QUIET}${COMPILE.cpp} -o $@ $<

${OBJECT.dir}/%.o: %.C
	$(call quiet_echo,CPP	$<)
	${QUIET}${COMPILE.cpp} -o $@ $<
