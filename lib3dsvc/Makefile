CXX = g++

CFLAGS = -Wall -Wextra -O3 -flto -fvisibility=internal -fPIC -fno-strict-aliasing \
	-Wfatal-errors -Wno-unused-value -Wno-sign-compare -Wno-implicit-fallthrough \
	-Wno-parentheses -Wno-conversion-null -Wno-maybe-uninitialized \
	-DTRL_EMUTYPE=TRL_EMUCORE_ROMTYPE_CGB -DTRL_PLATFORM_PC

LFLAGS = -s -shared

SRCS = $(wildcard CGB/*.cpp) cinterface.cpp newstate.cpp trlHeader.cpp blip_buf.c

ifeq ($(OS),Windows_NT)
EXT = dll
else
EXT = so
endif

all: lib3dsvc

lib3dsvc: $(SRCS)
	$(CXX) $(CFLAGS) $(SRCS) -o lib3dsvc.$(EXT) $(LFLAGS)