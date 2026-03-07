HELP_ME += "make.mk\n" \
"Provides the structure of everything and 'MAKE.filter'. Do not touch.\n" \
"MAKE.filter filters certain makefiles from being run at all.\n" \
"makefiles should do the sysv naming thing with the prefixing numbers to ensure correct load order.\n" \
"\n"
MAKE.filter += make.mk
MAKE.filter := $(MAKE.filter:${MAKE.dir}/%=%)
MAKE.filter := $(addprefix ${MAKE.dir}/,${MAKE.filter})
-include $(filter-out ${MAKE.filter},$(wildcard ${MAKE.dir}/*.mk))
