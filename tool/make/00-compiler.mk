HELP_ME += \
"00-compiler.mk\n" \
"LD will be automatically set to mold if possible. override LD from ld or set USE_MOLD to 0.\n" \
"CC will be automatically set to gcc if PREFER_GCC=1 is set. Otherwise Clang, or error.\n" \
"May be overwritten. If either compiler missing, will default to the other regardless of preference.\n" \
"Overwritten will always be taken as priority.\n" \
"CC defines CXX if it is a known good compiler\n" \
"(EXACTLY gcc or EXACTLY clang, this is not comprehensive or investigative.)\n" \
"This file provides the state IS_GCC and IS_CLANG, which will both be set accordingly.\n" \
"\n"

USE_MOLD ?= 1
ifeq (${LD}${USE_MOLD},ld1)
        ifneq ($(shell which mold 2> /dev/null),)
                LDFLAGS += -fuse-ld=mold
                LD := mold
        endif
endif

# If CC is set, we'll assume the respective compiler collection.

ifeq (${CC},cc)
        ifneq ($(shell which gcc 2> /dev/null),)
                ifneq (${PREFER_GCC},0)
                        CC := gcc
                endif
        endif
        ifneq ($(shell which clang 2> /dev/null),)
                ifeq (${CC},cc)
                        CC := clang
                endif
        endif
        ifeq (${CC},cc)
                $(error GCC & Clang not available.)
        endif
endif

# this can be flexible, however that would imply including
# the gmsl and I have got this far without that,
# so I will just leave this for trivial cases.

ifeq (${CC},gcc)
        CXX := g++
endif

ifeq (${CC},clang)
        CXX := clang++
endif

ifneq ($(findstring clang, $(CC)),)
IS_CLANG := 1
else
IS_CLANG := 0
endif

ifneq ($(findstring gcc, $(CC)),)
IS_GCC := 1
else
IS_GCC := 0
endif
