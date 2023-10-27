#ifndef CORE_TRI_H
#define CORE_TRI_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* type that can contain the binary value of a tri */
typedef uint64_t tri_t;

#define TRI_WIDTH 27

/* (3^(27) - 1) / 2 */
#define TRI_MAX 3812798742493LL
#define TRI_MIN -TRI_MAX

/* 54 bits */
#define TRI_BMASK 0x7fffffffffffff
/* alternating ...0101 */
#define TRI_PMASK 0x15555555555555
/* alternating ...1010 */
#define TRI_NMASK 0x2aaaaaaaaaaaaa

/**
 * fairly trivial mapping,
 * where operations are mapped as N/O/P, where
 * N means that negative values are mapped,
 * O means neutral and P means positive.
 *
 * So for example NOP means N is mapped to N,
 * O is mapped to O, P is mapped to P.
 */
enum triop {
	N = 1,
	O = 2,
	P = 3,
};
typedef enum triop triop_t;

/* syntactic sugar around passing arguments to TRIOP3 and TRIOP9 */
#define NNN N, N, N
#define NNO N, N, O
#define NNP N, N, P
#define NON N, O, N
#define NOO N, O, O
#define NOP N, O, P
#define NPN N, P, N
#define NPO N, P, O
#define NPP N, P, P

#define ONN O, N, N
#define ONO O, N, O
#define ONP O, N, P
#define OON O, O, N
#define OOO O, O, O
#define OOP O, O, P
#define OPN O, P, N
#define OPO O, P, O
#define OPP O, P, P

#define PNN P, N, N
#define PNO P, N, O
#define PNP P, N, P
#define PON P, O, N
#define POO P, O, O
#define POP P, O, P
#define PPN P, P, N
#define PPO P, P, O
#define PPP P, P, P

#define GET_TRIOP(t, x)\
	(((t) >> ((x) * 2)) & 0x3)

#define _SET_TRIOP(t, x)\
	((t) << ((x) * 2))

#define _TRIOP3(a, b, c, i) \
	(_SET_TRIOP((a), (i) + 0) | _SET_TRIOP((b), (i) + 1) | _SET_TRIOP((c), (i) + 2))

#define TRIOP3(a) \
	_TRIOP3(a, 0)

#define _TRIOP9(a, b, c, d, e, f, g, h, i) \
	(_TRIOP3(a, b, c, 0) | _TRIOP3(d, e, f, 3) | _TRIOP3(g, h, i, 6))

#define TRIOP9(a, b, c) \
	_TRIOP9(a, b, c)

static inline int tri_get_trit(tri_t t, size_t i)
{
	bool p = (t >> ((2 * i) + 0)) & 1;
	bool n = (t >> ((2 * i) + 1)) & 1;

	/* assume normalized */
	if (!p && !n)
		return 0;

	if (p)
		return 1;

	if (n)
		return -1;

	/* shouldn't be possible */
	return 0;
}

static inline tri_t tri_set_trit(tri_t t, size_t i, int f)
{
	/* preclear area */
	t &= ~(0x3ULL << (i * 2));
	if (f == 0)
		return t;

	if (f < 0)
		return t | (0x2ULL << (i * 2));

	return t | (0x1ULL << (i * 2));
}

/* keep n lowest trits */
static inline tri_t tri_mask(tri_t t, size_t n)
{
	return t & ((1ULL << (n * 2)) - 1);
}

/* discard n lowest trits */
static inline tri_t tri_discard(tri_t t, size_t n)
{
	return t & ~((1ULL << (n * 2)) - 1);
}

static inline tri_t tri_ns(tri_t t)
{
	tri_t n = ( t & TRI_NMASK) >> 1;
	tri_t p = (~t & TRI_PMASK) >> 0;

	tri_t ns = (n & p);
	ns |= ns << 1;

	return ns;
}

static inline tri_t tri_ps(tri_t t)
{
	tri_t n = (~t & TRI_NMASK) >> 1;
	tri_t p = ( t & TRI_PMASK) >> 0;

	tri_t ps = (n & p);
	ps |= ps << 1;

	return ps;
}

