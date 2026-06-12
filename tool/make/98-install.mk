HELP_ME += \
"98-install.mk\n" \
"\n"

PREFIX ?= /usr/local
MANPREFIX ?= ${PREFIX}/share/man

.PHONY: install
install: chad | ${LIBTARGET}.a ${LIBTARGET}.so
	mkdir -p ${DESTDIR}${PREFIX}/include ${DESTDIR}${PREFIX}/lib
	cp -f chad/terry.h ${DESTDIR}${PREFIX}/include
	cp -f chad.h ${DESTDIR}${PREFIX}/include
	cp -rf $^ ${DESTDIR}${PREFIX}/include
	cp -f $| ${DESTDIR}${PREFIX}/lib
	ldconfig
