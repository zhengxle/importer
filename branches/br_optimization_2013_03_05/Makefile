PROJECT_ROOT   	= 	$(shell cd .; pwd)

SUBDIRS        	= 	src

CLEANDIRS		+=	$(PROJECT_ROOT)/include/athena
CLEANDIRS		+=	$(PROJECT_ROOT)/logs
CLEANFILES		+=	$(PROJECT_ROOT)/libs/*.a
CLEANFILES		+=	$(PROJECT_ROOT)/libs/*.so

include common.mk

runtest:
	make -C $(PROJECT_ROOT)/src $(OPTIONS);
	make -C $(PROJECT_ROOT)/utest runtest $(OPTIONS);
