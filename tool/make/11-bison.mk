SOURCE.gen := $(wildcard ${SOURCE.dir}/*.yy.c ${SOURCE.dir}/*.tab.c)
SOURCE.gen := $(SOURCE.gen:${SOURCE.dir}/%=%)
SOURCE.gen := ${SOURCE.gen:.yy.c=.yy.o}
SOURCE.gen := ${SOURCE.gen:.tab.c=.tab.o}
ALSO += ${SOURCE.gen}

vpath %.l ${SOURCE.d}
vpath %.y ${SOURCE.d}
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
