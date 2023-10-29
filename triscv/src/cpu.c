#include <triscv/cpu.h>
#include <triscv/mmu.h>
#include <triscv/csr.h>
#include <bits.h>

struct cpu {
	vm_t pc;
	struct mmu *mmu;
	struct tmb *tmb;

	enum mode {
		MMODE = 0, SMODE = 1, UMODE = 2
	} mode;

	/* we only have 81 registers, but 3^4 can be encoded in 2^8, and this
	 * way we can directly use the BCT as an index, speeding things up a bit
	 *
	 * csrs are too big, probably not worth it */
	tri_t gpr[256];

	/* 6561 M-mode, 6561 S-mode, 6561 U-mode, maybe? so ixxxxxxxx is
	 * reserved for M, 0xxxxxx for S, 1xxxx... for U. Just have to map them
	 * to decimal/binary in a somewhat sensible manner */
	/* value */
	tri_t csr[19683];
	/* write trit, all csrs are readable? */
	tri_t csrw[19683];
};

static size_t get_csr_num(tri_t csr)
{
	return tri_to(csr) + 9841;
}

static tri_t get_csr(struct cpu *cpu, size_t i)
{
	size_t max_csr = cpu->mode * 6561;
	if (i < max_csr)
		return 0; /* illegal access, should maybe also raise an interrupt? */

	return cpu->csr[i];
}

static void set_csr(struct cpu *cpu, size_t i, tri_t t)
{
	size_t max_csr = cpu->mode * 6561;
	if (i < max_csr)
		return;

	tri_t csr = cpu->csr[i];
	tri_t w = cpu->csrw[i];

	/* clear out trits we don't have write permission for*/
	t   &=  w;
	csr &= ~w;
	csr |= t;

	cpu->csr[i] = csr;
}

static tri_t get_gpr(struct cpu *cpu, tri_t i)
{
	/* could also add in check that i is in range, though that would
	 * probably add a fair bit of overhead */
	if (i == 0)
		return 0;

	return cpu->gpr[i];
}

static void set_gpr(struct cpu *cpu, tri_t i, tri_t t)
{
	if (i == 0)
		return;

	cpu->gpr[i] = t;
}

static void csr_init(struct cpu *cpu)
{
	cpu->csr[CSR_MPOWER] = 0;
	cpu->csrw[CSR_MPOWER] = RW_MPOWER;
}

struct cpu *cpu_create(struct mmu *mmu, struct tmb *tmb)
{
	struct cpu *cpu = calloc(1, sizeof(struct cpu));
	cpu->mmu = mmu;
	cpu->tmb = tmb;
	csr_init(cpu);
	return cpu;
}

void cpu_destroy(struct cpu *cpu)
{
	free(cpu);
}

static void do_op_imm(struct cpu *cpu, tri_t i)
{
	tri_t rd, fn0, rs1, imm9;
	parse_i(i, &rd, &fn0, &rs1, &imm9);

	tri_t src = get_gpr(cpu, rs1);

	switch (fn0) {
	case OP_IMM_ADDI: {
		tri_t r = tri_add(src, imm9);
		set_gpr(cpu, rd, r);
		break;
	}
	default: fprintf(stderr, "illegal/unimplemented OP_IMM at %lx,"
				 "aborting\n", cpu->pc);
		 abort();
	}

	cpu->pc += 3;
}

static void do_system(struct cpu *cpu, tri_t i)
{
	tri_t rd, fn0, rs1, imm9;
	parse_i(i, &rd, &fn0, &rs1, &imm9);

	tri_t src = get_gpr(cpu, rs1);

	switch (fn0) {
	case SYSTEM_CSRRW: {
		/* read existing value and replace it with rs1 */
		size_t n = get_csr_num(imm9);
		tri_t c = get_csr(cpu, n);
		set_csr(cpu, n, src);
		set_gpr(cpu, rd, c);
		break;
	}

	default: fprintf(stderr, "illegal/unimplemented SYSTEM at %lx,"
				 "aborting\n", cpu->pc);
		 abort();
	}

	cpu->pc += 3;
}

static void do_store(struct cpu *cpu, tri_t i)
{
	tri_t imm4, fn0, rs1, rs2, imm5;
	parse_s(i, &imm4, &fn0, &rs1, &rs2, &imm5);

	tri_t imm9 = tri_sl(imm4, 5) | imm5;
	tri_t base = get_gpr(cpu, rs2);
	tri_t src = get_gpr(cpu, rs1);

	/* should maybe check that there's zeroes in other trits in fn0? */
	int w = tri_get_trit(fn0, 4);

	/* somewhat unsure if mmu should function in trinary or binary at this
	 * point */
	tri_t addr = tri_add(base, imm9);
	vm_t a = tri_to(addr);

	switch (w) {
	case 0: mmu_write1(cpu, cpu->mmu, a, src); break;
	case 1: mmu_write3(cpu, cpu->mmu, a, src); break;
	default:
		/* illegal value */
		abort();
	}

	cpu->pc += 3;
}

static void do_lui(struct cpu *cpu, tri_t i)
{
	tri_t rd, imm18;
	parse_u(i, &rd, &imm18);
	set_gpr(cpu, rd, tri_sl(imm18, 9));
	cpu->pc += 3;
}

void cpu_reset(struct cpu *cpu)
{
	csr_init(cpu);
}

void cpu_run(struct cpu *cpu, vm_t start)
{
	cpu->pc = start;

	/* run while the shutdown trit is zero */
	while (!(cpu->csr[CSR_MPOWER] & 0b1100)) {
		tri_t i = mmu_read3(cpu, cpu->mmu, cpu->pc);
		/** @todo check for raised interrupts, illegal addr etc. */

		/* check lowest five trits to determine opcode */
		switch (parse_opcode(i)) {
		case OPCODE_LUI:    do_lui(cpu, i);    break;
		case OPCODE_STORE:  do_store(cpu, i);  break;
		case OPCODE_SYSTEM: do_system(cpu, i); break;
		case OPCODE_OP_IMM: do_op_imm(cpu, i); break;
		default: /** @todo raise illegal instruction exception */
			     fprintf(stderr, "illegal/unimplemented "
					     "instruction at %lx, aborting\n",
					     cpu->pc);
			     abort();
			     break;
		}

		/* do_* is responsible for updating pc */
	}
}
