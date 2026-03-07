HELP_ME := \
"<<< Skelemake 9001 Definitely Helpful Information (DHI) >>>\n\n" \
"This is a biotechnical build something or other meant to do everything all of the time.\n" \
"We provide a few important general concepts:\n" \
"We define variables inline with ?= if they are externally configurable (i.e. command line, GNUmakefile, inline)\n" \
"Generally it's preferable to modify GNUmakefile or create a new file and exempt eclipsed makefiles with 'MAKE.filter'.\n" \
"For writing these files a few chains are used for ultimate definitions.\n" \
"ALSO: which are targets to made alongside the real TARGET\n" \
"(placed before TARGET however make is usually ran in parallel and by defition\n" \
"should always permit this, however your milage may vary depending on your ability.)\n" \
"You may use the .WAIT feature to turn this into a well-defined staged build.\n" \
"HELP_ME is a chained variable meant to define this command, and each file should contribute to it.\n" \
"We prefer isolation of all generetade files, no makefile should modify the SOURCE.dir." \
"Keep source flat.\n" \
"You can change this behaviour with a new file and vpath, obviously, see BasedProject/libchad 10-object.mk for an example.\n" \
"All filenames have optional, assumed prefixes, i.e. source/object, this is the primary benefit of this skelington.\n" \
"Use SEARCH.dir, which is critical for source/object-wise subdirectories.\n" \
"\n\n" \
${HELP_ME}

.PHONY: help
help:
	@echo ${HELP_ME}
