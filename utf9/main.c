#include <utf9.h>

#define STRING "𐍈𐍈𐍈𐍈"
int main()
{
	/* not strictly portable, assumes locale is utf8, etc. */
	const char *s = STRING;
	tri_t t[20];
	size_t c = 0;
	/* note 20 * 3, as t is in tri words but each word is three 'chars' */
	/* unsure if this is more or less confusing than using the word sizes
	 * directly */
	size_t l = utf8_to_utf9(t, 20 * 3, s, sizeof(STRING), &c);
	printf("utf8->utf9: %llu characters to %llu\n", c, l);

	char r[20];
	/* hmm, currently it's kind of difficult to tell if we just ran out of
	 * buffer space or failed due to some other issue. */
	l = utf9_to_utf8(r, 20, t, l, &c);
	printf("utf9->utf8: %llu characters to %llu\n", c, l);

	printf("original  : %s\n", s);
	printf("converted : %s\n", r);
}
