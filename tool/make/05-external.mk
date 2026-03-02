LIBRARY.orig := dictate/dictate.c dictate/dictate.h qx/qx.h kvec/hvec.h kvec/hlist.h \
                remove_all/remove_all.h sds/sds.c sds/sds.h sds/sdsalloc.h \
                strlist/strlist.h slurp/slurp.h libini/ini_file.c libini/ini_file.h
LIBRARY.install := $(addprefix ${SOURCE.dir}/,$(notdir ${LIBRARY.orig}))

define copier
${SOURCE.dir}/$(notdir $(1)): ${LIBRARY.dir}/$(1) ; @cp $$< $$@
endef

$(foreach f,${LIBRARY.orig},$(eval $(call copier,$f)))

ALSO += ${LIBRARY.install}
