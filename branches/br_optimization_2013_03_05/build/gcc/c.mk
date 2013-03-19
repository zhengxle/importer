# Extensions for files
CODE_EXT		= .c
HEADERS_EXT		= .h
OBJECT_EXT		= .o

# Compiler tools
CC				= gcc
LIBTOOL			= glibtool

# Arguments for the compiler tools
ARGS_CC         		= -std=c99 -Os -pedantic -Werror -Wall -Wextra -Wbad-function-cast -Wdeclaration-after-statement -Werror-implicit-function-declaration -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-prototypes -Wnested-externs -Wold-style-definition -Wparentheses -Wreturn-type -Wshadow -Wsign-compare -Wstrict-prototypes -Wswitch -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable
ARGS_LIBTOOL_COMPILE    = --mode=compile
ARGS_LIBTOOL_LINK       = --mode=link
