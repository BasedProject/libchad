HELP_ME += \
"98-clean.mk\n" \
"Provides recursive cleaning of object/ via recipe of clean. DO NOT FUCK WITH OBJECT.dir!!!\n" \
"Not intended as omniscient reset magic bullet. Just prune potentially bad objects.\n" \
"We only care about objects and only use objects from the toplevel of OBJECT.dir, not deeper.\n" \
"\n"

.PHONY: clean
clean:
	-${RM} -r ${OBJECT.dir}/* ${TARGET}
