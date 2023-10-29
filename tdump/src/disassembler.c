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
	case  X1: return  "x1";
	case  X2: return  "x2";
	case  X3: return  "x3";
	case  X4: return  "x4";
	case  X5: return  "x5";
	case  X6: return  "x6";
	case  X7: return  "x7";
	case  X8: return  "x8";
	case  X9: return  "x9";
	case X10: return "x10";
	case X11: return "x11";
	case X12: return "x12";
	case X13: return "x13";
	case X14: return "x14";
	case X15: return "x15";
	case X16: return "x16";
	case X17: return "x17";
	case X18: return "x18";
	case X19: return "x19";
	case X20: return "x20";
	case X21: return "x21";
	case X22: return "x22";
	case X23: return "x23";
	case X24: return "x24";
	case X25: return "x25";
	case X26: return "x26";
	case X27: return "x27";
	case X28: return "x28";
	case X29: return "x29";
	case X30: return "x30";
	case X31: return "x31";
	case X32: return "x32";
	case X33: return "x33";
	case X34: return "x34";
	case X35: return "x35";
	case X36: return "x36";
	case X37: return "x37";
	case X38: return "x38";
	case X39: return "x39";
	case X40: return "x40";
	case X41: return "x41";
	case X42: return "x42";
	case X43: return "x43";
	case X44: return "x44";
	case X45: return "x45";
	case X46: return "x46";
	case X47: return "x47";
	case X48: return "x48";
	case X49: return "x49";
	case X50: return "x50";
	case X51: return "x51";
	case X52: return "x52";
	case X53: return "x53";
	case X54: return "x54";
	case X55: return "x55";
	case X56: return "x56";
	case X57: return "x57";
	case X58: return "x58";
	case X59: return "x59";
	case X60: return "x60";
	case X61: return "x61";
	case X62: return "x62";
	case X63: return "x63";
	case X64: return "x64";
	case X65: return "x65";
	case X66: return "x66";
	case X67: return "x67";
	case X68: return "x68";
	case X69: return "x69";
	case X70: return "x70";
	case X71: return "x71";
	case X72: return "x72";
	case X73: return "x73";
	case X74: return "x74";
	case X75: return "x75";
	case X76: return "x76";
	case X77: return "x77";
	case X78: return "x78";
	case X79: return "x79";
	case X80: return "x80";
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
			//case OPCODE_SYSTEM: disasm_system(&ctx, i); break;
			case OPCODE_OP_IMM: disasm_op_imm(&ctx, i); break;
			default:
				printf(DEFAULT_PREFIX "unimp/illegal\n", ctx.pc);
				break;
		}
		ctx.pc += 3;
	}

	free((void *)buf);
	return 0;
}