static inline tri_t tri_zs(tri_t t)
{
	tri_t n = (~t & TRI_NMASK) >> 1;
	tri_t p = (~t & TRI_PMASK) >> 0;

	tri_t z = (n & p);
	z |= z << 1;

	return z;
}

static inline tri_t tri_us(tri_t t)
{
	tri_t n = ( t & TRI_NMASK) >> 1;
	tri_t p = ( t & TRI_PMASK) >> 0;

	tri_t u = (n & p);
	u |= u << 1;

	return u;
}

static inline tri_t tri_normalize(tri_t t)
{
	/* convert binary ones in both positive and negative trits to zero */
	tri_t t0 = ((t & TRI_PMASK) << 1) & t;
	t0 |= t0 << 1;
	return (t & ~t0) & TRI_BMASK;
}

static inline tri_t tri_bias(tri_t a)
{
	tri_t z = tri_zs(a);
	tri_t p = tri_ps(a);
	return (TRI_PMASK & z) | (TRI_NMASK & p);
}

static inline tri_t tri_unbias(tri_t a)
{
	tri_t n = tri_ns(a);
	tri_t z = tri_zs(a);
	return (TRI_PMASK & n) | (TRI_NMASK & z);
}

static inline tri_t tri_neg(tri_t t)
{
	tri_t p = t & TRI_PMASK;
	tri_t n = t & TRI_NMASK;
	return (p << 1) | (n >> 1);
}

static inline tri_t tri_from(int64_t v)
{
	static const uint16_t tbl[] = {
#include "t9.inc"
	};

	bool neg = false;
	if (v < 0) {
		neg = true;
		v = - v;
	}

	tri_t s = 0;
	for (size_t i = 0; i < 5; ++i) {
		int64_t d = v / 729;
		int64_t r = v - (d * 729);

		tri_t t = tbl[r];
		s |= (t & 0xfff) << (i * 12);

		v = d;

		tri_t c = t >> 12;
		if (c == 1)      v += 1;
		else if (c == 2) v -= 1;
	}

	if (neg)
		s = tri_neg(s);

	return s & TRI_BMASK;
}

static inline int64_t tri_to(tri_t t)
{
	/* apparently an algorithm that a superoptimizer found so I'm not even
	 * going to try to understand what's going on */
        tri_t acc = tri_bias(t);

        acc = acc - (((acc >>  2) & 0x3333333333333333) * (         4 -        3));
        acc = acc - (((acc >>  4) & 0x0F0F0F0F0F0F0F0F) * (        16 -        9));
        acc = acc - (((acc >>  8) & 0x00FF00FF00FF00FF) * (       256 -       81));
        acc = acc - (((acc >> 16) & 0x0000FFFF0000FFFF) * (     65536 -     6561));
        acc = acc - (((acc >> 32) & 0x00000000FFFFFFFF) * (4294967296 - 43046721));

        return (int64_t)acc - TRI_MAX;
}

static inline tri_t tri_parse(const char *s, size_t len, char n, char o, char p)
{
	int64_t r = 1;
	int64_t sum = 0;
	size_t l = len < TRI_WIDTH ? len : TRI_WIDTH;
	for (size_t i = 0; i < l; r *= 3, ++i) {
		char t = s[len - 1 - i];
		if (t == n) { sum -= r; continue; }
		if (t == p) { sum += r; continue; }
		if (t == o) continue;

		/* not pretty but good enough for now */
		fprintf(stderr, "invalid trinary digit: %c\n", t);
		abort();
	}

	return tri_from(sum);
}

static inline tri_t tri_parse_default(const char *s, size_t len)
{
	return tri_parse(s, len, 'i', '0', '1');
}

/* does not append trailing NULL */
/* could be useful to add how many zeroes to print out? */
static inline size_t tri_fmt(char *s, size_t len, tri_t t, char n, char o, char p)
{
	int64_t v = tri_to(t);
	if (v == 0) {
		s[0] = '0';
		return 1;
	}

	/* naive conversion to trinary is pretty nifty as it automatically stops
	 * once we reach zero, but I still need to add padding and possibly base
	 * as well */
	size_t i = 0;
	while (v) {
		if (i >= len)
			break;

		int d = v % 3;

		switch (d) {
		case +2:
		case -1: s[i] = n; v += 1; break;

		case -2:
		case +1: s[i] = p; v -= 1; break;

		default: s[i] = o;
		}

		v /= 3;
		i++;
	}

	/* reverse string */
	for (size_t j = 0; j < i / 2; ++j) {
		size_t k = i - j - 1;
		char tmp = s[j];
		s[j] = s[k];
		s[k] = tmp;
	}
	return i;
}

