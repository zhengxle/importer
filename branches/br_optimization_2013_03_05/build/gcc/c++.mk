# Extensions for files
CODE_EXT		=	.cpp
HEADERS_EXT		=	.h
OBJECT_EXT		=	.o

# Compiler tools
CC				=	g++
LIBTOOL			?=	g++
AR				?=	ar

# Arguments for the compiler tools
#ARGS_CC                 =	-pedantic -Wall -Wextra -Wno-variadic-macros
#ARGS_CC                 =	-Wall -Wextra -Wno-variadic-macros
ARGS_CC                 =	-Wall -Wno-variadic-macros
ARGS_LIBTOOL_COMPILE    ?=	--mode=compile
ARGS_LIBTOOL_LINK       =	$(PLATFORM_LIBTOOL_LINK)

ifdef release
	CFLAGS		+=	-ggdb -O2 -DNDEBUG
else
	CFLAGS		+=	-ggdb -O0
endif

CC_PIC_FLAG		=	$(PLATFORM_CC_PIC_FLAG)

# uncomment to debug memeory malloc problem
# CFLAGS			+=	-lefence

CFLAGS			+=	$(ARGS_CC)
