TARGETS			+=	$(CXXFILES:%.cpp=%)
TARGETS			+=	unittest

CFLAGS			+= -fno-access-control
CXXFILES        +=  TestImporter.cpp
CXXFILES        +=  TestNormalFileHandler.cpp
CXXFILES        +=  TestPbFileHandler.cpp
CXXFILES        +=  TestConfig.cpp

include ../common.mk

# static links
LDFLAGS			+=	-limporter
LDFLAGS			+=	-lperson

# dynamic links
LDFLAGS			+=	-Wl,-Bdynamic
LDFLAGS			+=	-levent_core
LDFLAGS			+=	-levent_extra
LDFLAGS			+=  -lprotobuf
LDFLAGS			+=	-L/opt/csr/common/lib
LDFLAGS			+=	-L/home/a/lib$(ARCH_SUFFIX)
LDFLAGS			+=	-L/home/a/lib
LDFLAGS			+=	-L./tools/

LDFLAGS			+=	-lpthread
LDFLAGS			+=	-ldl
LDFLAGS			+=	-lz
LDFLAGS			+=	-L/usr/lib64/gtest -lgtest
LDFLAGS			+=	-L/usr/lib64/gmock -lgmock
LDFLAGS			+=	-liconv
LDFLAGS			+=	-ltunioncommon
LDFLAGS			+=	-ltuniontools
LDFLAGS			+=	-ltbnet
LDFLAGS			+=	-ltbsys
LDFLAGS			+=	-ltxp_common

CFLAGS			+=	-I/home/a/include/tunion

CFLAGS			+=	-I/home/a/include/tunion/tools
CFLAGS			+=	-I/home/a/share/
CFLAGS			+=	-I/opt/csr/tair-2.3/include
CFLAGS			+=	-I/opt/csr/common/include/tbsys
CFLAGS			+=	-I/opt/csr/common/include/tbnet
CFLAGS			+=	-I/usr/include

CLEAN_LIST		+=	html

.PHONY: runtest
runtest: unittest
	@export LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(LIB):/usr/lib64/gtest && \
		./unittest || true

Test%: $(OBJ_DIR)/Test%.o $(OBJ_DIR)/main.o
	$(CC) -o $@ $^ $(LLIB) $(LDFLAGS)

.NOTPARALLEL: unittest
unittest: $(OBJ_DIR)/main.o $(OFILES)
	$(CC) -o $@ $^ $(LLIB) $(LDFLAGS)

