#ifndef TASM_ASSEMBLER_H
#define TASM_ASSEMBLER_H

#include <regs.h>
#include <tri.h>

struct asm_ctx;

enum asm_reloc_kind {
	/* absolute LUI + ADDI */
	RELOC_LA,
	/* relative AUIPC + ADDI (currently unimplemented) */
	RELOC_LR,
	RELOC_B,
	RELOC_J,
};

tri_t parse_imm(const char *imm);

void emit_r(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t fn0, enum gpr_num rs1,
		enum gpr_num rs2, tri_t fn5);

void emit_i(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t fn0, enum gpr_num rs1, tri_t imm9);

void emit_s(struct asm_ctx *ctx, tri_t opcode,
		tri_t fn0, enum gpr_num rs1, enum gpr_num rs2, tri_t imm9);

void emit_u(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, tri_t imm18);

void emit_d(struct asm_ctx *ctx, tri_t opcode,
		enum gpr_num rd, enum gpr_num rs1, enum gpr_num rs2, tri_t imm10);

/* emits a relocation for the previous instruction, very important to keep in
 * mind! */
void emit_reloc(struct asm_ctx *ctx, enum asm_reloc_kind reloc, const char *name);
void emit_label(struct asm_ctx *ctx, const char *name);

tri_t check_nop(const char *nop);
tri_t check_nop3(const char *nop3);
void check_shift(tri_t shmt);

tri_t check_csr(const char *csr);
tri_t check_width(const char *width);

int process_file(struct asm_ctx *ctx, const char *file);
int assemble(const char *outfile, const char *infile);

#endif
