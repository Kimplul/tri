/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

%{

/* get access to fileno to avoid warnings with flex */
#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <tasm/assembler.h>
#include <tasm/parser.h>
#include <bits.h>
#include <regs.h>
#include <tri.h>

%}

%locations

%define parse.trace
%define parse.error verbose
%define api.pure full
%define lr.type ielr

%lex-param {void *scanner} {struct parser *parser}
%parse-param {void *scanner} {struct parser *parser} {struct asm_ctx *ctx}

%union {
	const char *str;
	enum gpr_num gpr;
	tri_t tri;
};

%token <tri> imm
%token <str> label
%token <str> str
%token <str> id

%token COMMA ","
%token LPAREN "("
%token RPAREN ")"

%token set
%token include
%nterm <gpr> gpr;
%nterm <str> width addr csr

/* regs */
%token x0 x1 x2 x3 x4 x5 x6 x7 x8 x9
%token x10 x11 x12 x13 x14 x15 x16 x17 x18 x19
%token x20 x21 x22 x23 x24 x25 x26 x27 x28 x29
%token x30 x31 x32 x33 x34 x35 x36 x37 x38 x39
%token x40 x41 x42 x43 x44 x45 x46 x47 x48 x49
%token x50 x51 x52 x53 x54 x55 x56 x57 x58 x59
%token x60 x61 x62 x63 x64 x65 x66 x67 x68 x69
%token x70 x71 x72 x73 x74 x75 x76 x77 x78 x79
%token x80

/* i */
%token addi slti sgei seqi snei
%token unop diop
%token slli srli sll srl
%token add sub
%token slt sge seq sne
%token lui auipc
%token jal jalr
%token beq bne blt bge
%token ld st
%token ecall ebreak pcall
%token fence
/* meta */
%token li la nop

/* m (avoid name clash with stdlib div) */
%token mul diV rem

/* a */
%token stt cst ent cat

/* Zcsr */
%token csrrw csrrs csrrc

%{

struct file_ctx {
	const char *fname;
	const char *fbuf;
};

struct src_loc {
	int first_line;
	int last_line;
	int first_col;
	int last_col;
};

struct src_issue {
	struct src_loc loc;
	struct file_ctx fctx;
};

/** Modifies the signature of yylex to fit our parser better. */
#define YY_DECL int yylex(YYSTYPE *yylval, YYLTYPE *yylloc, \
	                  void *yyscanner, struct parser *parser)

/**
 * Declare yylex.
 *
 * @param yylval Bison current value.
 * @param yylloc Bison location info.
 * @param yyscanner Flex scanner.
 * @param parser Current parser state.
 * @return \c 0 when succesful, \c 1 otherwise.
 * More info on yylex() can be found in the flex manual.
 */
YY_DECL;

/**
 * Convert bison location info to our own source location info.
 *
 * @param yylloc Bison location info.
 * @return Internal location info.
 */
static struct src_loc to_src_loc(YYLTYPE *yylloc);

/**
 * Print parsing error.
 * Automatically called by bison.
 *
 * @param yylloc Location of error.
 * @param lexer Lexer.
 * @param parser Parser state.
 * @param msg Message to print.
 */
static void yyerror(YYLTYPE *yylloc, void *lexer,
		struct parser *parser, struct asm_ctx *ctx, const char *msg);

%}

%start input;
%%

width
	: id

/* eventually we might allow jumping to immediate addresses, but for now require
 * that a label always be used */
addr
	: id

