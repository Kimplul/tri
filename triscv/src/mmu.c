#include <triscv/mmu.h>
#include <triscv/csr.h>

/* from and to must be page aligned, each tlb in map represent a base page. */
struct tlb_map {
	vm_t from;
	pm_t to;
	tri_t tag;
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
		if (d->start + (pm_t)d->dev.size <= addr)
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

struct tri_option {
	tri_t value;
	bool ok;
};

static struct tri_option __mmu_read3(struct cpu *cpu, struct mmu *mmu, vm_t addr)
{
	struct dev_map *d = mmu_find_dev_map(mmu, addr);
	if (!d || !d->dev.read3) {
		/** @todo raise bus error */
		return (struct tri_option){.ok = false};
	}

	return (struct tri_option){
		.value = d->dev.read3(cpu, d->dev.dev, addr - d->start),
		.ok = true
	};
}

void mmu_enable(struct mmu *mmu)
{
	mmu->translate = true;
}

void mmu_disable(struct mmu *mmu)
{
	mmu->translate = false;
}

static bool __valid_mapping(struct tlb_map mapping)
{
	return !(mapping.from == 1 && mapping.to == 1);
}

static struct tlb_map __build_invalid_mapping()
{
	return (struct tlb_map){.from = 1, .to = 1};
}

static struct tlb_map __build_mapping(vm_t from, pm_t to, tri_t tag)
{
	return (struct tlb_map){.from = from, .to = to, .tag = tag};
}

static bool __valid_pte(tri_t pte)
{
	return tri_get_trit(pte, 0) == 1;
}

static bool __leaf_pte(tri_t pte)
{
	int rw = tri_get_trit(pte, 1);
	int x = tri_get_trit(pte, 3);

	return !(x == 0 && rw == 0);
}

static pm_t __process_pte(struct cpu *cpu, struct mmu *mmu, pm_t table, tri_t orig, size_t shift,
		struct tlb_map *mapping)
{
	tri_t ppn = tri_mask(tri_sr(orig, shift), 6);
	pm_t i = tri_to(ppn);
	struct tri_option pte = __mmu_read3(cpu, mmu, table + 3 * i);

	if (!pte.ok || !__valid_pte(pte.value)) {
		*mapping = __build_invalid_mapping();
		return 0;
	}

	if (__leaf_pte(pte.value)) {
		// pte was fine, so the tag must be as well
		tri_t tag = __mmu_read3(cpu, mmu, table + 3 * i + 3).value;

		tri_t base = tri_discard(pte.value, 9);
		tri_t cur = tri_discard(orig, shift);
		tri_t off = tri_sub(orig, cur);

		*mapping = __build_mapping(tri_to(orig), tri_to(base) + tri_to(off), tag);
		return 0;
	}

	return pte.value;
}

static struct tlb_map __fetch_mapping(struct cpu *cpu, struct mmu *mmu, vm_t addr)
{
	/* feels kind of silly to convert back to trinary, but I guess fine for
	 * now. */
	tri_t orig = tri_from(addr);

	int sign = tri_sign(orig);

	tri_t start = 0;
	switch (sign) {
	case  1: start = get_csr(cpu, CSR_SATPP); break;
	case  0: start = get_csr(cpu, CSR_SATPO); break;
	case -1: start = get_csr(cpu, CSR_SATPN); break;
	}

	start = tri_to(start);

	tri_t pte = 0;
	struct tlb_map mapping = {0};
	if (!(pte = __process_pte(cpu, mmu, start, orig, 21, &mapping)))
		return mapping;

	start = tri_to(tri_discard(pte, 9));
	if (!(pte = __process_pte(cpu, mmu, start, orig, 15, &mapping)))
		return mapping;

	start = tri_to(tri_discard(pte, 9));
	if (!(pte = __process_pte(cpu, mmu, start, orig, 9, &mapping)))
		return mapping;

	return __build_invalid_mapping();
}

static bool mmu_translate(struct cpu *cpu, struct mmu *mmu, vm_t *addr)
{
	(void)cpu;

	vm_t base_page = *addr / BASE_PAGE_SIZE;
	vm_t base_addr = base_page * BASE_PAGE_SIZE;
	size_t slot = (size_t)base_page % MMU_SIZE;
	vm_t offset = *addr - base_addr;

	struct tlb_map mapping = mmu->tlb[slot];
	if (mapping.from != base_addr || !__valid_mapping(mapping))
		mmu->tlb[slot] = mapping = __fetch_mapping(cpu, mmu, base_addr);

	if (mapping.from != base_addr || !__valid_mapping(mapping)) {
		/* @todo raise segfault */
		return false;
	}

	/* @todo check rwx and tags */
	*addr = mapping.to + offset;
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

	return __mmu_read3(cpu, mmu, addr).value;
}

tri_t mmu_read_pc(struct cpu *cpu, struct mmu *mmu, vm_t addr)
{
	if (mmu->translate) {
		if (!mmu_translate(cpu, mmu, &addr))
			return 0;
	}

	return __mmu_read3(cpu, mmu, addr).value;
}
