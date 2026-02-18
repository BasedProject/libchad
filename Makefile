CFLAGS := -std=c23
SOURCE := $(wildcard chad/*.c extern/*.c)

so:
	${CC} ${CFLAGS} -fPIC -shared ${SOURCE} -o object/libchad.so

dist:
	-mkdir object/chad/ 2> /dev/null
	for d in chad/ extern/; do \
		pushd $$d &> /dev/null; \
		find ./ -type f -name '*.h' -exec cp --parents {} ../object/chad/ \; ; \
		popd &> /dev/null; \
	done

clean:
	-rm -frfr object/*
