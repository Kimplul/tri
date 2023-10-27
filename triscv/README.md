# `triscv`, a trinary riscv-like ISA simulator

An attempt at creating a trinary computer simulator capable of running simple
operating systems, with virtual memory and user/system separation.

Natural bases of three used as trit groupings, i.e.
3^0 = trit
3^1 = nit (likely not actually used?)
3^2 = tryte (base size of characters etc, similar to byte)
3^3 = tri (base word size)

Ideally I would like to extend support up to 3^4 (tril?) that would be
equivalent to 64 bit groupings on conventional hardware, but the my trinary
arithmetic library underlying the simulator doesn't support 81 trits due to
efficiency/portability concerns. 128 bit integers could be usable on at least
x86, but not really portable. Something like `gmp` could also be used, but would
be very slow. Alternatively, consider 45 trit as an equivalence to 64 bit
computers, as they are approximately the same in value and divisible by three.

Heavy inspiration taken from riscv.

M-mode/S-mode/U-mode fits pretty nicely into trinary, heh.

# Operation set

27 trit ops, registers 3^4?

 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
|-----------------------------------------------------|
| fn5     | rs2   | rs1   | fn0     | rd    | opcode  | R-type
|-----------------------------------------------------|
| imm9            | rs1   | fn0     | rd    | opcode  | I-type
|-----------------------------------------------------|
| imm5    | rs2   | rs1   | fn0     | imm4  | opcode  | S-type
|-----------------------------------------------------|
| imm18                             | rd    | opcode  | U-type
|-----------------------------------------------------|
| imm5    | rs2   | rs1   | immd    | rd    | opcode  | D-type
|-----------------------------------------------------|
(D is a variant of R, where immd is actually fn0, but used as an immediate)

Compressed instructions probably possible to implement in future but left alone
for now.

Exact instructions still TBD, but R type probably reserves one fn trit value for
diops. It's unclear to me how readily diops can be implemented in hardware, so
consider this more exploratory than anythin else.

Similarly, I-type reserved on fn trit value to unops.

Turns out it's literally just a mapping, i.e. unops use a three-way mux with
the input value as the selection trit and the three control bits inputs to the
mux. Similarly, diops are just a nine-way mux.

# Registers

81, of which x0 is constant 0. ABI TBD but probably similar to riscv.

# Virtual memory

Physical memory consists of PPN[2], PPN[1], PPN[0] and page offset. 27 trits is enough
for about 7 teratrytes of memory, which probably doesn't need range extensions
like 32bit computers tend to use.

Page table entries:

 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0
 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
|-----------------------------------------------------|
| PPN[2]     | PPN[1]    | PPN[0]     |RSW|G|U|X|A|R|V|
|------------------------------------------------D-W--|
| TAG                                                 |
|-----------------------------------------------------|
| Reserved                                            |
|-----------------------------------------------------|

TAG is a tag that allows us to separate one address space into multiple regions,
similar to CODOMS system but scaled down a lot. If left 0, code executing in the
region is allowed to access other regions but outside regions are not allowed to
access the zero region, except executing a migration jump.

The reserved region might come
in handy for 'extensions' in the future, but can probably be set to zero for
now.

R/W and A/D work by the following table:

N => both (R and W, A and D)
O => none
P => top (R, A)

RSW is reserved for S-mode usage.

The idea here is a page marked write must also be marked read, and a dirty page
must also have been accessed. Whether an interrupt is raised when A/D is updated
is set by a status CSR, to be determined later. Three-level page tables.

Each base page is 3^8 = 6561, and since each PTE
takes up 9 trytes, each base page can fit 3^6 PTEs. Therefore, to cover the full
27 bit address space, we need three `satp` CSRs, `satpn`, `satpo`, `satpp`,
corresponding to the first trit in the address. This can give reasonably
efficient separation of user/kernelspace, for example -1 for kernel and 1 for
user. Still about 2.5 tera per space.

This can be extended to 81 bits, although with no nice whole number that maps to
81. Not a huge deal, by any means, although kind of annoying that the number of
elements per PTE shrinks to 243. Maybe not a huge issue, but might limit
useability somewhat as the number of page levels has to be increased much more
rapidly to get larger virtual address spaces.

Requiring physical addresses to be the same width as virtual addresses
simplifies hypervisor stuff somewhat, could be useful? Not that allocating some
pages in series is too big of an issue, but still feels like an unnecessary
complication in the RISC-V specs. Apparently the explanation given is that is
can be useful to emulate larger physical address spaces than virtual spaces,
though I'd like to see some examples. I guess easier masking of some addresses?
Dunno.

I might want to add in a bus error to separate it from pmp errors, there's been
some discussion about it in riscv mailing lists.

# CSRs

