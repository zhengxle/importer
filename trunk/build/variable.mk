TARGETS		?=
CODE		?=	C++

OPTIONS		+=

LIB			=	$(PROJECT_ROOT)/lib
INC			=	$(PROJECT_ROOT)/include
BIN			=	$(PROJECT_ROOT)/bin
OBJ_DIR		=	.obj
SOBJ_DIR	=	.sharedobj
TOBJ_DIR	=	.testobj

MKDIRS		+=	$(OBJ_DIR) $(SOBJ_DIR) $(TOBJ_DIR) $(LIB) $(INC)

PROCESSOR	=	$(shell uname -m)
ARCH_SUFFIX	=
ifeq ($(PROCESSOR), x86_64)
	ARCH_SUFFIX	=	64
else
	ARCH_SUFFIX	=
endif

PLATFORM	=	$(shell uname -s|tr A-Z a-z)
ifeq ($(PLATFORM), darwin)
	SHARED_LIB_EXT	=	.dylib
	STATIC_LIB_EXT	=	.a
	SYS_FLAG		=	-D_MACOS_
endif
SHARED_LIB_EXT	?=	.so
STATIC_LIB_EXT	?=	.a
SYS_FLAG		?=	-D_LINUX_
