/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#include <triscv/uart.h>
#include <utf9.h>

struct uart {
	/* guess this doesn't need much for now, at least until I add some state
	 * stuff to it */
};

struct uart *uart_create()
{
	return calloc(1, sizeof(struct uart));
}

void uart_destroy(struct uart *uart)
{
	free(uart);
}

static void uart_write1(struct cpu *cpu, struct uart *uart, pm_t addr, tri_t t)
{
	(void)cpu;
	(void)uart;
	(void)addr;

#define U8_LEN 16
	uint8_t u8[U8_LEN] = {0};
	size_t u9_read = 0;
	size_t l = utf9_to_utf8(u8, U8_LEN, &t, 1, &u9_read);

	for (size_t i = 0; i < l; ++i)
		putchar(u8[i]);
}

struct dev uart_dev(struct uart *uart)
{
	return (struct dev){
		       .dev = uart,
		       .size = 1,
		       .write1 = (dev_write1_t)uart_write1,
		       .write3 = NULL, /* illegal */
		       .read1 = NULL, /* not supported for now */
		       .read3 = NULL
	};
}
