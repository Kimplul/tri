#ifndef UTF9_H
#define UTF9_H

#include <stddef.h>
#include <tri.h>

size_t utf8_to_utf9(tri_t *u9, size_t u9_len, const uint8_t *u8, size_t u8_len, size_t *u8_read);

size_t utf9_to_utf8(uint8_t *u8, size_t u8_len, const tri_t *u9, size_t u9_len, size_t *u9_read);

#endif
