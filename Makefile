CFLAGS := -std=c23 -fPIC
CPPFLAGS := -I. -D_XOPEN_SOURCE=500
SOURCE.orig := $(wildcard extern/*.c chad/*.c chad/experimental/*.c)
SOURCE.orig := $(SOURCE.orig:extern/%=%)
SOURCE.orig := $(SOURCE.orig:chad/experimental/%=%)
SOURCE.orig := $(SOURCE.orig:chad/%=%)
OBJECT := $(addprefix object/,$(SOURCE.orig:.c=.o))

DEBUG ?= 0
ifeq (${DEBUG},1)
        CFLAGS   += -O2 -ggdb -fno-inline -Wall -Wextra -Wpedantic -Wshadow -Wundef -fno-omit-frame-pointer
else
        CFLAGS   += -O2 -ftree-vectorize -march=x86-64 -mtune=generic -ftrivial-auto-var-init=zero -fPIC -fstack-protector-strong -fstack-clash-protection
        CPPFLAGS += -DNDEBUG -D_FORTIFY_SOURCE=3
endif

ifneq (${DEBUG},1)
endif

vpath %.c extern
vpath %.c chad
vpath %.c chad/experimental

object/%.o: %.c
	@echo "CC	$<"
	@${COMPILE.c} -o $@ $<

.PHONY: all
all: object/libchad.a object/libchad.so

object/libchad.a: ${OBJECT}
	@echo "AR	$+"
	@ar rcs $@ $+

object/libchad.so: ${OBJECT}
	@echo "SO	$+"
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
