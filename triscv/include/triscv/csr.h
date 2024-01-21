#ifndef TRISCV_CSR_H
#define TRISCV_CSR_H

/* first trit is sleep mode, R/W, second trit shutdown, R/W */
#define CSR_MPOWER -9841
#define RW_MPOWER  0b1111

#define CSR_SATPP -3280
#define CSR_SATPO -3279
#define CSR_SATPN -3278

#endif
