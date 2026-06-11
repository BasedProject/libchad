LIBRARY.install := $(addprefix ${SOURCE.dir}/,$(notdir ${LIBRARY.orig})) $(addprefix ${SOURCE.dir}/experimental/,$(notdir ${LIBRARY.experimental}))

define copier
$(2)$(notdir $(1)): ${LIBRARY.dir}/$(1) ; cp $$< $$@
endef

ifeq (${HAS_PERU},1)
$(foreach f,${LIBRARY.orig},$(eval $(call copier,$f,${SOURCE.dir}/)))
$(foreach f,${LIBRARY.experimental},$(eval $(call copier,$f,${SOURCE.dir}/experimental/)))
endif

ALSO += ${LIBRARY.install}
