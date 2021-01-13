
COMPILER:=x86_64-w64-mingw32-g++-posix
ROOT:=$(CURDIR)
BIN:=bin
SRC:=src
BUILD:=Debug
NAME:=Project

INCLUDE:=\
$(ROOT)/$(SRC) \
$(ROOT)/vendor/SDL2/include \

LIBRARY:=\
$(ROOT)/vendor/SDL2/lib \

LIBNAME:=\
SDL2 SDL2_image SDL2_mixer SDL2_ttf

LFLAG:=\

CFLAG:=\
-std=gnu++17 \
-D_DEBUG \
-Wall -Wpedantic -Werror -Og \
-Wno-error=unknown-pragmas \

