# this could be done better
RELEASE		?= 0
OPTFLAGS	!= [ "$(RELEASE)" != "0" ] \
			&& echo "-O3 -flto" \
			|| echo "-O0"

DEBUG		?= 1
DEBUGFLAGS	!= [ "$(DEBUG)" != "0" ] \
			&& echo "-DDEBUG=1" \
			|| echo "-DNDEBUG=1"

ASSERT		?= 1
ASSERTFLAGS	!= [ "$(ASSERT)" != "0" ] \
			&& echo "-DASSERT=1" \
			|| echo

DEPFLAGS	= -MT $@ -MMD -MP -MF $@.d
LINTFLAGS	= -fsyntax-only
PREPROCESS	= -E

LLVM		?= 0
BUILD		= build

all: triscv

# default values, overwrite if/when needed
CROSS_COMPILE	=

OBJCOPY		!= [ "$(LLVM)" != "0" ] \
			&& echo llvm-objcopy \
			|| echo $(CROSS_COMPILE)objcopy

COMPILER	!= [ "$(LLVM)" != "0" ] \
			&& echo clang --target="$(CROSS_COMPILE)" \
			|| echo $(CROSS_COMPILE)gcc


OBFLAGS		= -std=c17 -g
WARNFLAGS	= -Wall -Wextra

COMPILE_FLAGS	= $(CFLAGS) $(WARNFLAGS) $(OPTFLAGS) $(OBFLAGS) $(ASSERTFLAGS) \
		   $(DEBUGFLAGS)

INCLUDE_FLAGS	= -I include -I ../core -I ../utf9

# This makes sure .bss is loaded into the binary
OBJCOPY_FLAGS	?= -Obinary -R .garbage \
		   --set-section-flags .bss=alloc,load,contents

COMPILE		= $(COMPILER) \
		  $(COMPILE_FLAGS) $(DEPFLAGS) $(INCLUDE_FLAGS)

LINT		= $(COMPILER) \
		  $(COMPILE_FLAGS) $(LINTFLAGS) $(INCLUDE_FLAGS)

UBSAN		?= 0
TRISCV_FLAGS	!= [ "$(UBSAN)" != "0" ] \
			&& echo -fsanitize=undefined \
			|| echo

COMPILE_TRISCV	= $(COMPILE) $(TRISCV_FLAGS)

-include deps.mk

triscv: $(TRISCV_OBJS)
	$(COMPILE_TRISCV) $(TRISCV_OBJS) -o $@


# might lint some common things twice
.PHONY:
lint: $(TRISCV_LINTS)
