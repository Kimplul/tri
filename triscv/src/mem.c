/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#include <triscv/mem.h>
#include <string.h>

struct mem {
	size_t size;
	uint32_t buf[];
};

struct mem *mem_create(size_t size)
{
	struct mem *mem = calloc(1,
	                         sizeof(struct mem) + size *
	                         sizeof(mem->buf[0]));
	mem->size = size;
	return mem;
}

void mem_destroy(struct mem *mem)
{
	free(mem);
}

void mem_init(struct mem *mem, const void *buf, size_t len)
{
	memcpy(mem->buf, buf, len);
}

static void mem_write1(struct cpu *cpu, struct mem *mem, pm_t addr, tri_t t)
{
	(void)cpu;
	mem->buf[addr] = tri_mask(t, 9);
}

static void mem_write3(struct cpu *cpu, struct mem *mem, pm_t addr, tri_t t)
{
	(void)cpu;
	tri_t t0 = tri_mask(t, 9);
	tri_t t1 = tri_mask(tri_sr(t, 9), 9);
	tri_t t2 = tri_mask(tri_sr(t, 18), 9);
	mem_write1(cpu, mem, addr + 0, t0);
	mem_write1(cpu, mem, addr + 1, t1);
	mem_write1(cpu, mem, addr + 2, t2);
}

static tri_t mem_read1(struct cpu *cpu, struct mem *mem, pm_t addr)
{
	(void)cpu;
	tri_t t = (tri_t)mem->buf[addr];
	return tri_mask(t, 9);
}

static tri_t mem_read3(struct cpu *cpu, struct mem *mem, pm_t addr)
{
	(void)cpu;
	/* not necessarily ideal, but I guess it works for now */
	tri_t t0 = mem_read1(cpu, mem, addr + 0);
	tri_t t1 = mem_read1(cpu, mem, addr + 1);
	tri_t t2 = mem_read1(cpu, mem, addr + 2);
	return t0 | tri_sl(t1, 9) | tri_sl(t2, 18);
}

struct dev mem_dev(struct mem *mem)
{
	return (struct dev){
		       .dev = mem,
		       .size = mem->size,
		       .write1 = (dev_write1_t)mem_write1,
		       .write3 = (dev_write3_t)mem_write3,
		       .read1 = (dev_read1_t)mem_read1,
		       .read3 = (dev_read3_t)mem_read3
	};
}
