.PHONY: all prereq debug clean

all:: prereq $(TARGETS)
ifeq ($(strip $(TARGETS)),)	# $(TARGETS) is empty
else
	@echo "$(TARGETS) is ready."
endif

release::
	$(MAKE) all $(OPTIONS)

prereq::
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir all $(OPTIONS); done

OFILES		=	$(CXXFILES:%.cpp=$(OBJ_DIR)/%.o)
SOFILES		=	$(CXXFILES:%.cpp=$(SOBJ_DIR)/%.o)
TOFILES		=	$(CXXFILES:%.cpp=$(TOBJ_DIR)/%.o)

.SECONDARY: $(OFILES) $(SOFILES) $(TOFILES)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@
$(SOBJ_DIR)/%.o: %.cpp | $(SOBJ_DIR)
	$(CC) $(CC_PIC_FLAG) -c $(CFLAGS) $(INCLUDE) $^ -o $@
$(TOBJ_DIR)/%.o: %.cpp | $(TOBJ_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@

#$(OBJ_DIR)/%.o:: %$(CODE_EXT) | $(OBJ_DIR)
#	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@
#$(SOBJ_DIR)/%.o:: %$(CODE_EXT) | $(SOBJ_DIR)
#	$(CC) $(CC_PIC_FLAG) -c $(CFLAGS) $(INCLUDE) $^ -o $@
#$(TOBJ_DIR)/%.o:: %$(CODE_EXT) | $(TOBJ_DIR)
#	$(CC) -c $(CFLAGS) $(INCLUDE) $^ -o $@

%$(STATIC_LIB_EXT): $(OFILES)	| $(LIB)
	@echo "Generating static library: $@ ..."
	$(AR) rc $@ $^
	$(CP) -f $@ $(LIB)/

%$(SHARED_LIB_EXT): $(SOFILES)  | $(LIB)
	@echo "Generating shared library: $@ ..."
	$(CC) -shared $(LDFLAGS) -o $@ $^
	$(CP) -f $@ $(LIB)/

$(sort $(MKDIRS)):
	$(MKDIR) -p $@

clean::
	for dir in $(SUBDIRS); do	\
		$(MAKE) -C $$dir clean $(OPTIONS);	\
	done
	$(RM) -f $(TARGETS)
	$(RM) -rf $(OBJ_DIR) $(SOBJ_DIR) $(TOBJ_DIR)
	$(RM) -rf $(CLEAN_LIST)

debug::
	@echo "PROJECT_ROOT = $(PROJECT_ROOT)"
	@echo "PROCESSOR = $(PROCESSOR)"
	@echo "ARCH_SUFFIX = $(ARCH_SUFFIX)"
	@echo "PLATFORM = $(PLATFORM)"
	@echo "SHARED_LIB_EXT = $(SHARED_LIB_EXT)"
	@echo "STATIC_LIB_EXT = $(STATIC_LIB_EXT)"
	@echo "SYS_FLAG = $(SYS_FLAG)"
	@echo "TARGETS = $(TARGETS)"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "INCLUDE = $(INCLUDE)"
	@echo "CODE_EXT = $(CODE_EXT)"
	@echo "CP = $(CP)"
	@echo "LIB = $(LIB)"
	@echo "INC = $(INC)"