TDB

# Extensions

## I

addi, slti
|-----------------------------------------------------|
| imm0            | rs1   | fn0     | rd    | OP-IMM  | I-type
|-----------------------------------------------------|

unop (some macro instructions might be available in assembler)
|-----------------------------------------------------|
| 0         |N|O|P| rs1   | fn0     | rd    | OP-IMM  | I-type
|-----------------------------------------------------|

slli, srli (shifts work differently in balanced forms, have to be careful)
	(shmt is 'unsigned', i.e. the actual shift amount is shmt + 13)
|-----------------------------------------------------|
| imm0      |shmt | rs1   | fn0     | rd    | OP-IMM  | I-type
|-----------------------------------------------------|

lui
|-----------------------------------------------------|
| imm9                              | rd    | LUI     | U-type
|-----------------------------------------------------|

auipc
|-----------------------------------------------------|
| imm9                              | rd    | AUIPC   | U-type
|-----------------------------------------------------|

add, slt, sge, seq, sne, sll, srl, sub
|-----------------------------------------------------|
| 0       | rs2   | rs1   | fn0     | rd    | OP      | R-type
|-----------------------------------------------------|

diop
|-----------------------------------------------------|
|N|O|P|N|O| rs2   | rs1   |P|N|O|P|0| rd    | DIOP    | D-type
|-----------------------------------------------------|

nop
|-----------------------------------------------------|
| 0               | x0    | 0       | x0    | OP-IMM  | I-type
|-----------------------------------------------------|

jal
|-----------------------------------------------------|
| imm9                              | rd    | JAL     | U-type
|-----------------------------------------------------|

jalr
|-----------------------------------------------------|
| imm0            | rs1   | 0       | rd    | JALR    | I-type
|-----------------------------------------------------|

beq, bne, blt, bge
|-----------------------------------------------------|
| imm0    | rs2   | rs1   | fn0     | imm4  | BRANCH  | S-type
|-----------------------------------------------------|

load (w = width, i = 1 tryte, 0 = 3 trytes, 1 = 9 trytes)
|-----------------------------------------------------|
| imm0            | rs1   |w| 0     | rd    | LOAD    | I-type
|-----------------------------------------------------|

store
|-----------------------------------------------------|
| imm5    | rs2   | rs1   |w| 0     | imm4  | STORE   | S-type
|-----------------------------------------------------|

fence (todo)
|-----------------------------------------------------|
| imm0            | rs1   | fn0     | rd    | MEM     | I-type
|-----------------------------------------------------|

ecall, ebreak, pcall
|-----------------------------------------------------|
| imm0            | x0    | fn0     | x0    | SYSTEM  | I-type
|-----------------------------------------------------|

hints, any OP-IMM or OP with rd = x0. Additionally,
a number of maybe-instructions in SYSTEM for future use, if unimplemented
just write 0 to rd.

## M

mul
|-----------------------------------------------------|
| fn5     | rs2   | rs1   | fn0     | rd    | OP      | R-type
|-----------------------------------------------------|

div
|-----------------------------------------------------|
| fn5     | rs2   | rs1   | fn0     | rd    | OP      | R-type
|-----------------------------------------------------|

rem
|-----------------------------------------------------|
| fn5     | rs2   | rs1   | fn0     | rd    | OP      | R-type
|-----------------------------------------------------|

## A

stt (start transaction)
cst (checked store)
ent (end transaction)
cat (cancel transaction)

Each system has a buffer with at least three slots for checked transactions.
Each checked transaction is written to the buffer when an stc is encountered.
stc clears out this buffer and ent checks if all stores are valid and flushes
the buffer to real memory, or cache or wherever. A system is allowed to give
each core a buffer or use a global buffer, but the size should be given in a CSR
somewhere. Platforms may require at least n slots. Maybe? Reads inside
transaction read from memory. Slow commits, at least somewhat, but probably
somewhat simpler. Spinlock (and by extension, mutex) would then be

spinlock:
	// spin until a zero appears
	lw x1, (x2)
	bnez x1, spinlock

	// start transaction, try to write 1
	stt
	li x1, 1
	stc x1, (x2)
	ent x1
	// someone else tried at the same time, wait for next zero
	// preferably also do a spin for a random but increasing time to try to
	// avoid livelock, or rely on whatever system we're dealing with to
	// provide it for us
	beqz x1, spinlock

could probably also provide simple atomics, like add or something, but eh

## Zicsr

csrrw, csrrs, csrrc
|-----------------------------------------------------|
| imm0            | rs    | fn0     | rd    | SYSTEM  | I-type
|-----------------------------------------------------|

The CSR numbers are specified in the future.

Also, possibly floating point stuff in the future, though I haven't chosen a
floating point format yet.
