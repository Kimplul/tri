#include <triscv/uart.h>
#include <triscv/cpu.h>
#include <triscv/mmu.h>
#include <triscv/tmb.h>
#include <triscv/mem.h>

#define OPCODE(t) (t)
#define RD(t) ((t) << 10)
#define RS1(t) ((t) << 28)
#define RS2(t) ((t) << 36)
#define IMM4(t) ((t) << 10)
#define IMM5(t) ((t) << 44)
#define IMM9(t) ((t) << 36)
#define IMM18(t) ((t) << 18)

static const tri_t prog[] = {
	/* li x1, '0' (48) */
	/* or in this case, lui x1, 0, addi x1, 48 */
	OPCODE(0b0100ULL) | RD(0b01ULL) | IMM18(0b0ULL),
	OPCODE(0b0000ULL) | RD(0b01ULL) | RS1(0b01ULL) | IMM9(0b0110100100ULL),
	/* li x2, 19683 (uart base reg) */
	OPCODE(0b0100ULL) | RD(0b10ULL) | IMM18(0b1ULL),
	OPCODE(0b0000ULL) | RD(0b10ULL) | RS1(0b10ULL) | IMM9(0ULL),
	/* sw x1, 0(x2) */
	OPCODE(0b0010ULL) | RS2(0b01ULL) | RS1(0b10ULL),
	/* li x1, 3 (mpower)*/
	OPCODE(0b0100ULL) | RD(0b01ULL),
	OPCODE(0b0000ULL) | RD(0b01ULL) | RS1(0b01ULL) | IMM9(0b0100ULL),
	/* csrrw mpower, x0, x1 */
	/* mpower = -9841, which is then internally converted to 0 */
	/* NOT FINAL CSR VALUE */
	OPCODE(0b0001ULL) | RD(0b00ULL) | RS1(0b01ULL) | IMM9(0b101010101010101010UL)
};

int main()
{
	/* add memory regions etc. */
	struct mmu *mmu = mmu_create();

	/* map one trinary page */
	struct mem *mem = mem_create(19683);
	mem_init(mem, prog, 8);
	mmu_map_dev(mmu, 0, mem_dev(mem));

	struct uart *uart = uart_create();
	mmu_map_dev(mmu, 19683, uart_dev(uart));

	struct tmb *tmb = tmb_create();

	/* one cpu for each core we want */
	struct cpu *cpu = cpu_create(mmu, tmb);

	cpu_run(cpu, 0);

	uart_destroy(uart);
	cpu_destroy(cpu);
	tmb_destroy(tmb);
	mmu_destroy(mmu);
	mem_destroy(mem);

	return 0;
}
