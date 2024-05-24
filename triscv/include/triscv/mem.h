/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#ifndef TRISCV_MEM_H
#define TRISCV_MEM_H

#include <triscv/common.h>
#include <triscv/mmu.h>

struct mem *mem_create(size_t size);
void mem_destroy(struct mem *mem);
void mem_init(struct mem *mem, const void *buf, size_t len);

struct dev mem_dev(struct mem *mem);

#endif
