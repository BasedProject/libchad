ifneq (${DEBUG},1)
        CFLAGS   += -fstack-protector-strong
        CXXFLAGS += -fstack-protector-strong
        ifneq (${PLATFORM},Mac)
                CFLAGS   += -fstack-clash-protection
                CXXFLAGS += -fstack-clash-protection
                ifeq (${IS_GCC},1)
                        CFLAGS   += -fPIC -fpic
                        CXXFLAGS += -fPIC -fpic
                else
                        CFLAGS   += -fPIC
                        CXXFLAGS += -fPIC
                endif
                LDFLAGS  += -Wl,-z,relro,-z,now
        endif
        CPPFLAGS += -D_FORTIFY_SOURCE=3
endif
