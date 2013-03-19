# compiler flag (position independent code)
PLATFORM_CC_PIC_FLAG		=	-fno-common

# shared library creation flag
PLATFORM_CC_SHARED			=	-dynamic

LIBTOOL						:=	libtool

PLATFORM_LIBTOOL_LINK       :=	-dynamic

CFLAGS						+=	-D__MACOS__
