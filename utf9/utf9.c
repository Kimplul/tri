#include <tri.h>

static size_t legal_utf8(const uint8_t *u8, size_t pos, size_t len)
{
	if (pos >= len)
		return 0;

	u8 += pos;

	uint8_t c = u8[0];
	if (~c & 0x80)
		return 1;

	if (~c & 0x40)
		return 0;

	/* we know 0b11xxxxxx, so we must have at least two bytes */
	size_t bytes = 2;
	if (~c & 0x20)      bytes = 2;
	else if (~c & 0x10) bytes = 3;
	else if (~c & 0x08) bytes = 4;

	/* too short, code point is cut off */
	if (len < bytes)
		return 0;

	for (size_t i = 0; i < bytes - 1; ++i) {
		/* invalid continuation byte */
		uint8_t top_two_bits = u8[1 + i] >> 6;
		/* don't know if we sign extended, so mask lowest two bits */
		if ((top_two_bits & 0x3) != 2)
			return 0;
	}

	return bytes;
}

static tri_t get_tryte(const tri_t *t, size_t p)
{
	size_t idx = p / 3;
	size_t shift = (p % 3) * 9;
	tri_t e = t[idx];

	e = tri_sr(e, shift);
	e = tri_mask(e, 9);
	return e;
}

static size_t legal_utf9(const tri_t *t, size_t p9, size_t len)
{
	if (p9 >= len)
		return 0;

	tri_t e = get_tryte(t, p9);
	int top = tri_get_trit(e, 8);

	/* continuation tryte as first tryte, not allowed */
	if (top == -1)
		return 0;

	/* one tryte codepoint */
	if (top == 0) {
		switch (tri_get_trit(e, 7)) {
		case -1: return 0; /* illegal */
		case  0: return 1;
		case  1: return 2;
		}

		/* shouldn't be possible but just to make sure */
		return 0;
	}

	/* two tryte codepoint */
	if (p9 + 1 >= len)
		return 0;

	tri_t n = get_tryte(t, p9 + 1);
	int d0 = tri_get_trit(n, 8);

	switch (tri_get_trit(e, 7)) {
	case -1: return 0; /* reserved for now */
	case  0: {
		int d1 = tri_get_trit(n, 7);
		if (d0 == 0 && d1 == -1)
			return 3;

		return 0;
	}

	case  1: {
		if (d0 == -1)
			return 4;

		return 0;
	}
	}

	return 0;
}

static int64_t extract_bits_utf8(const uint8_t *u8, size_t pos, size_t bytes)
{
	u8 += pos;

	/* feels like some repetition could be dealt with, but as long as this works I
	 * guess */
	switch (bytes) {
	case 1: return u8[0] & 0x7f;
	case 2: {
		int64_t b0 = u8[0] & 0x1f;
		int64_t b1 = u8[1] & 0x3f;
		return (b0 << 6) | b1;
	}

	case 3: {
		int64_t b0 = u8[0] & 0xf;
		int64_t b1 = u8[1] & 0x3f;
		int64_t b2 = u8[2] & 0x3f;
		return (b0 << 12) | (b1 << 6) | b2;
	}

	case 4: {
		int64_t b0 = u8[0] & 0x7;
		int64_t b1 = u8[1] & 0x3f;
		int64_t b2 = u8[2] & 0x3f;
		int64_t b3 = u8[3] & 0x3f;
		return (b0 << 18) | (b1 << 12) | (b2 << 6) | b3;
	}
	}

	abort();
	return 0;
}

static int64_t extract_bits_utf9(const tri_t *u9, size_t p9, size_t bytes)
{
	tri_t e = get_tryte(u9, p9);
	/* clear out header trits */
	e = tri_mask(e, 7);

	int64_t r = tri_to(e);
	switch (bytes) {
	case 1: return r & 0x7f;
	case 2: return r & 0x7ff;
	case 3: {
		int64_t b0 = r & 0x3ff;
		tri_t t = get_tryte(u9, p9 + 1);
		t = tri_mask(t, 7);
		int64_t b1 = tri_to(t) & 0x3f;
		return (b0 << 6) + b1;
	}
	case 4: {
		int64_t b0 = r & 0x1ff;
		/* four byte case is kind of special, as it only has a single
		 * trit as a marker */
		tri_t t = get_tryte(u9, p9 + 1);
		t = tri_mask(t, 8);
		int64_t b1 = tri_to(t) & 0x7ff;
		return (b0 << 12) + b1;
	}
	}

	/* shouldn't be possible */
	return 0;
}

