#include <tdump/disassembler.h>
#include <limits.h>
#include <bits.h>

struct disasm_ctx {
	const uint32_t *buf;
	size_t pc;
	size_t len;
};

static const char *get_gpr(tri_t x)
{
	switch (x) {
	case  X0: return  "x0";
	case  X1: return  "sp";
	case  X2: return  "fp";
	case  X3: return  "gp";
	case  X4: return  "a0";
	case  X5: return  "a1";
	case  X6: return  "a2";
	case  X7: return  "a3";
	case  X8: return  "a4";
	case  X9: return  "a5";
	case X10: return  "a6";
	case X11: return  "t0";
	case X12: return  "t1";
	case X13: return  "t2";
	case X14: return  "t3";
	case X15: return  "t4";
	case X16: return  "t5";
	case X17: return  "t6";
	case X18: return  "s0";
	case X19: return  "s1";
	case X20: return  "s2";
	case X21: return  "s3";
	case X22: return  "s4";
	case X23: return  "s5";
	case X24: return  "s6";
	case X25: return  "tp";
	case X26: return  "ra";
	case X27: return  "a7";
	case X28: return  "a8";
	case X29: return  "a9";
	case X30: return "a10";
	case X31: return "a11";
	case X32: return "a12";
	case X33: return "a13";
	case X34: return "a14";
	case X35: return "a15";
	case X36: return "a16";
	case X37: return "a17";
	case X38: return "a18";
	case X39: return "a19";
	case X40: return "a20";
	case X41: return "a21";
	case X42: return "a22";
	case X43: return "a23";
	case X44: return "a24";
	case X45: return  "t7";
	case X46: return  "t8";
	case X47: return  "t9";
	case X48: return "t10";
	case X49: return "t11";
	case X50: return "t12";
	case X51: return "t13";
	case X52: return "t14";
	case X53: return "t15";
	case X54: return "t16";
	case X55: return "t17";
	case X56: return "t18";
	case X57: return "t19";
	case X58: return "t20";
	case X59: return "t21";
	case X60: return "t22";
	case X61: return "t23";
	case X62: return "t24";
	case X63: return  "s7";
	case X64: return  "s8";
	case X65: return  "s9";
	case X66: return "s10";
	case X67: return "s11";
	case X68: return "s12";
	case X69: return "s13";
	case X70: return "s14";
	case X71: return "s15";
	case X72: return "s16";
	case X73: return "s17";
	case X74: return "s18";
	case X75: return "s19";
	case X76: return "s20";
	case X77: return "s21";
	case X78: return "s22";
	case X79: return "s23";
	case X80: return "s24";
	default: return "ill";
	}
}

static void *read_object_file(const char *file, size_t *len)
{
	FILE *f = fopen(file, "rb");
	if (!f) {
		fprintf(stderr, "failed opening simulation file %s\n", file);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long s = ftell(f);
	if (s == LONG_MAX) {
		fprintf(stderr, "unable to get file size of %s\n", file);
		return NULL;
	}

	if (len)
		*len = s;

	fseek(f, 0, SEEK_SET);
	char *buf = malloc(s);
	if (!buf)
		return NULL;

	fread(buf, s, 1 , f);
	fclose(f);

	return buf;
}

#define DEFAULT_PREFIX "%zu\t"

static void disasm_lui(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, imm18;
	parse_u(i, &rd, &imm18);

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm18);
	imm[l] = '\0';
	printf(DEFAULT_PREFIX "lui %s, %s\n",
			ctx->pc, get_gpr(rd), imm);
}

static void disasm_store(struct disasm_ctx *ctx, tri_t i)
{
	tri_t imm4, fn0, rs1, rs2, imm5;
	parse_s(i, &imm4, &fn0, &rs1, &rs2, &imm5);

	tri_t imm9 = tri_sl(imm4, 5) | imm5;

	int w = tri_get_trit(fn0, 4);
	char *width = NULL;
	switch (w) {
		case 0: width = "t"; break;
		case 1: width = "w"; break;
		default: width = "ill"; break;
	}

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm9);
	imm[l] = '\0';
	printf(DEFAULT_PREFIX "st %s, %s, %s(%s)\n",
			ctx->pc, width, get_gpr(rs1), imm, get_gpr(rs2));
}

static void disasm_load(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, fn0, rs1, imm9;
	parse_i(i, &rd, &fn0, &rs1, &imm9);

	int w = tri_get_trit(fn0, 4);
	char *width = NULL;
	switch (w) {
		case 0: width = "t"; break;
		case 1: width = "w"; break;
		default: width = "ill"; break;
	}

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm9);
	imm[l] = '\0';
	printf(DEFAULT_PREFIX "ld %s, %s, %s(%s)\n",
			ctx->pc, width, get_gpr(rd), imm, get_gpr(rs1));
}

