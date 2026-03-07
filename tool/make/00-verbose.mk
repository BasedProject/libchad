HELP_ME += \
"00-verbose.mk\n" \
"Sets VERBOSE. Regarding a bug: VERBOSE can't be set in GNUmakefile.\n" \
"VERBOSE must only be used in command line or outright defined in file.\n" \
"QUIET is provided for optional QUIET things that can be revoked with enabled VERBOSE.\n" \
"usage is dollar{QUIET}dollar{LINK.cpp} -o \"dollar@\" dollar+\n" \
"macro quiet_echo is provided for statements like 'CC\tsome_file.c'\n" \
"Usage is dollar(call quiet_echo,CC	dollar<)\n" \
"\n"

VERBOSE ?= 0

quiet_echo = $(if $(filter 0,$(VERBOSE)),@echo "$(1)")
QUIET := @
ifneq (${VERBOSE},0)
QUIET :=
endif
