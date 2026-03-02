DEBUG          ?= 0
SANITIZE       ?= 0
VECTORIZED_ALL ?= 0
VECTORIZED     ?= 0

ifneq (${SANITIZE},0)
        DEBUG := 1
endif

ifneq (${DEBUG},0)
        LFLAGS   += --debug --trace
        YFLAGS   += --debug
        # there's gcc15 -flto-incremental
        # for clang see https://clang.llvm.org/docs/ThinLTO.html
        ifeq (${IS_CLANG},1)
                CFLAGS   += -flto=thin -glldb
                CXXFLAGS += -flto=thin -glldb
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
        ifeq (${IS_GCC},1)
                CFLAGS += -flto=auto
                CXXFLAGS += -flto=auto
        else
                CFLAGS   += -flto
                CXXFLAGS += -flto
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