static void set_utf9(tri_t *u9, size_t p9, tri_t t, const char *s, size_t len)
{
	/* should this prefer get_tryte and set_trit or something? */
	size_t idx = p9 / 3;
	size_t shift = (p9 % 3) * 9;

	tri_t e = u9[idx];

	/* should only have lowest tryte, but just to be sure */
	t = tri_mask(t, 9);

	/* clear out our shift destination */
	tri_t tmp = tri_mask(e, shift);
	e = tri_discard(e, shift + 9);
	e |= tmp;

	/* set prefixes, assumes i01 */
	for (size_t i = 0; i < len; ++i) {
		char c = s[i];

		switch (c) {
		case '1': t = tri_set_trit(t, 8 - i,  1); break;
		case 'i': t = tri_set_trit(t, 8 - i, -1); break;
		}
	}

	t = tri_sl(t, shift);
	e |= t;
	u9[idx] = e;
}

static void set_utf8(uint8_t *u8, size_t p8, int64_t b, const char *s, size_t len)
{
	/* set prefixes */
	for (size_t i = 0; i < len; ++i) {
		char c = s[i];
		switch (c) {
		case '1': b |=  (1 << (7 - i)); break;
		case '0': b &= ~(1 << (7 - i)); break;
		}
	}

	u8[p8] = b;
}

size_t utf8_to_utf9(tri_t *u9, size_t u9_len, const uint8_t *u8, size_t u8_len, size_t *u8_read)
{
	size_t p8 = 0;
	size_t p9 = 0;

	while (true) {
		if (p9 == u9_len)
			break;

		if (p8 == u8_len)
			break;

		size_t bytes = 0;
		/* also checks that we have enough space to work with */
		if ((bytes = legal_utf8(u8, p8, u8_len)) == 0)
			return 0;

		/* round up */
		size_t trytes = (bytes  + 1) / 2;

		/* not enough space for result */
		if (p9 + trytes >= u9_len)
			return 0;

		int64_t bits = extract_bits_utf8(u8, p8, bytes);
		switch (bytes) {
		case 1: {
			tri_t t = tri_from(bits & 0x7f);
			set_utf9(u9, p9++, t, "00", 2);
			break;
		}

		case 2: {
			tri_t t = tri_from(bits & 0x7ff);
			set_utf9(u9, p9++, t, "01", 2);
			break;
		}

		case 3: {
			tri_t t0 = tri_from(bits & 0x3f);
			tri_t t1 = tri_from((bits >> 6) & 0x3ff);
			set_utf9(u9, p9++, t1, "10", 2);
			set_utf9(u9, p9++, t0, "0i", 2);
			break;
		}

		case 4: {
			tri_t t0 = tri_from(bits & 0x3ff);
			tri_t t1 = tri_from((bits >> 12) & 0x1f);
			set_utf9(u9, p9++, t1, "11", 2);
			set_utf9(u9, p9++, t0, "i", 1);
			break;
		}
		default: abort();
		}

		p8 += bytes;
	}

	if (u8_read)
		*u8_read = p8;

	return p9;
}

size_t utf9_to_utf8(uint8_t *u8, size_t u8_len, const tri_t *u9, size_t u9_len, size_t *u9_read)
{
	size_t p8 = 0;
	size_t p9 = 0;

	while (true) {
		if (p9 == u9_len)
			break;

		if (p8 == u8_len)
			break;

		size_t bytes = 0;
		if ((bytes = legal_utf9(u9, p9, u9_len)) == 0)
			return 0;

		size_t trytes = (bytes + 1) / 2;
		if (p8 + bytes >= u8_len)
			return 0;

		int64_t bits = extract_bits_utf9(u9, p9, bytes);
		/* moving this switch into something like encode_bits_utf8()
		 * could be useful if we want to iterate over all codepoints */
		switch (bytes) {
		case 1: {
			int64_t b0 = bits & 0x7f;
			set_utf8(u8, p8++, b0, "0", 1);
			break;
		}

		case 2: {
			int64_t b1 = bits & 0x3f;
			int64_t b0 = (bits >> 6) & 0x1f;
			set_utf8(u8, p8++, b0, "110", 3);
			set_utf8(u8, p8++, b1, "10", 2);
			break;
		}

		case 3: {
			int64_t b2 = bits & 0x3f;
			int64_t b1 = (bits >> 6) & 0x3f;
			int64_t b0 = (bits >> 12) & 0xf;
			set_utf8(u8, p8++, b0, "1110", 4);
			set_utf8(u8, p8++, b1, "10", 2);
			set_utf8(u8, p8++, b2, "10", 2);
			break;
		}

		case 4: {
			int64_t b3 = bits & 0x3f;
			int64_t b2 = (bits >> 6) & 0x3f;
			int64_t b1 = (bits >> 12) & 0x3f;
			int64_t b0 = (bits >> 18) & 0x07;
			set_utf8(u8, p8++, b0, "11110", 5);
			set_utf8(u8, p8++, b1, "10", 2);
			set_utf8(u8, p8++, b2, "10", 2);
			set_utf8(u8, p8++, b3, "10", 2);
			break;
		}
		}

		p9 += trytes;

	}

	if (u9_read)
		*u9_read = p9;

	return p8;
}
