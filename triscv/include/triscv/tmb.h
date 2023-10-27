#ifndef TRISCV_TMB_H
#define TRISCV_TMB_H

#include <triscv/common.h>
#include <triscv/cpu.h>

struct tmb *tmb_create();
void tmb_destroy(struct tmb *tmb);

size_t tmb_size(struct cpu *cpu);

void tmb_clear(struct cpu *cpu);
void tmb_cancel(struct cpu *cpu);
void tmb_store1(struct cpu *cpu, vm_t addr, tri_t t);
void tmb_store3(struct cpu *cpu, vm_t addr, tri_t t);
bool tmb_commit(struct cpu *cpu);

#endif