static inline size_t tri_fmt_default(char *s, size_t len, tri_t t)
{
	return tri_fmt(s, len, t, 'i', '0', '1');
}

static inline tri_t tri_sl(tri_t t, size_t i)
{
	return t << (i * 2);
}

static inline tri_t tri_sr(tri_t t, size_t i)
{
	return t >> (i * 2);
}

/* bias happends to be used in several places */
#define BIAS 0x5555555555555555ULL
static inline tri_t tri_bsum(tri_t a, tri_t b)
{
	/* directly lifted from libter27,
	 * http://homepage.cs.uiowa.edu/~dwjones/ternary/libtern.shtml
	 * added comments to help myself understand what's going on */

	/* Really cool algorithm, first `a` is mapped to another number system,
	 * where 00 is invalid, and the trinary values look like
	 *	00 "0" => 01
	 *	01 "1" => 10
	 *	10 "2" => 11
	 *
	 * This is so our hardware addition functions according to
	 *
	 *	c+b | 00 | 01 | 10
	 *	----+----+----+---
	 *	 01 | 01 | 10 | 11
	 *	 10 | 10 | 11 |+00
	 *	 11 | 11 |+00 |+01
	 *
	 * + means carry. Note how similar the above table is to unbalanced
	 * trinary:
	 *
	 *	a+b | 0 | 1 | 2
	 *	----+---+---+--
	 *	 0  | 0 | 1 | 2
	 *	 1  | 1 | 2 |+0
	 *	 2  | 2 |+0 |+1
	 *
	 * Ignoring carries for the moment, we can map 01 => 0, 10 => 1 and
	 * 11 => 2. To get back to our normal number system, we can subtract the
	 * bias again, except for where carries happen. However, notice that the
	 * number that is left behind IS the number we want! So we just need to
	 * detect when a carry has occured, and we don't have to fix up that
	 * location.
	 *
	 * Getting the carry occurences is done with b ^ c ^ d.
	 * b^c is the standard way to compute the sum of two bits and discarding
	 * the carry. Therefore, if (b^c) is different from d, we know that the
	 * previous stage must have sent us a carry!
	 */

	/* add bias to make binary addition in hardware more closely
	 * match unbalanced trinary addition */
	tri_t c = a + BIAS;

	/* caclulate biased sum with errors */
	tri_t d = b + c;

	/* detect if a carry happened in the previous stage, if one is detected
	 * then that region shouldn't be subtracted in the final step */
	tri_t e = (~(b ^ c ^ d) & BIAS) >> 2;

	/* subtract to counter adding bias in first step and fix errors that
	 * show up in second stage */
	return (d - e) & TRI_BMASK;
}

static inline tri_t tri_bneg(tri_t a)
{
	return 0x2aaaaaaaaaaaaaaaULL - a;
}

#define TRI_B0 0x1540000000000000ULL
static inline tri_t tri_bsl(tri_t a, int i)
{
	return (a << (2 * i)) | (TRI_B0 >> (2 * (31 - i)));
}

static inline tri_t tri_bsr(tri_t a, int i)
{
	return (a >> (2 * i)) | (TRI_B0 << (2 * (31 - i)));
}

static inline tri_t tri_badd(tri_t a, tri_t b)
{
	/* do some biased number magic for partial sum */
	tri_t bsum = tri_bsum(a, b);

	/* subtract bias for full sum. note that bias + 1 is the same as -bias */
	tri_t sum = tri_bsum(bsum, BIAS + 1);
	return sum;
}

static inline tri_t tri_bsub(tri_t a, tri_t b)
{
	return tri_badd(a, tri_bneg(b));
}

