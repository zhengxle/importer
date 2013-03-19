PROJECT_ROOT	:=	$(shell cd $(dir $(lastword $(MAKEFILE_LIST))); pwd)

CODE			?=	c++
COMPILER		?=	gcc

include $(PROJECT_ROOT)/build/command.mk
include $(PROJECT_ROOT)/build/variable.mk
include $(PROJECT_ROOT)/build/gcov.mk

include $(PROJECT_ROOT)/build/rules/rules.mk
include $(PROJECT_ROOT)/build/rules/help.mk

INCLUDE		+=	-I$(INC)
INCLUDE		+=	-I$(PROJECT_ROOT)/src
LDFLAGS		+=	-L$(LIB)

include $(PROJECT_ROOT)/build/gcc/auto-variable.mk
include $(PROJECT_ROOT)/build/$(COMPILER)/$(CODE).mk
include $(PROJECT_ROOT)/build/platform/$(PLATFORM).mk

# coverage in unittest
CLEAN_LIST	+=	coverage.info
