.PHONY: all
all: setup
	$(MAKE) -f scripts/makefile

# this kicks all unrecognised targets to the client script.
# note that trying to compile individual files, e.g.
#
#	make kernel.elf
#
# will not work, you would need
#
#	make -f scripts/makefile kernel.elf
#
# instead
.DEFAULT: setup
	$(MAKE) -f scripts/makefile $<

.PHONY:
setup:
	@echo -n > deps.mk
	@./scripts/gen-deps -p TRISCV -c COMPILE_TRISCV -b triscv "${TRISCV_SOURCES}"

CLEANUP		:= build deps.mk triscv
CLEANUP_CMD	:=
TRISCV_SOURCES	:= ../utf9/utf9.c ../core/bits.c

include src/source.mk

.PHONY: format
format:
	find include src -iname '*.[ch]' |\
		xargs uncrustify -c uncrustify.conf --no-backup -F -

.PHONY: license
license:
	find include src -iname '*.[ch]' |\
		xargs ./scripts/license

.PHONY: docs
docs:
	find include src -iname '*.[ch]' -not -path */gen/* |\
		xargs ./scripts/warn-undocumented
	doxygen docs/doxygen.conf

RM	= rm

.PHONY: clean
clean:
	$(RM) -rf $(CLEANUP)

.PHONY: clean_docs
clean_docs:
	$(RM) -rf docs/output

.PHONY: clean_all
clean_all: clean clean_docs
