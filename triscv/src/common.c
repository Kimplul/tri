#include <triscv/common.h>

static const char *err_strs[] = {
	[OK] = "OK",
	[ERR_FULL] = "full",
	[ERR_EXISTS] = "exists",
	[ERR_OOB] = "out of bounds"
};

const char *err_str(stat_t s)
{
	return err_strs[s];
}