static inline tri_t tri_add(tri_t a, tri_t b)
{
	/* convert to biased numbers */
	tri_t ab = tri_bias(a);
	tri_t bb = tri_bias(b);

	/* internal helper */
	tri_t sum = tri_badd(ab, bb);

	/* convert back to balanced numbers */
	tri_t r = tri_unbias(sum);
	return r;
}
#undef BIAS

static inline tri_t tri_sub(tri_t a, tri_t b)
{
	return tri_add(a, tri_neg(b));
}

#define TRI_N13 0b101010
#define TRI_N12 0b101000
#define TRI_N11 0b101001
#define TRI_N10 0b100010
#define TRI_N9  0b100000
#define TRI_N8  0b100001
#define TRI_N7  0b100110
#define TRI_N6  0b100100
#define TRI_N5  0b100101
#define TRI_N4  0b001010
#define TRI_N3  0b001000
#define TRI_N2  0b001001
#define TRI_N1  0b000010
#define TRI_0   0b000000
#define TRI_P1  0b000001
#define TRI_P2  0b000110
#define TRI_P3  0b000100
#define TRI_P4  0b000101
#define TRI_P5  0b011010
#define TRI_P6  0b011000
#define TRI_P7  0b011001
#define TRI_P8  0b010010
#define TRI_P9  0b010000
#define TRI_P10 0b010001
#define TRI_P11 0b010110
#define TRI_P12 0b010100
#define TRI_P13 0b010101

static inline tri_t tri_mul(tri_t a, tri_t b)
{
	/* probably needs a little bit more testing */
	tri_t pa = tri_bias(a);
	tri_t na = tri_bneg(a);
	tri_t p = tri_bias(0);

	for (int i = 0; i < 9; ++i) {
		tri_t m = b & 0x3f;
		b >>= 6;

		switch (m) {
		case TRI_N2:  p = tri_badd(p, na); /* fallthru */
		case TRI_N1:  p = tri_badd(p, na);
			      break;

		case TRI_N5:  p = tri_badd(p, na); /* fallthru */
		case TRI_N4:  p = tri_badd(p, na); /* fallthru */
		case TRI_N3:  p = tri_badd(p, tri_bsl(na, 1));
			      break;

		case TRI_N8:  p = tri_badd(p, na); /* fallthru */
		case TRI_N7:  p = tri_badd(p, na); /* fallthru */
		case TRI_N6:  p = tri_badd(p, tri_bsl(na, 1));
			      p = tri_badd(p, tri_bsl(na, 1));
			      break;

		case TRI_N11: p = tri_badd(p, na); /* fallthru */
		case TRI_N10: p = tri_badd(p, na); /* fallthru */
		case TRI_N9:  p = tri_badd(p, tri_bsl(na, 2));
			      break;

		case TRI_N13: p = tri_badd(p, na); /* fallthru */
		case TRI_N12: p = tri_badd(p, tri_bsl(na, 2));
			      p = tri_badd(p, tri_bsl(na, 1));
			      break;

		case TRI_0:   break;
		case TRI_P2:  p = tri_badd(p, pa); /* fallthru */
		case TRI_P1:  p = tri_badd(p, pa);
			      break;

		case TRI_P5:  p = tri_badd(p, pa); /* fallthru */
		case TRI_P4:  p = tri_badd(p, pa); /* fallthru */
		case TRI_P3:  p = tri_badd(p, tri_bsl(pa, 1));
			      break;

		case TRI_P8:  p = tri_badd(p, pa); /* fallthru */
		case TRI_P7:  p = tri_badd(p, pa); /* fallthru */
		case TRI_P6:  p = tri_badd(p, tri_bsl(pa, 1));
			      p = tri_badd(p, tri_bsl(pa, 1));
			      break;

		case TRI_P11: p = tri_badd(p, pa); /* fallthru */
		case TRI_P10: p = tri_badd(p, pa); /* fallthru */
		case TRI_P9:  p = tri_badd(p, tri_bsl(pa, 2));
			      break;

		case TRI_P13: p = tri_badd(p, pa); /* fallthru */
		case TRI_P12: p = tri_badd(p, tri_bsl(pa, 2));
			      p = tri_badd(p, tri_bsl(pa, 1));
			      break;

		default: printf("misshandled 0x%lx\n", m);
			 abort();
		}
	}

	return tri_unbias(p);
}

