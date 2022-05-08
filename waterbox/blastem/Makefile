CCFLAGS := -DDISABLE_ZLIB -DM68000 -DDISABLE_NUKLEAR -DDISABLE_OPENGL -DIS_LIB -DX86_64 -m64 \
	-Icore -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-missing-field-initializers \
	-Wno-unused-function -Wno-sign-compare -Wno-implicit-fallthrough -Wno-unused-value -Wno-parentheses \
	-Wno-unused-label -Wno-type-limits -Wno-unused-but-set-variable -Wno-pointer-sign -Wno-switch -Wno-maybe-uninitialized \
	-Werror=pointer-to-int-cast -Werror=int-to-pointer-cast -Werror=implicit-function-declaration \
	-std=gnu11 -fomit-frame-pointer

TARGET := blastem.wbx

SRCS = $(shell find $(ROOT_DIR) -type f -name '*.c')

include ../common.mak