/* lexer makes sure the abi names are correct */
gpr
	: x0	{$$ =  X0_NUM;}
	| x1	{$$ =  X1_NUM;}
	| x2	{$$ =  X2_NUM;}
	| x3	{$$ =  X3_NUM;}
	| x4	{$$ =  X4_NUM;}
	| x5	{$$ =  X5_NUM;}
	| x6	{$$ =  X6_NUM;}
	| x7	{$$ =  X7_NUM;}
	| x8	{$$ =  X8_NUM;}
	| x9	{$$ =  X9_NUM;}
	| x10	{$$ = X10_NUM;}
	| x11	{$$ = X11_NUM;}
	| x12	{$$ = X12_NUM;}
	| x13	{$$ = X13_NUM;}
	| x14	{$$ = X14_NUM;}
	| x15	{$$ = X15_NUM;}
	| x16	{$$ = X16_NUM;}
	| x17	{$$ = X17_NUM;}
	| x18	{$$ = X18_NUM;}
	| x19	{$$ = X19_NUM;}
	| x20	{$$ = X20_NUM;}
	| x21	{$$ = X21_NUM;}
	| x22	{$$ = X22_NUM;}
	| x23	{$$ = X23_NUM;}
	| x24	{$$ = X24_NUM;}
	| x25	{$$ = X25_NUM;}
	| x26	{$$ = X26_NUM;}
	| x27	{$$ = X27_NUM;}
	| x28	{$$ = X28_NUM;}
	| x29	{$$ = X29_NUM;}
	| x30	{$$ = X30_NUM;}
	| x31	{$$ = X31_NUM;}
	| x32	{$$ = X32_NUM;}
	| x33	{$$ = X33_NUM;}
	| x34	{$$ = X34_NUM;}
	| x35	{$$ = X35_NUM;}
	| x36	{$$ = X36_NUM;}
	| x37	{$$ = X37_NUM;}
	| x38	{$$ = X38_NUM;}
	| x39	{$$ = X39_NUM;}
	| x40	{$$ = X40_NUM;}
	| x41	{$$ = X41_NUM;}
	| x42	{$$ = X42_NUM;}
	| x43	{$$ = X43_NUM;}
	| x44	{$$ = X44_NUM;}
	| x45	{$$ = X45_NUM;}
	| x46	{$$ = X46_NUM;}
	| x47	{$$ = X47_NUM;}
	| x48	{$$ = X48_NUM;}
	| x49	{$$ = X49_NUM;}
	| x50	{$$ = X50_NUM;}
	| x51	{$$ = X51_NUM;}
	| x52	{$$ = X52_NUM;}
	| x53	{$$ = X53_NUM;}
	| x54	{$$ = X54_NUM;}
	| x55	{$$ = X55_NUM;}
	| x56	{$$ = X56_NUM;}
	| x57	{$$ = X57_NUM;}
	| x58	{$$ = X58_NUM;}
	| x59	{$$ = X59_NUM;}
	| x60	{$$ = X60_NUM;}
	| x61	{$$ = X61_NUM;}
	| x62	{$$ = X62_NUM;}
	| x63	{$$ = X63_NUM;}
	| x64	{$$ = X64_NUM;}
	| x65	{$$ = X65_NUM;}
	| x66	{$$ = X66_NUM;}
	| x67	{$$ = X67_NUM;}
	| x68	{$$ = X68_NUM;}
	| x69	{$$ = X69_NUM;}
	| x70	{$$ = X70_NUM;}
	| x71	{$$ = X71_NUM;}
	| x72	{$$ = X72_NUM;}
	| x73	{$$ = X73_NUM;}
	| x74	{$$ = X74_NUM;}
	| x75	{$$ = X75_NUM;}
	| x76	{$$ = X76_NUM;}
	| x77	{$$ = X77_NUM;}
	| x78	{$$ = X78_NUM;}
	| x79	{$$ = X79_NUM;}
	| x80	{$$ = X80_NUM;}

