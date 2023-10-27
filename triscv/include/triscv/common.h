#ifndef TRISCV_COMMON_H
#define TRISCV_COMMON_H

#include <tri.h>
#include <stdint.h>

typedef uint64_t vm_t;
typedef uint64_t pm_t;

/* forward declarations */
struct cpu;
struct tmb;
struct mmu;
struct mem;
struct uart;

enum stat {
	OK = 0,
	ERR_FULL,
	ERR_EXISTS,
	ERR_OOB,
};

typedef enum stat stat_t;

const char *err_str(stat_t s);

#endif
