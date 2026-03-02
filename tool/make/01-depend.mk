CFLAGS   += -MMD -MP
CXXFLAGS += -MMD -MP
DEPEND := $(wildcard ${OBJECT.dir}/*.d)
-include ${DEPEND}
