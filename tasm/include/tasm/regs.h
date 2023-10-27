#ifndef TASM_REGS_H
#define TASM_REGS_H

#include <stdlib.h>
#include <stdio.h>

enum gpr_num {
	X0_NUM,
	X1_NUM,
	X2_NUM,
	X3_NUM,
	X4_NUM,
	X5_NUM,
	X6_NUM,
	X7_NUM,
	X8_NUM,
	X9_NUM,
	X10_NUM,
	X11_NUM,
	X12_NUM,
	X13_NUM,
	X14_NUM,
	X15_NUM,
	X16_NUM,
	X17_NUM,
	X18_NUM,
	X19_NUM,
	X20_NUM,
	X21_NUM,
	X22_NUM,
	X23_NUM,
	X24_NUM,
	X25_NUM,
	X26_NUM,
	X27_NUM,
	X28_NUM,
	X29_NUM,
	X30_NUM,
	X31_NUM,
	X32_NUM,
	X33_NUM,
	X34_NUM,
	X35_NUM,
	X36_NUM,
	X37_NUM,
	X38_NUM,
	X39_NUM,
	X40_NUM,
	X41_NUM,
	X42_NUM,
	X43_NUM,
	X44_NUM,
	X45_NUM,
	X46_NUM,
	X47_NUM,
	X48_NUM,
	X49_NUM,
	X50_NUM,
	X51_NUM,
	X52_NUM,
	X53_NUM,
	X54_NUM,
	X55_NUM,
	X56_NUM,
	X57_NUM,
	X58_NUM,
	X59_NUM,
	X60_NUM,
	X61_NUM,
	X62_NUM,
	X63_NUM,
	X64_NUM,
	X65_NUM,
	X66_NUM,
	X67_NUM,
	X68_NUM,
	X69_NUM,
	X70_NUM,
	X71_NUM,
	X72_NUM,
	X73_NUM,
	X74_NUM,
	X75_NUM,
	X76_NUM,
	X77_NUM,
	X78_NUM,
	X79_NUM,
	X80_NUM,
};

/* generated with a script */
enum gpr_tri {
	X41 = 170,
	X42 = 168,
	X43 = 169,
	X44 = 162,
	X45 = 160,
	X46 = 161,
	X47 = 166,
	X48 = 164,
	X49 = 165,
	X50 = 138,
	X51 = 136,
	X52 = 137,
	X53 = 130,
	X54 = 128,
	X55 = 129,
	X56 = 134,
	X57 = 132,
	X58 = 133,
	X59 = 154,
	X60 = 152,
	X61 = 153,
	X62 = 146,
	X63 = 144,
	X64 = 145,
	X65 = 150,
	X66 = 148,
	X67 = 149,
	X68 = 42,
	X69 = 40,
	X70 = 41,
	X71 = 34,
	X72 = 32,
	X73 = 33,
	X74 = 38,
	X75 = 36,
	X76 = 37,
	X77 = 10,
	X78 = 8,
	X79 = 9,
	X80 = 2,
	X0 = 0,
	X1 = 1,
	X2 = 6,
	X3 = 4,
	X4 = 5,
	X5 = 26,
	X6 = 24,
	X7 = 25,
	X8 = 18,
	X9 = 16,
	X10 = 17,
	X11 = 22,
	X12 = 20,
	X13 = 21,
	X14 = 106,
	X15 = 104,
	X16 = 105,
	X17 = 98,
	X18 = 96,
	X19 = 97,
	X20 = 102,
	X21 = 100,
	X22 = 101,
	X23 = 74,
	X24 = 72,
	X25 = 73,
	X26 = 66,
	X27 = 64,
	X28 = 65,
	X29 = 70,
	X30 = 68,
	X31 = 69,
	X32 = 90,
	X33 = 88,
	X34 = 89,
	X35 = 82,
	X36 = 80,
	X37 = 81,
	X38 = 86,
	X39 = 84,
	X40 = 85,
};

