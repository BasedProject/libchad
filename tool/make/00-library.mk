HELP_ME += \
"00-library.mk\n" \
"Provides library function.\n" \
"flatten: flattens directory structure in regards to SEARCH.dir. Slightly more confusing than notdir\n" \
"search: searches SEARCH.dir" \
"\n"

# flattens directories, i.e. source/this source/and/so/on/that -> this that, as long as those dirs are provided in SEARCH.dir
define flatten
$(foreach d,$(SEARCH.dir),$(eval $1 := $($1:$(d)/%=%)))
endef

# searches a group in all directories
define search
$(wildcard $(foreach s,$1,$(addsuffix /*.${s},${SEARCH.dir})))
endef

define convert
$(foreach s,$2,$(eval $1 := ${$1:.${s}=.o}))
endef
