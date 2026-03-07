HELP_ME += \
"02-search.mk\n" \
"Provides SEARCH.object, recipes thereof, and chains.\n" \
"\n"


SEARCH.object := ${addprefix ${OBJECT.dir}/,${SEARCH.dir:${SOURCE.dir}/%=%}}
ALSO += ${SEARCH.object}

${SEARCH.object}:
	@mkdir -p $@

${OBJECT.orig}: ${SEARCH.object}