i
	: addi gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_ADDI, $4, $6);}

	| slti gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SLTI, $4, $6);}

	| sgei gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SGEI, $4, $6);}

	| seqi gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SEQI, $4, $6);}

	| snei gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SNEI, $4, $6);}

	| slli gpr "," gpr "," imm
	{check_shift($6); emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SLLI, $4, $6);}

	| srli gpr "," gpr "," imm
	{check_shift($6); emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_SRLI, $4, $6);}

	| add gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_ADD, $4, $6, 0);}

	| sub gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SUB, $4, $6, 0);}

	| slt gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SLT, $4, $6, 0);}

	| sge gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SGE, $4, $6, 0);}

	| seq gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SEQ, $4, $6, 0);}

	| sne gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SNE, $4, $6, 0);}

	| sll gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SLL, $4, $6, 0);}

	| srl gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_SRL, $4, $6, 0);}

	| lui gpr "," imm
	{emit_u(ctx, OPCODE_LUI, $2, $4);}

	| auipc gpr "," imm
	{emit_u(ctx, OPCODE_AUIPC, $2, $4);}

	| jal gpr "," addr
	{emit_reloc(ctx, RELOC_J, $4);
	 emit_u(ctx, OPCODE_JAL, $2, 0);}

	| jalr gpr "," gpr "," imm
	{emit_i(ctx, OPCODE_JALR, $2, 0, $4, $6);}

	| beq gpr "," gpr "," addr
	{emit_reloc(ctx, RELOC_B, $6);
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BEQ, $2, $4, 0);}

	| bne gpr "," gpr "," addr
	{emit_reloc(ctx, RELOC_B, $6);
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BNE, $2, $4, 0);}

	| blt gpr "," gpr "," addr
	{emit_reloc(ctx, RELOC_B, $6);
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BLT, $2, $4, 0);
	 }

	| bge gpr "," gpr "," addr
	{emit_reloc(ctx, RELOC_B, $6);
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BGE, $2, $4, 0);}

	| ld width "," gpr "," imm "(" gpr ")"
	{emit_i(ctx, OPCODE_LOAD, check_width($2), $4, $8, $6);}

	| st width "," gpr "," imm "(" gpr ")"
	{emit_s(ctx, OPCODE_STORE, check_width($2), $4, $8, $6);}

	| ecall
	{emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_ECALL, X0_NUM, 0);}

	| ebreak
	{emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_EBREAK, X0_NUM, 0);}

	| pcall
	{emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_PCALL, X0_NUM, 0);}

	| fence
	{emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_FENCE, X0_NUM, 0); /* still todo */}

	| unop gpr "," gpr "," str
	{emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_UNOP, $4, check_nop($6));}

	| diop gpr "," gpr "," gpr "," str
	{emit_d(ctx, OPCODE_DIOP, $2, $4, $6, check_nop3($8));}

	/* meta */
	| nop
	{emit_i(ctx, OPCODE_OP_IMM, X0_NUM, OP_IMM_ADDI, X0_NUM, 0);}

	| la gpr "," addr
	{emit_reloc(ctx, RELOC_LA, $4);
	 emit_u(ctx, OPCODE_LUI, $2, 0);
	 emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_ADDI, $2, 0);}

	| li gpr "," imm
	{emit_u(ctx, OPCODE_LUI, $2, tri_sr($4, 9));
	 emit_i(ctx, OPCODE_OP_IMM, $2, OP_IMM_ADDI, $2, tri_mask($4, 9));}
	/* stuff like call and ret TBD once I've come up with a proper register
	 * calling convention so we know which register to use as ra */

m
	: mul gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_MUL, $4, $6, 0);}

	| diV gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_DIV, $4, $6, 0);}

	| rem gpr "," gpr "," gpr
	{emit_r(ctx, OPCODE_OP, $2, OP_DIV, $4, $6, 0);}

a
	: stt
	{emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_STT, X0_NUM, 0);}

	| cst width "," gpr "," imm "(" gpr ")"
	{emit_s(ctx, OPCODE_STORE, STORE_CST | check_width($2), $4, $8, $6);}

	| ent gpr
	{emit_i(ctx, OPCODE_MEM, $2, MEM_ENT, X0_NUM, 0);}

	| cat
	{emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_CAT, X0_NUM, 0);}

