HELP_ME += \
"11-gperf.mk\n" \
"Automatic gperf support.\n" \
"Chains in GPERF.orig.\n" \
"Provides GPERF configurable for overrides.\n" \
"\n"

GPERF      ?= gperf
GPERF.orig := $(call search, gperf)
$(call flatten, GPERF.orig)
GPERF.orig := $(addprefix ${OBJECT.dir},${GPERF.orig})
ALSO       += ${GPERF.orig}

vpath %.gperf   ${SEARCH.dir}

${OBJECT.dir}/%.h: %.gperf
	$(call quiet_echo,GPERF	$<)
	${QUIET}${GPERF} --null-strings -tEIH $(shell basename $(basename $<))_hash -N $(shell basename $(basename $<))_lookup < $< > $@
