HELP_ME += \
"98-all.mk\n" \
"provides all and run.\n" \
"implies ALSO. and TARGET.\n" \
"ALSO is everything literally in recipe written before (not logically) TARGET.\n" \
"use .WAIT if required.\n" \
"TARGET is your program.\n" \
"run runs TARGET with ARGS, please provide ARGS if you want those for your invocation\n"

.DEFAULT_GOAL := all

.PHONY: all
all: ${ALSO} ${TARGET}

ARGS ?=
run: ${ALSO} ${TARGET}
	./${TARGET} ${ARGS}
