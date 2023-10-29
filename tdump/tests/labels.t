start:
	/* RELOC_LA */
	la x1, other_func
	/* RELOC_B */
	beq x0, x0, other_func

other_func:
	/* RELOC_J */
	jal x0, final_func
	jal x0, start

final_func:
	nop
