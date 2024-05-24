/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#ifndef TRISCV_MMU_H
#define TRISCV_MMU_H

#include <triscv/common.h>
#include <triscv/cpu.h>

#define BASE_PAGE_SIZE 19683

typedef void (*dev_write1_t)(struct cpu *cpu, void *dev, pm_t addr, tri_t t);
typedef void (*dev_write3_t)(struct cpu *cpu, void *dev, pm_t addr, tri_t t);
typedef tri_t (*dev_read1_t)(struct cpu *cpu, void *dev, pm_t addr);
typedef tri_t (*dev_read3_t)(struct cpu *cpu, void *dev, pm_t addr);

/* only character devices for now */
struct dev {
	void *dev;
	size_t size;
	dev_write1_t write1;
	dev_write3_t write3;
	dev_read1_t read1;
	dev_read3_t read3;
};

struct mmu *mmu_create();
void mmu_destroy(struct mmu *mmu);

/* not thread safe */
stat_t mmu_map_dev(struct mmu *mmu, pm_t start, struct dev dev);

void mmu_enable(struct mmu *mmu);
void mmu_disable(struct mmu *mmu);

bool mmu_valid(struct mmu *mmu, vm_t addr);

/* mmu can raise signals, so we pass cpu along */
tri_t mmu_read1(struct cpu *cpu, struct mmu *mmu, vm_t addr);
tri_t mmu_read3(struct cpu *cpu, struct mmu *mmu, vm_t addr);

void mmu_write1(struct cpu *cpu, struct mmu *mmu, vm_t addr, tri_t t);
void mmu_write3(struct cpu *cpu, struct mmu *mmu, vm_t addr, tri_t t);

tri_t mmu_read_pc(struct cpu *cpu, struct mmu *mmu, vm_t addr);

#endif
