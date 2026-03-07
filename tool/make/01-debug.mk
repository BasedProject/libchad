HELP_ME += \
"01-debug.mk\n" \
"Provides DEBUG, when nonzero will provide debugging information.\n" \
"Provides SANITIZE, when nonzero will provide -fsantize maximally for relavant compiler.\n" \
"Note that SANITIZE isn't trying to cover all possible usages of -fsan, just the most generally useful.\n" \
"Provides VECTORIZED_ALL, when nonzero will provide complete debugging information about automatic vectorization\n" \
"Provides VECTORIZED, when nonzero will provide partial (success-only) about automatic vectorization.\n" \
"Override in command line, in GNUmakefile or inline as needbe.\n" \
"Note that GCC has better output regarding automatic vectorization.\n" \
"Adds lots of flags for CFLAGS, CPPFLAGS, CXXFLAGS, LFLAGS, YFLAGS, which should be read in source.\n" \
"In summary, we try to fast by default, and provide real, generally speedy debugging otherwise.\n" \
"You should alraedy know about NDEBUG in C, which is provided correctly.\n" \
"Compiler's respective debugger is respected automatically.\n" \
"This is not comprehensive, overwrite or write your own if you need that.\n" \
"provides DO_LTO, which is automatically disabled for libraries.\n" \
"\n"

DEBUG          ?= 0
SANITIZE       ?= 0
VECTORIZED_ALL ?= 0
VECTORIZED     ?= 0

ifneq (${SANITIZE},0)
        DEBUG := 1
endif

# don't do LTO if we're a library as that causes demonic issues with linking
ifeq ($(findstring 11-lib.mk,$(MAKE.filter)),11-lib.mk)
        DO_LTO ?= 1
else
        DO_LTO := 0
endif

ifneq (${DEBUG},0)
        LFLAGS   += --debug --trace
        YFLAGS   += --debug
        # there's gcc15 -flto-incremental
        # for clang see https://clang.llvm.org/docs/ThinLTO.html
        ifeq (${IS_CLANG},1)
                ifeq (${DO_LTO},1)
                        CFLAGS   += -flto=thin
                        CXXFLAGS += -flto=thin
                endif
                CFLAGS   += -glldb
                CXXFLAGS += -glldb
        else
                ifeq (${IS_GCC},1)
                        CFLAGS   += -pg -ggdb
                        CXXFLAGS += -pg -ggdb
                else
                        CFLAGS   += -g
                        CXXFLAGS += -g
                endif
        endif
        CFLAGS   += -fno-inline -Wall -Wextra -Wpedantic -Wshadow -Wundef -fno-omit-frame-pointer
        CXXFLAGS += -fno-inline -Wall -Wextra -Wpedantic -Wshadow -Wundef -fno-omit-frame-pointer
else
        ifeq (${DO_LTO},1)
                ifeq (${IS_GCC},1)
                        CFLAGS += -flto=auto
                        CXXFLAGS += -flto=auto
                else
                        CFLAGS   += -flto
                        CXXFLAGS += -flto
                endif
        endif
        CFLAGS   += -ftree-vectorize -march=x86-64 -mtune=generic
        CXXFLAGS += -ftree-vectorize -march=x86-64 -mtune=generic
        CPPFLAGS += -DNDEBUG
endif

ifneq (${SANITIZE},0)
        ifeq (${IS_CLANG},1)
                CFLAGS   += -fvisibility=hidden -fsanitize=address,leak,undefined,bounds
                CXXFLAGS += -fvisibility=hidden -fsanitize=address,leak,undefined,bounds
                ifeq (${PLATFORM},Linux)
                        # Didn't work on Darwin with Clang-19, assuming Linux specific.
                        CFLAGS   += -fsanitize=cfi
                        CXXFLAGS += -fsanitize=cfi
                endif
        else
                CFLAGS   += -fsanitize=address,leak,undefined
                CXXFLAGS += -fsanitize=address,leak,undefined
        endif
endif

ifneq (${VECTORIZED_ALL},0)
        ifeq (${IS_CLANG},1)
          CFLAGS   += -Rpass=loop-vectorize -Rpass-missed=loop-vectorize
          CXXFLAGS += -Rpass=loop-vectorize -Rpass-missed=loop-vectorize
        else
          CFLAGS   += -fopt-info-vec-all
          CXXFLAGS += -fopt-info-vec-all
        endif
else
        ifneq (${VECTORIZED},0)
                ifeq (${IS_CLANG},1)
                        CFLAGS   += -Rpass=loop-vectorize
                        CXXFLAGS += -Rpass=loop-vectorize
                else
                        CFLAGS   += -fopt-info-vec-optimized
                        CXXFLAGS += -fopt-info-vec-optimized
                endif
        endif
endif
