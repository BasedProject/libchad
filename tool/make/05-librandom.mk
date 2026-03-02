LIBRANDOM.source.c := $(filter-out ${LIBRARY.dir}/librandom/source/main.c,$(wildcard ${LIBRARY.dir}/librandom/source/*.c))
LIBRANDOM.source.h := $(wildcard ${LIBRARY.dir}/librandom/source/*.h)
LIBRANDOM.orig := $(LIBRANDOM.source.c) $(LIBRANDOM.source.h)
LIBRANDOM.orig := $(addprefix ${SOURCE.dir}/random/,$(LIBRANDOM.orig:${LIBRARY.dir}/librandom/source/%=%))
LIBRANDOM.object := $(notdir $(LIBRANDOM.source.c))
LIBRANDOM.object := $(addprefix ${OBJECT.dir}/,$(LIBRANDOM.object:.c=.o))

vpath %.c ${SOURCE.dir}/random

${SOURCE.dir}/random/%.c: ${LIBRARY.dir}/librandom/source/%.c ; @cp $< $@
${SOURCE.dir}/random/%.h: ${LIBRARY.dir}/librandom/source/%.h ; @cp $< $@

ALSO += ${LIBRANDOM.orig} ${LIBRANDOM.object}