#if 0
/* I'll deal with division later, turns out hardware and software division
 * differs */
static inline tri_t tri_div(tri_t a, tri_t b)
{
	/* ditto */
	trival_t ba = tri_to(a);
	trival_t bb = tri_to(b);
	return tri_from(ba / bb);
}

static inline tri_t tri_rem(tri_t a, tri_t b)
{
	trival_t ba = tri_to(a);
	trival_t bb = tri_to(b);
	return tri_from(ba % bb);
}
#endif

/* return sign of whole tri, -1 for negative, 0 for zero, 1 for positive */
static inline int tri_sign(tri_t t)
{
	if (t == 0)
		return 0;

	int lz = __builtin_clzll(t);
	if (lz % 2 == 0)
		return 1;

	return -1;
}

static inline bool tri_eq(tri_t a, tri_t b)
{
	return a == b;
}

static inline bool tri_lt(tri_t a, tri_t b)
{
	tri_t r = tri_sub(a, b);
	int s = tri_sign(r);
	if (s >= 0)
		return false;

	return true;
}

static inline bool tri_le(tri_t a, tri_t b)
{
	return tri_eq(a, b) || tri_lt(a, b);
}

static inline bool tri_gt(tri_t a, tri_t b)
{
	return tri_le(b, a);
}

static inline bool tri_ge(tri_t a, tri_t b)
{
	return tri_lt(b, a);
}

#define tri_illegal_op()\
	do { fprintf(stderr, "illegal op, aborting\n"); abort(); } while (0)

#define tri_unop(o, a)\
	tri_unop_do(_TRIOP3(o, 0), a)

static inline tri_t tri_unop_do(triop_t op, tri_t a)
{

	tri_t n = 0;
	tri_t p = 0;

	tri_t an = tri_ns(a);
	tri_t ap = tri_ps(a);
	tri_t az = tri_zs(a);

	/* handle mapping n */
	switch (GET_TRIOP(op, 0)) {
	case N: n |= an; break;
	case P: p |= an; break;
	case O: /* noop */ break;
	default: tri_illegal_op();
	}

	/* map o */
	switch (GET_TRIOP(op, 1)) {
	case N: n |= az; break;
	case P: p |= az; break;
	case O: /* noop */ break;
	default: tri_illegal_op();
	}

	/* map p */
	switch (GET_TRIOP(op, 2)) {
	case N: n |= ap; break;
	case P: p |= ap; break;
	case O: /* noop */ break;
	default: tri_illegal_op();
	}

	return (TRI_PMASK & p) | (TRI_NMASK & n);
}

#define tri_diop(o0, o1, o2, a, b)\
	tri_diop_do(_TRIOP9(o0, o1, o2), a, b)

static inline tri_t tri_diop_do(triop_t op, tri_t a, tri_t b)
{
	tri_t n = 0;
	tri_t p = 0;

	tri_t an = tri_ns(a);
	tri_t ap = tri_ps(a);
	tri_t az = tri_zs(a);

	tri_t bn = tri_ns(b);
	tri_t bp = tri_ps(b);
	tri_t bz = tri_zs(b);

	for (int i = 0; i < 9; i += 3) {
		/* select map */
		tri_t r = 0;
		switch (i) {
		case 0: r = an; break;
		case 3: r = az; break;
		case 6: r = ap; break;
		}

		/* map n */
		switch (GET_TRIOP(op, i + 0)) {
		case N: n |= r & bn; break;
		case P: p |= r & bn; break;
		case O: /* noop */ break;
		default: tri_illegal_op();
		}

		/* map o */
		switch (GET_TRIOP(op, i + 1)) {
		case N: n |= r & bz; break;
		case P: p |= r & bz; break;
		case O: /* noop */ break;
		default: tri_illegal_op();
		}

		/* map p */
		switch (GET_TRIOP(op, i + 2)) {
		case N: n |= r & bp; break;
		case P: p |= r & bp; break;
		case O: /* noop */ break;
		default: tri_illegal_op();
		}
	}

	return (TRI_PMASK & p) | (TRI_NMASK & n);
}

#undef tri_illegal_op
#endif
