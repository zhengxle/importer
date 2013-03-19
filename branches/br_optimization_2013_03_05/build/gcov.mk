GTEST_FLAGS		+=
ifeq ($(unittest), yes)
	CFLAGS		+= -D UNITTEST
	OPTIONS		+= unittest=yes
endif

ifeq ($(coverage), yes)
	OPTIONS		+= coverage=yes
	CFLAGS		+= -fprofile-arcs -ftest-coverage -fno-access-control
	LDFLAGS		+= -fprofile-arcs
	#CFLAGS += -fprofile-arcs -ftest-coverage -fkeep-inline-functions -fno-default-inline
	GTEST_FLAGS += --gtest_repeat=1 --gtest_shuffle --gtest_color=no
endif
