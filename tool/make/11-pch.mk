# This header at this moment does nothing.

# I was under the impression that pch would flattenable. However this setup is invalid.
#  You either need to manhandle the compiler (every include needs to be in command line)
#   OR have thing be inlined in the source tree (not happening.)

ifeq (1,)
HEADER.pch.filter ?=
HEADER.orig.c := $(wildcard $(addsuffix /*.h, ${SEARCH.dir}))
HEADER.orig := $(filter-out ${HEADER.pch.filter},${HEADER.orig.c} ${HEADER.orig.cxx})
HEADER.orig := $(notdir ${HEADER.orig})

HEADER.pch := $(addprefix ${OBJECT.dir}/, ${HEADER.orig})

ifeq (${IS_GCC},1)
        HEADER.pch := $(addsuffix .gch,${HEADER.pch})
else
        HEADER.pch := $(addsuffix .pch,${HEADER.pch})
endif

ALSO       += ${HEADER.pch}

vpath %.h ${SOURCE.dir} ${OBJECT.dir}

${OBJECT.dir}/%.h.pch: %.h
	@echo "PCH	$<"
	@${COMPILE.c} ${PCHFLAGS} -x c-header -o $@ $<

${OBJECT.dir}/%.h.gch: %.h
	@echo "GCH	$<"
	@${COMPILE.c} ${PCHFLAGS} -x c-header -o $@ $<
endif
