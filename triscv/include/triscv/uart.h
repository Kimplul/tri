/* SPDX-License-Identifier: copyleft-next-0.3.1 */

#ifndef TRISCV_UART_H
#define TRISCV_UART_H

#include <triscv/common.h>
#include <triscv/mmu.h>

struct uart *uart_create();
void uart_destroy(struct uart *uart);

struct dev uart_dev(struct uart *uart);

#endif
