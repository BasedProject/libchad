HELP_ME += \
"01-depend.mk\n" \
"Automatically generates header dependencies for C/C++.\n" \
"Modifies CFLAGS & CXXFLAGS.\n" \
"Provides DEPEND, which includes all .d files in object.\n" \
"\n"

# CFLAGS   += -MMD -MP
# CXXFLAGS += -MMD -MP
# DEPEND := $(wildcard ${OBJECT.dir}/*.d)
# -include ${DEPEND}
