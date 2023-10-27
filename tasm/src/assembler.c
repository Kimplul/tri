#include <tasm/assembler.h>
#include <tasm/parser.h>
#include <tasm/bits.h>

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

struct asm_ctx {
	size_t size;
	size_t idx;
	tri_t *buf;
};

static void emit(struct asm_ctx *ctx, tri_t i)
{
	if (ctx->size == ctx->idx) {
		ctx->size *= 2;
		ctx->buf = realloc(ctx->buf, ctx->size * sizeof(tri_t));
	}

	ctx->buf[ctx->idx++] = i;
}

static bool check_imm(tri_t imm, size_t n)
{
	/* check that we can fit imm into n trits */
	return tri_mask(imm, n) == imm;
}

tri_t parse_imm(const char *imm)
{
	size_t len = strlen(imm);
	if (len < 2) {
		/* must be base 10 */
		char *end = NULL;
		int64_t val = strtoll(imm, &end, 10);
		assert(imm + len == end);
		return tri_from(val);
	}

	if (strncmp(imm, "0t", 2) == 0) {
		/* must be raw trinary */
		return tri_parse_default(imm, len);
	}

	if (strncmp(imm, "0h", 2) == 0) {
		/* must be heptavintimal */
		fprintf(stderr, "heptavintimal not yet implemented\n");
		abort();
		return 0;
	}

	/* try to let strtoll figure out */
	char *end = NULL;
	int64_t val = strtoll(imm, &end, 0);
	if (imm + len == end)
		return tri_from(val);


	fprintf(stderr, "unrecognised immediate: %s\n", imm);
	abort();
	return 0;
}

void emit_r(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t fn0, enum gpr_num rs1,
		enum gpr_num rs2, tri_t fn5)
{
	tri_t xrd  = gpr_tri(rd );
	tri_t xrs1 = gpr_tri(rs1);
	tri_t xrs2 = gpr_tri(rs2);
	tri_t i = build_r(opcode, xrd, fn0, xrs1, xrs2, fn5);
	emit(ctx, i);
}

void emit_i(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t fn0, enum gpr_num rs1, tri_t imm9)
{
	tri_t xrd   = gpr_tri(rd );
	tri_t xrs1  = gpr_tri(rs1);
	if (!check_imm(imm9, 9)) {
		fprintf(stderr, "immediate %lx doesn't fit into 9 trits\n", imm9);
		abort();
		return;
	}
	tri_t i = build_i(opcode, xrd, fn0, xrs1, imm9);
	emit(ctx, i);
}

void emit_s(struct asm_ctx *ctx, tri_t opcode,
		tri_t fn0, enum gpr_num rs1, enum gpr_num rs2, tri_t imm9)
{
	tri_t xrs1  = gpr_tri(rs1);
	tri_t xrs2  = gpr_tri(rs2);
	if (!check_imm(imm9, 9)) {
		fprintf(stderr, "immediate %lx doesn't fit into 9 trits\n", imm9);
		abort();
		return;
	}
	tri_t imm4 = tri_mask(imm9, 4);
	tri_t imm5 = tri_mask(tri_sr(imm9, 4), 5);

	tri_t i = build_s(opcode, imm4, fn0, xrs1, xrs2, imm5);
	emit(ctx, i);
}

void emit_u(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t imm18)
{
	tri_t xrd = gpr_tri(rd);
	if (!check_imm(imm18, 18)) {
		fprintf(stderr, "immediate %lx does not fit into 18 trits\n", imm18);
		abort();
		return;
	}

	tri_t i = build_u(opcode, xrd, imm18);
	emit(ctx, i);
}

void emit_d(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, enum gpr_num rs1, enum gpr_num rs2, tri_t imm10)
{
	tri_t xrd  = gpr_tri(rd );
	tri_t xrs1 = gpr_tri(rs1);
	tri_t xrs2 = gpr_tri(rs2);

	if (!check_imm(imm10, 10)) {
		fprintf(stderr, "immediate %lx does not fit into 10 trits\n", imm10);
		abort();
		return;
	}

	tri_t imm0 = tri_mask(imm10, 5);
	tri_t imm1 = tri_mask(tri_sr(imm10, 5), 5);

	tri_t i = build_r(opcode, xrd, imm0, xrs1, xrs2, imm1);
	emit(ctx, i);
}

static char *tasm_basename(const char *file)
{
	size_t l = strlen(file);
	size_t n = l - 1;
	while (--n) {
		if (file[n] == '/')
			break;
	}

	if (n == 0)
		return strdup(file);

	return strndup(file + n + 1, l - n);
}

static char *tasm_dirname(const char *file)
{
	size_t l = strlen(file);
	size_t n = l - 1;
	while (--n) {
		if (file[n] == '/')
			break;
	}

	return strndup(file, n);
}

