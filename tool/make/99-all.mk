.DEFAULT_GOAL := all

.PHONY: all
all: ${ALSO} ${TARGET}

ARGS ?=
run: ${ALSO} ${TARGET}
	./${TARGET} ${ARGS}
