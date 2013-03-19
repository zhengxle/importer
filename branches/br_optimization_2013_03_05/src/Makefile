PROJECT_ROOT	=	$(shell cd ..; pwd)

TARGETS			+=	tairFileImporter
TARGETS			+=	libimporter.a

CLEANFILES		+=	tairFileImporter

SUBDIRS			=

INCLUDE			+=	-I/home/a/include
INCLUDE			+=	-I/home/a/include/tunion

INCLUDE			+=	-I/opt/csr/common/include/tbsys

LDFLAGS			+=	-L/home/a/lib$(ARCH_SUFFIX)
LDFLAGS			+=	-lpthread
LDFLAGS			+=	-ltunioncommon
LDFLAGS			+=	-ltuniontools
LDFLAGS			+=	-ldl

LDFLAGS			+=	-Wl,-Bdynamic


CXXFILES		+=	Config.cpp
CXXFILES		+=	Importer.cpp
CXXFILES		+=  FileHandler.cpp	
CXXFILES		+=  NormalFileHandler.cpp	
CXXFILES		+=  PbFileHandler.cpp	
CXXFILES		+=  main.cpp	

include $(PROJECT_ROOT)/common.mk

tairFileImporter: $(OBJ_DIR)/Importer.o $(OFILES) | $(BIN)
	$(CC) -o $@ $^ $(LDFLAGS) $(LLIB)
	cp $@ $(BIN)
runtest:
	make -C $(PROJECT_ROOT)/utest runtest
