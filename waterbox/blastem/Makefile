CCFLAGS := -DNEW_CORE -DDISABLE_ZLIB -DM68030 -DDISABLE_NUKLEAR -DDISABLE_OPENGL -DIS_LIB \
	-Icore -Icore/musashi -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter \
	-Werror=pointer-to-int-cast -Werror=int-to-pointer-cast -Werror=implicit-function-declaration \
	-std=gnu11 -fomit-frame-pointer

TARGET := blastem.wbx

SRCS = $(shell find $(ROOT_DIR) -type f -name '*.c')

include ../common.mak
