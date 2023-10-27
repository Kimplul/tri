#include <tri.h>

static tri_t f;

static tri_t filter(tri_t t)
{
	tri_t r = tri_diop(OON, OOO, OOP, t, f);
	return r;
}

int main()
{
	/* very much not enough testing */
	f = tri_parse_default("111111111", 9);

	tri_t a = tri_parse_default("iii000111", 9);
	tri_t b = tri_parse_default("i01i01i01", 9);

	tri_t r = tri_diop(NNN, NNN, NNN, a, b);
	assert(tri_eq(filter(r), tri_parse_default("iiiiiiiii", 9)));
}
