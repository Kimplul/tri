start:
	li x1, 48
	li x2, 19683
	st w, x1, 0(x2)
	li x1, 3
	csrrw mpower, x0, x1
