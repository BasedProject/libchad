SOURCE.orig.c := $(wildcard $(addsuffix /*.c, ${SEARCH.dir}))
SOURCE.orig := $(notdir ${SOURCE.orig.c})
SOURCE.orig := ${SOURCE.orig:.c=.o}
OBJECT.orig += $(addprefix ${OBJECT.dir}/, ${SOURCE.orig})

CPPFLAGS += -I${OBJECT.dir}

vpath %.c ${SOURCE.dir}
vpath %.c ${SOURCE.dir}/experimental

# this file / 99-all.mk is designed for a single target executable object, not library generation.
# Therefore, we'll call linkage exactly once and I can avoid touching Bourne Shell.
${TARGET}: ${OBJECT.dir}/${LIBTARGET}.a ${OBJECT.dir}/main.o
	@echo "LD	$@"
	@${LINK.c} -o "$@" $+

${OBJECT.dir}/%.o: %.c
	@echo "CC	$<"
	@${COMPILE.c} -o $@ $<