Zcsr
	: csrrw csr "," gpr "," gpr
	{emit_i(ctx, OPCODE_SYSTEM, $4, SYSTEM_CSRRW, $6, check_csr($2));}

	| csrrs csr "," gpr "," gpr
	{emit_i(ctx, OPCODE_SYSTEM, $4, SYSTEM_CSRRS, $6, check_csr($2));}

	| csrrc csr "," gpr "," gpr
	{emit_i(ctx, OPCODE_SYSTEM, $4, SYSTEM_CSRRC, $6, check_csr($2));}

csr
	: id

statement
	: i
	| a
	| m
	| Zcsr

directive
	: set id imm
	| include str {process_file(ctx, $2);}

top
	: label {emit_label(ctx, $1);}
	| statement
	| directive

unit
	: top
	| top unit

input
	: unit
	| /* empty */

%%

static const char *find_lineno(const char *buf, size_t no)
{
	if (no == 0 || no == 1)
		return buf;

	char c;
	while ((c = *buf)) {
		buf++;

		if (c == '\n')
			no--;

		if (no == 1)
			break;
	}

	return buf;
}

static void _issue(struct src_issue issue, const char *fmt, va_list args)
{
	/* get start and end of current line in buffer */
	const char *line_start = find_lineno(issue.fctx.fbuf,
	                                     issue.loc.first_line);
	const char *line_end = strchr(line_start, '\n');
	if (!line_end)
		line_end = strchr(line_start, 0);

	const int line_len = line_end - line_start;

	fprintf(stderr, "%s:%i:%i: ",
		issue.fctx.fname,
	        issue.loc.first_line,
	        issue.loc.first_col);

	vfprintf(stderr, fmt, args);
	fputc('\n', stderr);

	int lineno_len = snprintf(NULL, 0, "%i", issue.loc.first_line);
	fputc(' ', stderr);
	fprintf(stderr, "%i | ", issue.loc.first_line);

	fprintf(stderr, "%.*s\n", line_len, line_start);

	for (int i = 0; i < lineno_len + 2; ++i)
		fputc(' ', stderr);

	fprintf(stderr, "| ");

	for (int i = 0; i < issue.loc.first_col - 1; ++i)
		fputc(line_start[i] == '\t' ? '\t' : ' ', stderr);

	for (int i = issue.loc.first_col; i < issue.loc.last_col; ++i) {
		if (i == issue.loc.first_col)
			fputc('^', stderr);
		else
			fputc('~', stderr);
	}

	fputc('\n', stderr);
}

void src_issue(struct src_issue issue, const char *err_msg, ...)
{
	va_list args;
	va_start(args, err_msg);
	_issue(issue, err_msg, args);
	va_end(args);
}
#include "gen_lexer.inc"

static struct src_loc to_src_loc(YYLTYPE *yylloc)
{
	struct src_loc loc;
	loc.first_line = yylloc->first_line;
	loc.last_line = yylloc->last_line;
	loc.first_col = yylloc->first_column;
	loc.last_col = yylloc->last_column;
	return loc;
}

static void yyerror(YYLTYPE *yylloc, void *lexer,
		struct parser *parser, struct asm_ctx *ctx, const char *msg)
{
	(void)lexer;
	(void)ctx;

	struct src_issue issue;
	issue.loc = to_src_loc(yylloc);
	issue.fctx.fbuf = parser->buf;
	issue.fctx.fname = parser->fname;
	src_issue(issue, msg);
}

struct parser *create_parser()
{
	return calloc(1, sizeof(struct parser));
}

void destroy_parser(struct parser *p)
{
	yylex_destroy(p->lexer);
	free(p);
}

void parse(struct parser *p, struct asm_ctx *ctx, const char *fname, const char *buf)
{
	p->fname = fname;
	p->buf = buf;

	p->comment_nesting = 0;

	p->failed = false;

	yylex_init(&p->lexer);
	yy_scan_string(buf, p->lexer);
	yyparse(p->lexer, p, ctx);
}
