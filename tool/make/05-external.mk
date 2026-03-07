LIBRARY.orig := dictate/dictate.c dictate/dictate.h qx/qx.h \
                remove_all/remove_all.h sds/sds.c sds/sds.h sds/sdsalloc.h \
                strlist/strlist.h slurp/slurp.h libini/ini_file.c libini/ini_file.h
LIBRARY.experimental := kvec/hvec.h kvec/hlist.h
LIBRARY.install := $(addprefix ${SOURCE.dir}/,$(notdir ${LIBRARY.orig})) $(addprefix ${SOURCE.dir}/experimental/,$(notdir ${LIBRARY.experimental}))

define copier
$(2)$(notdir $(1)): ${LIBRARY.dir}/$(1) ; @cp $$< $$@
endef

ifeq (${HAS_PERU},1)
$(foreach f,${LIBRARY.orig},$(eval $(call copier,$f,${SOURCE.dir}/)))
$(foreach f,${LIBRARY.experimental},$(eval $(call copier,$f,${SOURCE.dir}/experimental/)))
endif

ALSO += ${LIBRARY.install}
