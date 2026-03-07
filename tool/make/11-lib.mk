HELP_ME += \
"11-lib.mk\n" \
"Disabled by default. Provides building for libraries.\n" \
"Provides NOT_APART_OF_LIBRARY & LIBTARGET configurables.\n" \
"NOT_APART_OF_LIBRARY is a semi-flexible configuarable for things that aren't apart of the library,\n" \
"should automatically resolve correctly for C/C++ files. ALWAYS DOUBLE CHECK. DON'T BE RETARDED.\n" \
"LIBTARGET is the output name, literally should be something like\n" \
"'librandom' or 'libchad'.\n" \
"Chains in library construction (.a, .so).\n" \
"\n"

$(call flatten, NOT_APART_OF_LIBRARY)
NOT_APART_OF_LIBRARY := $(NOT_APART_OF_LIBRARY:${OBJECT.dir}/%=%)
NOT_APART_OF_LIBRARY := $(addprefix ${OBJECT.dir}/,${NOT_APART_OF_LIBRARY})
NOT_APART_OF_LIBRARY := $(NOT_APART_OF_LIBRARY:.c=.o)
NOT_APART_OF_LIBRARY := $(NOT_APART_OF_LIBRARY:.cpp=.o)
NOT_APART_OF_LIBRARY := $(NOT_APART_OF_LIBRARY:.c++=.o) # milage may vary
NOT_APART_OF_LIBRARY := $(NOT_APART_OF_LIBRARY:.C=.o)
OBJECT.lib := $(filter-out ${NOT_APART_OF_LIBRARY},${OBJECT.orig})

LIBTARGET ?= lib$(basename $(TARGET))

${OBJECT.dir}/${LIBTARGET}.a: ${OBJECT.lib}
	$(call quiet_echo,AR	$@)
	${QUIET}ar rcs -o "$@" $+

${OBJECT.dir}/${LIBTARGET}.so: ${OBJECT.lib}
	$(call quiet_echo,SO	$@)
ifeq (${SOURCE.orig.cxx},)
	${QUIET}${LINK.c} -shared -o "$@" $+
else
	${QUIET}${LINK.cpp} -shared -o "$@" $+
endif

ALSO += ${OBJECT.dir}/${LIBTARGET}.a ${OBJECT.dir}/${LIBTARGET}.so
