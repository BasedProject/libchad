ifeq (${LD},ld)
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
