PROJECT_ROOT    =   $(shell cd ../..; pwd)
PROC            =   /usr/local/bin/protoc
PROC_PATH       =   ./
CPP_OUT_PATH    =   ./
LDFLAGS         += -L/home/a/lib64/ -lprotobuf -lpthread
CXXFILES 		+= main.cpp
CXXFILES		+= Person.pb.cpp
TARGETS			+= person	
TARGETS			+= libperson.a

include $(PROJECT_ROOT)/common.mk

person: $(OBJ_DIR)/main.o $(OFILES) | $(BIN)
	 $(CC) -o $@ $^ $(LDFLAGS) $(LLIB)
Person.pb.cpp: Person.pb.cc
	mv $^ $@
Person.pb.cc: Person.proto
	$(PROC) --proto_path=$(PROC_PATH) --cpp_out=$(CPP_OUT_PATH) $^
