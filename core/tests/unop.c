#include <tri.h>

int main()
{
	/* technically speaking there are only 27 cases to test, and they could
	 * potentially all checked for manually, but this is good enough for now
	 */
	tri_t t = tri_parse_default("i01", 3);

	tri_t r = tri_unop(NOP, t);
	assert(tri_eq(r, t));

	r = tri_unop(NNN, t);
	assert(tri_eq(r, tri_from(TRI_MIN)));

	r = tri_unop(OOO, t);
	assert(tri_eq(r, tri_from(0)));

	r = tri_unop(PPP, t);
	assert(tri_eq(r, tri_from(TRI_MAX)));

	r = tri_unop(PON, t);
	assert(tri_eq(r, tri_parse_default("10i", 3)));
}
