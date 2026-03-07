HELP_ME += \
"11-bison.mk\n" \
"Builds lex/yacc files automatically.\n" \
"Chains in SOURCE.gen for generated source from Flex/Bison.\n" \
"\n"

SOURCE.gen := $(call search, yy.c tab.c)
$(call flatten,SOURCE.orig)
SOURCE.gen := $(addprefix ${OBJECT.dir}/,${SOURCE.gen})
SOURCE.gen := ${SOURCE.gen:.yy.c=.yy.o}
SOURCE.gen := ${SOURCE.gen:.tab.c=.tab.o}
ALSO += ${SOURCE.gen}

vpath %.l ${SEARCH.d}
vpath %.y ${SEARCH.d}
vpath %.yy.c ${OBJECT.d}
vpath %.tab.c ${OBJECT.d}

%.yy.c: %.l
	flex -o ${OBJECT.d}/$@ --header=${OBJECT.d}/$(subst .c,.h,$@) $?

%.tab.c: %.y
	bison -o ${OBJECT.d}/$@ --header=${OBJECT.d}/$(subst .c,.h,$@) $?

%.yy.o: %.yy.c
	${COMPILE.c} ${LFLAGS} -o ${OBJECT.d}/$@ ${OBJECT.d}/$<

%.tab.o: %.tab.c
	${COMPILE.c} ${YFLAGS} -o ${OBJECT.d}/$@ ${OBJECT.d}/$<
