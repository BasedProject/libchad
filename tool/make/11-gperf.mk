vpath %.gperf ${SOURCE.dir}

GPERF      ?= gperf
GPERF.orig := $(wildcard ${SOURCE.dir}/*.gperf)
GPERF.orig := $(GPERF.orig:${SOURCE.dir}/%.gperf=${OBJECT.dir}/%.h)
ALSO       += ${GPERF.orig}

${OBJECT.dir}/%.h: %.gperf
	@echo "GPERF	$<"
	@${GPERF} --null-strings -tEIH $(shell basename $(basename $<))_hash -N $(shell basename $(basename $<))_lookup < $< > $@
