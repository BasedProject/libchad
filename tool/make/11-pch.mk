# This header at this moment does nothing.

# I was under the impression that pch would flattenable. However this setup is invalid.
#  You either need to manhandle the compiler (every include needs to be in command line)
#   OR have thing be inlined in the source tree (not happening.)

HELP_ME += \
"11-pch.mk\n" \
"Disabled. Do not use. Currently in disposed due to how GCC/Clang load PCH files.\n" \
"Also note that most developers are bad people and don't really think about this.\n" \
"COULD be rewritten to inline .pch'd files into source, however this breaks the universal fundamental law of not shitting on the dining table.\n" \
"\n"

ifeq (1,)

HEADER.pch.filter ?=
HEADER.orig.cxx := $(wildcard ${SOURCE.dir}/*.H ${OBJECT.dir}/*.H ${SOURCE.dir}/*.hpp ${OBJECT.dir}/*.hpp ${SOURCE.dir}/*.h++ ${OBJECT.dir}/*.h++)
HEADER.orig.c   := $(wildcard ${SOURCE.dir}/*.h ${OBJECT.dir}/*.h)
HEADER.orig := $(filter-out ${HEADER.pch.filter},${HEADER.orig.c} ${HEADER.orig.cxx})
HEADER.orig := $(HEADER.orig:${SOURCE.dir}/%=%)
HEADER.orig := $(HEADER.orig:${OBJECT.dir}/%=%)

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

# C++

${OBJECT.dir}/%.H.pch: %.H
	@echo "PCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

${OBJECT.dir}/%.H.gch: %.H
	@echo "GCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

${OBJECT.dir}/%.hpp.pch: %.hpp
	@echo "PCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

${OBJECT.dir}/%.hpp.gch: %.hpp
	@echo "GCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

${OBJECT.dir}/%.h++.pch: %.h++
	@echo "PCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

${OBJECT.dir}/%.h++.gch: %.h++
	@echo "GCH	$<"
	@${COMPILE.cpp} ${PCHFLAGS} -x c++-header -o $@ $<

endif
