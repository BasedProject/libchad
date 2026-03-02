MAKE.filter += make.mk
MAKE.filter := $(MAKE.filter:${MAKE.dir}/%=%)
MAKE.filter := $(addprefix ${MAKE.dir}/,${MAKE.filter})
-include $(filter-out ${MAKE.filter},$(wildcard ${MAKE.dir}/*.mk))
