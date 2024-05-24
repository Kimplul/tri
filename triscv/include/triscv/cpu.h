/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#ifndef TRISCV_CPU_H
#define TRISCV_CPU_H

#include <triscv/common.h>

struct cpu *cpu_create(struct mmu *mmu, struct tmb *tmb);
void cpu_reset(struct cpu *cpu);
void cpu_destroy(struct cpu *cpu);

/** @todo how should external interrupts be handled? add some list of devices to
 * update after each cycle? */
void cpu_run(struct cpu *cpu, vm_t start);

void set_csr(struct cpu *cpu, long i, tri_t t);
tri_t get_csr(struct cpu *cpu, long i);

#endif