static char *tasm_cwdname()
{
	size_t size;
	long path_max = pathconf(".", _PC_PATH_MAX);
	if (path_max == -1)
		size = 1024;
	else
		size = (size_t)path_max;

	char *buf = malloc(size);
	if (!buf)
		return NULL;

	if (!getcwd(buf, size)) {
		fprintf(stderr, "%s\n", strerror(errno));
		free(buf);
		return NULL;
	}

	return buf;
}

static char *read_file(const char *file, FILE *f)
{
	fseek(f, 0, SEEK_END);
	/** @todo check how well standardized this actually is */
	long s = ftell(f);
	if (s == LONG_MAX) {
		fprintf(stderr, "%s might be a directory", file);
		return NULL;
	}

	fseek(f, 0, SEEK_SET);

	char *buf = malloc(s + 1);
	if (!buf)
		return NULL;

	fread(buf, s + 1, 1, f);
	/* remember terminating null */
	buf[s] = 0;
	return buf;
}

static int process(struct asm_ctx *ctx, const char *file)
{
	FILE *f = fopen(file, "rb");
	if (!f) {
		fprintf(stderr, "failed opening %s: %s\n", file, strerror(errno));
		return -1;
	}

	const char *buf = read_file(file, f);
	fclose(f);

	if (!buf)
		return -1;

	struct parser *p = create_parser();
	parse(p, ctx, file, buf);
	bool failed = p->failed;
	destroy_parser(p);

	free((void *)buf);

	if (failed)
		return -1;

	return 0;
}

/** @todo eventually take context */
int process_file(struct asm_ctx *ctx, const char *file)
{
	const char *base = tasm_basename(file);
	const char *dir = tasm_dirname(file);

	const char *cwd = tasm_cwdname();

	chdir(dir);
	int res = process(ctx, base);
	chdir(cwd);

	free((void *)base);
	free((void *)dir);
	free((void *)cwd);

	return res;
}

int assemble(const char *outfile, const char *infile)
{
	/** @todo cleanup */
	struct asm_ctx ctx = {.size = 1, .buf = malloc(sizeof(tri_t)), .idx = 0};
	int ret = process_file(&ctx, infile);
	if (ret)
		return ret;

	FILE *f = fopen(outfile, "wb");
	if (!f)
		return -1;

	for (size_t i = 0; i < ctx.idx; ++i) {
		tri_t t = ctx.buf[i];
		/* output trytewise LE */
		uint32_t t0 = tri_mask(t, 9);
		uint32_t t1 = tri_mask(tri_sr(t,  9), 9);
		uint32_t t2 = tri_mask(tri_sr(t, 18), 9);

		size_t c0 = fwrite(&t0, sizeof(t0), 1, f);
		size_t c1 = fwrite(&t1, sizeof(t1), 1, f);
		size_t c2 = fwrite(&t2, sizeof(t2), 1, f);

		/* better error handling would be nice */
		assert(c0);
		assert(c1);
		assert(c2);
	}

	fclose(f);
	free(ctx.buf);
}

void check_shift(tri_t shmt)
{
	int64_t v = tri_from(shmt);
	assert(v < 27);
}

tri_t check_nop(const char *nop)
{
	tri_t r = 0;
	size_t count = 0;
	size_t len = strlen(nop);
	for (size_t i = 0; i < len; ++i) {
		switch (nop[i]) {
		case 'o':
		case 'O':
		case '0': tri_set_trit(r, i,  0); break;

		case 'n':
		case 'N':
		case 'i': tri_set_trit(r, i, -1); break;

		case 'p':
		case 'P':
		case '1': tri_set_trit(r, i,  1); break;

		case ' ': continue;
		default:
			fprintf(stderr, "invalid character in unop format: %c\n", nop[i]);
			abort();
		}

		count++;
	}

	assert(count == 3);
	return r;
}

tri_t check_nop3(const char *nop)
{
	tri_t r = 0;
	size_t count = 0;
	size_t len = strlen(nop);
	for (size_t i = 0; i < len; ++i) {
		switch (nop[i]) {
		case 'o':
		case 'O':
		case '0': tri_set_trit(r, i,  0); break;

		case 'n':
		case 'N':
		case 'i': tri_set_trit(r, i, -1); break;

		case 'p':
		case 'P':
		case '1': tri_set_trit(r, i,  1); break;

		case ' ': continue;
		default:
			fprintf(stderr, "invalid character in unop format: %c\n", nop[i]);
			abort();
		}

		count++;
	}

	assert(count == 9);
	return r;
}

tri_t check_csr(const char *csr)
{
	/** @todo only mpower supported for now, will have to work on this */
	assert(strcmp(csr, "mpower"));
	return 0;
}

tri_t check_width(const char *width)
{
	if (strncmp(width, "w", 1) == 0)
		return WIDTH_W;

	if (strncmp(width, "t", 1) == 0)
		return WIDTH_T;

	fprintf(stderr, "illegal width specifier: %s\n", width);
	abort();
	return 0;
}

void emit_reloc(struct asm_ctx *ctx, enum asm_reloc reloc, const char *name)
{
	/** @todo implement */
}

void emit_label(struct asm_ctx *ctx, const char *name)
{
	/** @todo implement */
}
