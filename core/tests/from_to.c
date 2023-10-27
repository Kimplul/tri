#include <tri.h>

int main()
{
	/* increment by prime to hopefully somewhat randomly test patterns */
	for (int64_t i = TRI_MIN; i < TRI_MAX; i += 1048009) {
		tri_t t = tri_from(i);
		assert(tri_to(t) == i);
	}
}
