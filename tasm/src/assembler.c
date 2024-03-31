#include <triscv/csr.h>
#include <tasm/assembler.h>
#include <tasm/parser.h>
#include <bits.h>

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

struct asm_symbol {
	const char *name;
	size_t offset;
};

struct asm_reloc {
	enum asm_reloc_kind kind;
	const char *sym;
	size_t offset;
};

struct asm_ctx {
	size_t size;
	size_t idx;
	tri_t *buf;

	size_t sym_max;
	size_t sym_count;
	struct asm_symbol *syms;

	size_t reloc_max;
	size_t reloc_count;
	struct asm_reloc *relocs;
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

	/* low five */
	tri_t imm5 = tri_mask(imm9, 5);
	/* high four */
	tri_t imm4 = tri_mask(tri_sr(imm9, 5), 4);

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

static struct asm_ctx *asm_ctx_create()
{
	struct asm_ctx *ctx = malloc(sizeof(struct asm_ctx));
	/* code buffer */
	ctx->size = 1;
	ctx->buf = malloc(sizeof(tri_t));
	ctx->idx = 0;

	/* relocations */
	ctx->reloc_max = 1;
	ctx->relocs = malloc(sizeof(struct asm_reloc));
	ctx->reloc_count = 0;

	/* symbols */
	ctx->sym_max = 1;
	ctx->syms = malloc(sizeof(struct asm_reloc));
	ctx->sym_count = 0;

