#include <tasm/bits.h>

tri_t parse_opcode(tri_t i)
{
	/* opcode is lowest five trits */
	return tri_mask(i, 5);
}

tri_t build_r(tri_t opcode, tri_t rd, tri_t fn0, tri_t rs1, tri_t rs2, tri_t fn5)
{
	return opcode
		| tri_sl(rd ,  5)
		| tri_sl(fn0,  9)
		| tri_sl(rs1, 14)
		| tri_sl(rs2, 18)
		| tri_sl(fn5, 22);
}

void parse_r(tri_t i, tri_t *rd, tri_t *fn0, tri_t *rs1, tri_t *rs2, tri_t *fn5)
{
	*rd  = tri_mask(tri_sr(i,  5), 4);
	*fn0 = tri_mask(tri_sr(i,  9), 5);
	*rs1 = tri_mask(tri_sr(i, 14), 4);
	*rs2 = tri_mask(tri_sr(i, 18), 4);
	*fn5 = tri_mask(tri_sr(i, 22), 5);
}

tri_t build_i(tri_t opcode, tri_t rd, tri_t fn0, tri_t rs1, tri_t imm9)
{
	return opcode
		| tri_sl(rd  ,  5)
		| tri_sl(fn0 ,  9)
		| tri_sl(rs1 , 14)
		| tri_sl(imm9, 18);
}

void parse_i(tri_t i, tri_t *rd, tri_t *fn0, tri_t *rs1, tri_t *imm9)
{
	*rd   = tri_mask(tri_sr(i,  5), 4);
	*fn0  = tri_mask(tri_sr(i,  9), 5);
	*rs1  = tri_mask(tri_sr(i, 14), 4);
	*imm9 = tri_mask(tri_sr(i, 18), 9);
}

tri_t build_s(tri_t opcode, tri_t imm4, tri_t fn0, tri_t rs1, tri_t rs2, tri_t imm5)
{
	return opcode
		| tri_sl(imm4,  5)
		| tri_sl(fn0 ,  9)
		| tri_sl(rs1 , 14)
		| tri_sl(rs2 , 18)
		| tri_sl(imm5, 22);
}

void parse_s(tri_t i, tri_t *imm4, tri_t *fn0, tri_t *rs1, tri_t *rs2, tri_t *imm5)
{
	*imm4 = tri_mask(tri_sr(i,  5), 4);
	*fn0  = tri_mask(tri_sr(i,  9), 5);
	*rs1  = tri_mask(tri_sr(i, 14), 4);
	*rs2  = tri_mask(tri_sr(i, 18), 4);
	*imm5 = tri_mask(tri_sr(i, 22), 5);
}

tri_t build_u(tri_t opcode, tri_t rd, tri_t imm18)
{
	return opcode
		| tri_sl(rd   , 5)
		| tri_sl(imm18, 9);
}

void parse_u(tri_t i, tri_t *rd, tri_t *imm18)
{
	*rd    = tri_mask(tri_sr(i, 5),  4);
	*imm18 = tri_mask(tri_sr(i, 9), 18);
}
