#SYS_BASE_DIR	=	$(shell cd $(dir $(lastword $(MAKEFILE_LIST)))/gcc; pwd)
SYS_BASE_DIR	=	$(PROJECT_ROOT)/build/gcc

SYS_NERR		=	$(shell gcc $(SYS_BASE_DIR)/sys_nerr.c -o $(SYS_BASE_DIR)/sys_nerr >&/dev/null && $(SYS_BASE_DIR)/sys_nerr | perl -pe "chomp")