static void disasm_op_imm(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, fn0, rs1, imm9;
	parse_i(i, &rd, &fn0, &rs1, &imm9);

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm9);
	imm[l] = '\0';

	switch (fn0) {
		case OP_IMM_ADDI:
			printf(DEFAULT_PREFIX "addi %s, %s, %s\n",
					ctx->pc, get_gpr(rd), get_gpr(rs1), imm);
			break;

		default:
			printf(DEFAULT_PREFIX "unknown/unimp op_imm\n",
					ctx->pc);
	}
}

static void disasm_op(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, fn0, rs1, rs2, fn5;
	parse_r(i, &rd, &fn0, &rs1, &rs2, &fn5);

	switch (fn5) {
		case 0:
		switch (fn0) {
			case OP_ADD:
				printf(DEFAULT_PREFIX "add %s, %s, %s\n",
						ctx->pc,
						get_gpr(rd),
						get_gpr(rs1),
						get_gpr(rs2));
				break;

			case OP_SUB:
				printf(DEFAULT_PREFIX "sub %s, %s, %s\n",
						ctx->pc,
						get_gpr(rd),
						get_gpr(rs1),
						get_gpr(rs2));
				break;

			default:
				printf(DEFAULT_PREFIX "unknown/unimp op\n",
						ctx->pc);
		}
		break;

		default: printf(DEFAULT_PREFIX "unknown/unimp op metaclass\n",
					 ctx->pc);
	}
}

static void disasm_jalr(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, fn0, rs1, imm9;
	parse_i(i, &rd, &fn0, &rs1, &imm9);

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm9);
	imm[l] = '\0';

	switch (fn0) {
		case 0:
			printf(DEFAULT_PREFIX "jalr %s, %s(%s)\n",
					ctx->pc, get_gpr(rd), imm, get_gpr(rs1));
		break;
		default: printf(DEFAULT_PREFIX "unknown/unimp jalr\n", ctx->pc);
	}
}

static void disasm_branch(struct disasm_ctx *ctx, tri_t i)
{
	tri_t imm4, fn0, rs1, rs2, imm5;
	parse_s(i, &imm4, &fn0, &rs1, &rs2, &imm5);

	tri_t imm9 = tri_sl(imm4, 5) | imm5;

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm9);
	imm[l] = '\0';

	switch (fn0) {
		case BRANCH_BLT:
			printf(DEFAULT_PREFIX "blt %s, %s, %s\n",
					ctx->pc, get_gpr(rs1), get_gpr(rs2), imm);
		break;
		default: printf(DEFAULT_PREFIX "unknown/unimp branch\n", ctx->pc);
	}
}

static void disasm_auipc(struct disasm_ctx *ctx, tri_t i)
{
	tri_t rd, imm18;
	parse_u(i, &rd, &imm18);

	char imm[256];
	size_t l = tri_fmt_default(imm, 256, imm18);
	imm[l] = '\0';

	printf(DEFAULT_PREFIX "auipc %s, %s\n",
			ctx->pc, get_gpr(rd), imm);
}

static tri_t read1(struct disasm_ctx *ctx, size_t off)
{
	tri_t t = (tri_t)ctx->buf[off];
	return tri_mask(t, 9);
}

static tri_t read3(struct disasm_ctx *ctx, size_t off)
{
	tri_t t0 = read1(ctx, off + 0);
	tri_t t1 = read1(ctx, off + 1);
	tri_t t2 = read1(ctx, off + 2);
	return t0 | tri_sl(t1, 9) | tri_sl(t2, 18);
}

int disassemble(const char *file)
{
	size_t len = 0;
	const uint32_t *buf = read_object_file(file, &len);
	/* somewhat specific but we know that each tryte is mapped to uin32_t */
	struct disasm_ctx ctx = {.buf = buf, .pc = 0, .len = len / sizeof(uint32_t)};
	while (ctx.pc < ctx.len) {
		tri_t i = read3(&ctx, ctx.pc);

		switch (parse_opcode(i)) {
			case OPCODE_LUI: disasm_lui(&ctx, i); break;
			case OPCODE_STORE: disasm_store(&ctx, i); break;
			case OPCODE_LOAD: disasm_load(&ctx, i); break;
			//case OPCODE_SYSTEM: disasm_system(&ctx, i); break;
			case OPCODE_OP_IMM: disasm_op_imm(&ctx, i); break;
			case OPCODE_OP: disasm_op(&ctx, i); break;
			case OPCODE_JALR: disasm_jalr(&ctx, i); break;
			case OPCODE_BRANCH: disasm_branch(&ctx, i); break;
			case OPCODE_AUIPC: disasm_auipc(&ctx, i); break;
			default:
				printf(DEFAULT_PREFIX "unimp/illegal\n", ctx.pc);
				break;
		}
		ctx.pc += 3;
	}

	free((void *)buf);
	return 0;
}
