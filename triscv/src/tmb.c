/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#include <triscv/tmb.h>

struct map {
	vm_t to;
	tri_t val;
	size_t width;
	bool valid;
};

#define TMB_SIZE 3
struct tmb {
	struct map map[TMB_SIZE];
};

struct tmb *tmb_create()
{
	return calloc(1, sizeof(struct tmb));
}

void tmb_destroy(struct tmb *tmb)
{
	free(tmb);
}

size_t tmb_size(struct cpu *cpu)
{
	(void)cpu;
	return TMB_SIZE;
}
