CFLAGS := -std=c23 -fPIC
CPPFLAGS := -Ichad
SOURCE.orig := $(wildcard extern/*.c)
SOURCE := $(SOURCE.orig:extern/%=%)
OBJECT := $(addprefix object/,$(SOURCE:.c=.o))

vpath %.c extern

object/%.o: %.c
	@echo "CC	$<"
	@${COMPILE.c} -o $@ $<

.PHONY: all
all: object/libchad.a object/libchad.so

object/libchad.a: ${OBJECT}
	@echo "AR	$<"
	@ar rcs $@ $+

object/libchad.so: ${OBJECT}
	@echo "SO	$<"
	@${CC} ${CFLAGS} ${CPPFLAGS} -shared $+ -o $@

dist:
	-mkdir object/chad/ 2> /dev/null
	for d in chad/ extern/; do \
		pushd $$d &> /dev/null; \
		find ./ -type f -name '*.h' -exec cp --parents {} ../object/chad/ \; ; \
		popd &> /dev/null; \
	done

clean:
	-rm -frfr object/*