static inline enum gpr_tri gpr_tri(enum gpr_num g)
{
	switch (g) {
	case  X0_NUM: return X0;
	case  X1_NUM: return X1;
	case  X2_NUM: return X2;
	case  X3_NUM: return X3;
	case  X4_NUM: return X4;
	case  X5_NUM: return X5;
	case  X6_NUM: return X6;
	case  X7_NUM: return X7;
	case  X8_NUM: return X8;
	case  X9_NUM: return X9;
	case X10_NUM: return X10;
	case X11_NUM: return X11;
	case X12_NUM: return X12;
	case X13_NUM: return X13;
	case X14_NUM: return X14;
	case X15_NUM: return X15;
	case X16_NUM: return X16;
	case X17_NUM: return X17;
	case X18_NUM: return X18;
	case X19_NUM: return X19;
	case X20_NUM: return X20;
	case X21_NUM: return X21;
	case X22_NUM: return X22;
	case X23_NUM: return X23;
	case X24_NUM: return X24;
	case X25_NUM: return X25;
	case X26_NUM: return X26;
	case X27_NUM: return X27;
	case X28_NUM: return X28;
	case X29_NUM: return X29;
	case X30_NUM: return X30;
	case X31_NUM: return X31;
	case X32_NUM: return X32;
	case X33_NUM: return X33;
	case X34_NUM: return X34;
	case X35_NUM: return X35;
	case X36_NUM: return X36;
	case X37_NUM: return X37;
	case X38_NUM: return X38;
	case X39_NUM: return X39;
	case X40_NUM: return X40;
	case X41_NUM: return X41;
	case X42_NUM: return X42;
	case X43_NUM: return X43;
	case X44_NUM: return X44;
	case X45_NUM: return X45;
	case X46_NUM: return X46;
	case X47_NUM: return X47;
	case X48_NUM: return X48;
	case X49_NUM: return X49;
	case X50_NUM: return X50;
	case X51_NUM: return X51;
	case X52_NUM: return X52;
	case X53_NUM: return X53;
	case X54_NUM: return X54;
	case X55_NUM: return X55;
	case X56_NUM: return X56;
	case X57_NUM: return X57;
	case X58_NUM: return X58;
	case X59_NUM: return X59;
	case X60_NUM: return X60;
	case X61_NUM: return X61;
	case X62_NUM: return X62;
	case X63_NUM: return X63;
	case X64_NUM: return X64;
	case X65_NUM: return X65;
	case X66_NUM: return X66;
	case X67_NUM: return X67;
	case X68_NUM: return X68;
	case X69_NUM: return X69;
	case X70_NUM: return X70;
	case X71_NUM: return X71;
	case X72_NUM: return X72;
	case X73_NUM: return X73;
	case X74_NUM: return X74;
	case X75_NUM: return X75;
	case X76_NUM: return X76;
	case X77_NUM: return X77;
	case X78_NUM: return X78;
	case X79_NUM: return X79;
	case X80_NUM: return X80;
	}

	fprintf(stderr, "illegal gpr num: %d\n", g);
	abort();
	return -1;
}

static inline enum gpr_num gpr_num(enum gpr_tri t)
{
	switch (t) {
	case  X0: return  X0_NUM;
	case  X1: return  X1_NUM;
	case  X2: return  X2_NUM;
	case  X3: return  X3_NUM;
	case  X4: return  X4_NUM;
	case  X5: return  X5_NUM;
	case  X6: return  X6_NUM;
	case  X7: return  X7_NUM;
	case  X8: return  X8_NUM;
	case  X9: return  X9_NUM;
	case X10: return X10_NUM;
	case X11: return X11_NUM;
	case X12: return X12_NUM;
	case X13: return X13_NUM;
	case X14: return X14_NUM;
	case X15: return X15_NUM;
	case X16: return X16_NUM;
	case X17: return X17_NUM;
	case X18: return X18_NUM;
	case X19: return X19_NUM;
	case X20: return X20_NUM;
	case X21: return X21_NUM;
	case X22: return X22_NUM;
	case X23: return X23_NUM;
	case X24: return X24_NUM;
	case X25: return X25_NUM;
	case X26: return X26_NUM;
	case X27: return X27_NUM;
	case X28: return X28_NUM;
	case X29: return X29_NUM;
	case X30: return X30_NUM;
	case X31: return X31_NUM;
	case X32: return X32_NUM;
	case X33: return X33_NUM;
	case X34: return X34_NUM;
	case X35: return X35_NUM;
	case X36: return X36_NUM;
	case X37: return X37_NUM;
	case X38: return X38_NUM;
	case X39: return X39_NUM;
	case X40: return X40_NUM;
	case X41: return X41_NUM;
	case X42: return X42_NUM;
	case X43: return X43_NUM;
	case X44: return X44_NUM;
	case X45: return X45_NUM;
	case X46: return X46_NUM;
	case X47: return X47_NUM;
	case X48: return X48_NUM;
	case X49: return X49_NUM;
	case X50: return X50_NUM;
	case X51: return X51_NUM;
	case X52: return X52_NUM;
	case X53: return X53_NUM;
	case X54: return X54_NUM;
	case X55: return X55_NUM;
	case X56: return X56_NUM;
	case X57: return X57_NUM;
	case X58: return X58_NUM;
	case X59: return X59_NUM;
	case X60: return X60_NUM;
	case X61: return X61_NUM;
	case X62: return X62_NUM;
	case X63: return X63_NUM;
	case X64: return X64_NUM;
	case X65: return X65_NUM;
	case X66: return X66_NUM;
	case X67: return X67_NUM;
	case X68: return X68_NUM;
	case X69: return X69_NUM;
	case X70: return X70_NUM;
	case X71: return X71_NUM;
	case X72: return X72_NUM;
	case X73: return X73_NUM;
	case X74: return X74_NUM;
	case X75: return X75_NUM;
	case X76: return X76_NUM;
	case X77: return X77_NUM;
	case X78: return X78_NUM;
	case X79: return X79_NUM;
	case X80: return X80_NUM;
	}

	fprintf(stderr, "illegal gpr: %d\n", t);
	abort();
	return -1;
}
#endif
