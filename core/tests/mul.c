#include <tri.h>
#include <string.h>

int main(int argc, char *argv[])
{
	assert(argc == 2);
	char *s = argv[1];
	tri_t a = tri_parse_default(s, strlen(s));
	tri_t one = tri_from(1);

	for (int64_t i = -13; i <= 13; ++i) {
		tri_t b = tri_from(i);
		b = tri_mul(b, one);
		assert(tri_to(b) == i);
	}

	int64_t ba = tri_to(a);

	for (size_t i = 0; i < 1000000000; ++i)
		a = tri_mul(a, one);

	assert(ba == tri_to(a));

	char r[32];
	size_t l = tri_fmt_default(r, 32, a);
	r[l] = '\0';
	printf("%s\n", r);
}
