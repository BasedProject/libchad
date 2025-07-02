SOURCE := $(wildcard chad/*.c extern/*.c)

so:
	${CC} -fPIC -shared ${SOURCE} -o object/libchad.so

dist:
	-mkdir object/chad/
	for d in chad/ extern/; do \
		pushd $$d; \
		find ./ -type f -name '*.h' -exec cp --parents {} ../object/chad/ \; ; \
		popd; \
	done

clean:
	-rm -frfr object/*
