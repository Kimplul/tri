#ifndef TASM_BITS_H
#define TASM_BITS_H

#include <tasm/regs.h>
#include <tri.h>

#define OPCODE_OP_IMM 0b0000000000
#define OP_IMM_ADDI   0b0000000000
#define OP_IMM_SUBI   0b0000000001
#define OP_IMM_SLTI   0b0000000010
#define OP_IMM_SGEI   0b0000000100
#define OP_IMM_SEQI   0b0000000101
#define OP_IMM_SNEI   0b0000000110
#define OP_IMM_SLLI   0b0000001000
#define OP_IMM_SRLI   0b0000001001
#define OP_IMM_UNOP   0b0000001010

#define OPCODE_OP     0b0000000001
#define OP_ADD        0b0000000000
#define OP_SUB        0b0000000001
#define OP_SLT        0b0000000010
#define OP_SGE        0b0000000100
#define OP_SEQ        0b0000000101
#define OP_SNE        0b0000000110
#define OP_SLL        0b0000001000
#define OP_SRL        0b0000001001
#define OP_MUL        0b0000001010
#define OP_DIV        0b0000010000
#define OP_REM        0b0000010001

#define OPCODE_LUI    0b0000000010
#define OPCODE_AUIPC  0b0000000100
#define OPCODE_JAL    0b0000000101
#define OPCODE_JALR   0b0000000110

#define OPCODE_BRANCH 0b0000001000
#define BRANCH_BEQ    0b0000000000
#define BRANCH_BNE    0b0000000001
#define BRANCH_BLT    0b0000000010
#define BRANCH_BGE    0b0000000100

#define OPCODE_LOAD   0b0000001001
#define OPCODE_STORE  0b0000001010
#define STORE_CST     0b0000000001

#define OPCODE_SYSTEM 0b0000010000
#define SYSTEM_ECALL  0b0000000000
#define SYSTEM_EBREAK 0b0000000001
#define SYSTEM_PCALL  0b0000000010
#define SYSTEM_CSRRW  0b0000000100
#define SYSTEM_CSRRS  0b0000000101
#define SYSTEM_CSRRC  0b0000000110

#define OPCODE_MEM    0b0000010001
#define MEM_FENCE     0b0000000000
#define MEM_STT       0b0000000001
#define MEM_ENT       0b0000000010
#define MEM_CAT       0b0000000100

#define OPCODE_DIOP   0b0000010010

#define WIDTH_W       0b0100000000
#define WIDTH_T       0b0000000000

#define nonnull __attribute__((nonnull))

tri_t parse_opcode(tri_t i);

tri_t build_r(tri_t opcode, tri_t rd, tri_t fn0, tri_t rs1, tri_t rs2, tri_t fn5);
void nonnull parse_r(tri_t i, tri_t *rd, tri_t *rs1, tri_t *rs2, tri_t *fn0, tri_t *fn5);

tri_t build_i(tri_t opcode, tri_t rd, tri_t fn0, tri_t rs1, tri_t imm9);
void nonnull parse_i(tri_t i, tri_t *rd, tri_t *fn0, tri_t *rs1, tri_t *imm9);

tri_t build_s(tri_t opcode, tri_t imm4, tri_t fn0, tri_t rs1, tri_t rs2, tri_t imm5);
void nonnull parse_s(tri_t i, tri_t *imm4, tri_t *fn0, tri_t *rs1, tri_t *rs2, tri_t *imm5);

tri_t build_u(tri_t opcode, tri_t rd, tri_t imm18);
void nonnull parse_u(tri_t i, tri_t *rd, tri_t *imm18);

#endif