	return ctx;
}

static void asm_ctx_relocs_destroy(struct asm_ctx *ctx)
{
	for (size_t i = 0; i < ctx->reloc_count; ++i) {
		free((void *)ctx->relocs[i].sym);
	}

	free(ctx->relocs);
}

static void asm_ctx_syms_destroy(struct asm_ctx *ctx)
{
	for (size_t i = 0; i < ctx->sym_count; ++i) {
		free((void *)ctx->syms[i].name);
	}

	free(ctx->syms);
}

static void asm_ctx_destroy(struct asm_ctx *ctx)
{
	free(ctx->buf);
	asm_ctx_relocs_destroy(ctx);
	asm_ctx_syms_destroy(ctx);
	free(ctx);
}

/* convert instruction index (as used by ctx->idx) to addresses */
static size_t asm_addr(size_t o)
{
	return o * 3;
}

static void fix_reloc_la(struct asm_ctx *ctx, size_t ro, size_t so)
{
	tri_t t = tri_from(so);
	/* 9 lowest */
	tri_t lo = tri_mask(t, 9);
	/* 18 highest */
	tri_t hi = tri_mask(tri_sr(t, 9), 18);

	/* lui, assume zero-initialized immediate */
	tri_t lui = ctx->buf[ro];
	assert(parse_opcode(lui) == OPCODE_LUI);
	tri_t rd, imm;
	parse_u(lui, &rd, &imm);
	assert(imm == 0);
	ctx->buf[ro] = build_u(OPCODE_LUI, rd, hi);

	/* addi */
	tri_t addi = ctx->buf[ro + 1];
	assert(parse_opcode(addi) == OPCODE_OP_IMM);
	tri_t fn0, rs1;
	parse_i(addi, &rd, &fn0, &rs1, &imm);
	assert(fn0 == OP_IMM_ADDI);
	assert(imm == 0);
	ctx->buf[ro + 1] = build_i(OPCODE_OP_IMM, rd, fn0, rs1, lo);
}

static void fix_reloc_b(struct asm_ctx *ctx, size_t ro, size_t so)
{
	int64_t off = asm_addr(so) - asm_addr(ro);
	tri_t t = tri_from(off);
	if (tri_mask(t, 9) != t) {
		/* should really be line based rather than offset, but good
		 * enough for now */
		fprintf(stderr, "branch offset at %llu too large\n",
				(unsigned long long)ro);
		abort();
	}

	/* low five */
	tri_t lo = tri_mask(t, 5);
	/* high four */
	tri_t hi = tri_mask(tri_sr(t, 5), 4);

	tri_t b = ctx->buf[ro];
	assert(parse_opcode(b) == OPCODE_BRANCH);

	tri_t imm4, fn0, rs1, rs2, imm5;
	parse_s(b, &imm4, &fn0, &rs1, &rs2, &imm5);
	assert(imm4 == 0 && imm5 == 0);

	ctx->buf[ro] = build_s(OPCODE_BRANCH, hi, fn0, rs1, rs2, lo);
}

static void fix_reloc_j(struct asm_ctx *ctx, size_t ro, size_t so)
{
	/* internal offsets are instruction indexes, so convert to address */
	int64_t off = asm_addr(so) - asm_addr(ro);
	tri_t t = tri_from(off);
	if (tri_mask(t, 18) != t) {
		fprintf(stderr, "jump offset at %llu too large\n",
				(unsigned long long)ro);
		abort();
	}

	tri_t j = ctx->buf[ro];
	assert(parse_opcode(j) == OPCODE_JAL);

	tri_t rd, imm18;
	parse_u(j, &rd, &imm18);
	assert(imm18 == 0);

	ctx->buf[ro] = build_u(OPCODE_JAL, rd, t);
}

static void fix_reloc_call(struct asm_ctx *ctx, size_t ro, size_t so)
{
	int64_t off = asm_addr(so) - asm_addr(ro);
	tri_t t = tri_from(off);

	tri_t a = ctx->buf[ro];
	assert(parse_opcode(a) == OPCODE_AUIPC);

	tri_t rd, imm18;
	parse_u(a, &rd, &imm18);
	assert(imm18 == 0);

	ctx->buf[ro] = build_u(OPCODE_AUIPC, rd, tri_sr(t, 9));

	tri_t j = ctx->buf[ro + 1];
	assert(parse_opcode(j) == OPCODE_JALR);
	tri_t fn0, rs1, imm;
	parse_i(j, &rd, &fn0, &rs1, &imm);
	ctx->buf[ro + 1] = build_i(OPCODE_JALR, rd, fn0, rs1, tri_mask(t, 9));
}

static int try_fix_reloc(struct asm_ctx *ctx, struct asm_reloc r)
{
	/* ideally this would probably be a hashmap, but good enough for now */
	for (size_t i = 0; i < ctx->sym_count; ++i) {
		struct asm_symbol s = ctx->syms[i];
		if (strcmp(s.name, r.sym) != 0)
			continue;

		size_t ro = r.offset;
		size_t so = s.offset;
		/* matching */
		switch (r.kind) {
			case RELOC_LA: fix_reloc_la(ctx, ro, so); break;
			case RELOC_B: fix_reloc_b(ctx, ro, so); break;
			case RELOC_J: fix_reloc_j(ctx, ro, so); break;
			case RELOC_CALL: fix_reloc_call(ctx, ro, so); break;
			default: fprintf(stderr, "unimplemented reloc: %d\n", r.kind);
				 abort();
		}
		return 0;
	}

	/* we didn't find a symbol matching reloc */
	return 1;
}

static int fix_relocs(struct asm_ctx *ctx)
{
	for (size_t i = 0; i < ctx->reloc_count; ++i) {
		struct asm_reloc r = ctx->relocs[i];
		if (try_fix_reloc(ctx, r)) {
			/* we were unable to fulfill this reloc, fail */
			fprintf(stderr, "unable to fulfill reloc for %s\n", r.sym);
			return 1;
		}
	}

	return 0;
}

int assemble(const char *outfile, const char *infile)
{
	/** @todo cleanup */
	struct asm_ctx *ctx = asm_ctx_create();
	int ret = process_file(ctx, infile);
	if (ret)
		return ret;

	ret = fix_relocs(ctx);
	if (ret)
		return ret;

	FILE *f = fopen(outfile, "wb");
	if (!f)
		return -1;

	for (size_t i = 0; i < ctx->idx; ++i) {
		tri_t t = ctx->buf[i];
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
	asm_ctx_destroy(ctx);
	return 0;
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
	if (strcmp(csr, "mpower"))
		return tri_from(CSR_MPOWER);

	if (strcmp(csr, "satpp"))
		return tri_from(CSR_SATPP);

	if (strcmp(csr, "satpo"))
		return tri_from(CSR_SATPO);

	if (strcmp(csr, "satpn"))
		return tri_from(CSR_SATPN);

	assert(0);
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

void emit_reloc(struct asm_ctx *ctx, enum asm_reloc_kind reloc, const char *name)
{
	if (ctx->reloc_count >= ctx->reloc_max) {
		ctx->reloc_max *= 2;
		ctx->relocs = realloc(ctx->relocs, ctx->reloc_max * sizeof(struct asm_reloc));
	}

	ctx->relocs[ctx->reloc_count++] = (struct asm_reloc){
		.kind = reloc,
		.sym = strdup(name),
		.offset = ctx->idx
	};
}

void emit_label(struct asm_ctx *ctx, const char *name)
{
	if (ctx->sym_count >= ctx->sym_max) {
		ctx->sym_max *= 2;
		ctx->syms = realloc(ctx->syms, ctx->sym_max * sizeof(struct asm_symbol));
	}

	ctx->syms[ctx->sym_count++] = (struct asm_symbol){
		.name = strdup(name),
		.offset = ctx->idx
	};
}
