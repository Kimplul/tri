#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>

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

static const char *cmdline_usage =
"triscv simulator usage:\n"
" triscv simfile\n"
"	-h      Show usage(this)\n"
"	simfile File to simulate\n"
;

static void usage()
{
	fprintf(stderr, cmdline_usage);
}

static const char *read_simulation_file(const char *file, size_t *len)
{
	FILE *f = fopen(file, "rb");
	if (!f) {
		fprintf(stderr, "failed opening simulation file %s\n", file);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long s = ftell(f);
	if (s == LONG_MAX) {
		fprintf(stderr, "unable to get file size of %s\n", file);
		return NULL;
	}

	if (len)
		*len = s;

	fseek(f, 0, SEEK_SET);
	char *buf = malloc(s);
	if (!buf)
		return NULL;

	fread(buf, s, 1 , f);
	return buf;
}

int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "h")) != -1) {
		switch (opt) {
			case 'h':
				usage();
				exit(EXIT_SUCCESS);
				break;
			default:
				usage();
				exit(EXIT_FAILURE);
				break;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "no simulation file\n");
		usage();
		exit(EXIT_FAILURE);
	}

	if (optind != argc - 1) {
		fprintf(stderr, "too many simulation files\n");
		usage();
		exit(EXIT_FAILURE);
	}


	/* add memory regions etc. */
	struct mmu *mmu = mmu_create();

	/* map one trinary page */
	struct mem *mem = mem_create(19683);
	size_t len = 0;
	const char *buf = read_simulation_file(argv[optind], &len);
	mem_init(mem, buf, len);

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
