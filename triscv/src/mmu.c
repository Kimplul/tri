#include <triscv/mmu.h>

struct tlb_map {
	vm_t from;
	pm_t to;
	bool valid;
};

struct dev_map {
	pm_t start;
	struct dev dev;
};

/* completely arbitrary value */
#define MMU_SIZE 1024
#define MAX_DEVS 16
struct mmu {
	/* virtual -> physical */
	struct tlb_map tlb[MMU_SIZE];

	/* physical to dev */
	struct dev_map dev[MAX_DEVS];
	size_t devs;

	/* whether we should treat incoming addresses as virtual or physical */
	bool translate;
};

struct mmu *mmu_create()
{
	/** @todo map some backing memory as well */
	return calloc(1, sizeof(struct mmu));
}

void mmu_destroy(struct mmu *mmu)
{
	free(mmu);
}

static struct dev_map *mmu_find_dev_map(struct mmu *mmu, pm_t addr)
{
	for (size_t i = 0; i < mmu->devs; ++i) {
		struct dev_map *d = &mmu->dev[i];
		if (d->start > addr)
			continue;

		/* slightly tricky off by one here */
		if (d->dev.size <= (addr - d->start))
			continue;

		return d;
	}

	return NULL;
}

stat_t mmu_map_dev(struct mmu *mmu, pm_t start, struct dev dev)
{
	/** @todo return status or something */
	if (mmu->devs == MAX_DEVS)
		return ERR_FULL;

	if (mmu_find_dev_map(mmu, start))
		return ERR_EXISTS;

	struct dev_map *d = &mmu->dev[mmu->devs++];
	d->dev = dev;
	d->start = start;
	return OK;
}

void mmu_enable(struct mmu *mmu)
{
	mmu->translate = true;
}

void mmu_disable(struct mmu *mmu)
{
	mmu->translate = false;
}

static bool mmu_translate(struct cpu *cpu, struct mmu *mmu, vm_t *addr)
{
	(void)cpu;
	(void)mmu;
	(void)addr;
	/** @todo raise segfault if addr is not allowed */
	return true;
}

void mmu_write1(struct cpu *cpu, struct mmu *mmu, vm_t addr, tri_t t)
{
	if (mmu->translate) {
		if (!mmu_translate(cpu, mmu, &addr))
			return;
	}

	struct dev_map *d = mmu_find_dev_map(mmu, addr);
	if (!d || !d->dev.write1) {
		/** @todo raise bus (?) error */
	}

	d->dev.write1(cpu, d->dev.dev, addr - d->start, t);
}

void mmu_write3(struct cpu *cpu, struct mmu *mmu, vm_t addr, tri_t t)
{
	if (mmu->translate) {
		if (!mmu_translate(cpu, mmu, &addr))
			return;
	}

	struct dev_map *d = mmu_find_dev_map(mmu, addr);
	if (!d || !d->dev.write3) {
		/** @todo raise bus error */
	}

	d->dev.write3(cpu, d->dev.dev, addr - d->start, t);
}

tri_t mmu_read1(struct cpu *cpu, struct mmu *mmu, vm_t addr)
{
	if (mmu->translate) {
		if (!mmu_translate(cpu, mmu, &addr))
			return 0;
	}

	struct dev_map *d = mmu_find_dev_map(mmu, addr);
	if (!d || !d->dev.read1) {
		/** @todo raise bus error */
		return 0;
	}

	return d->dev.read1(cpu, d->dev.dev, addr - d->start);
}

tri_t mmu_read3(struct cpu *cpu, struct mmu *mmu, vm_t addr)
{
	if (mmu->translate) {
		if (!mmu_translate(cpu, mmu, &addr))
			return 0;
	}

	struct dev_map *d = mmu_find_dev_map(mmu, addr);
	if (!d || !d->dev.read3) {
		/** @todo raise bus error */
		return 0;
	}

	return d->dev.read3(cpu, d->dev.dev, addr - d->start);
}
