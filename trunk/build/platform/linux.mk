# compiler flag (position independent code)
PLATFORM_CC_PIC_FLAG		=	-fPIC

# shared library creation flag
PLATFORM_CC_SHARED			=	-shared

LIBTOOL						=	$(CC)

AR							:=	ar

CFLAGS						+=	-D__LINUX__

INCLUDE						+=	-I/home/a/include
LDFLAGS						+=	-L/home/a/lib
LDFLAGS						+=	-L/home/a/lib64
