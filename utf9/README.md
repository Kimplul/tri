# utf9, trinary utf8

utf9 can be seen as a thin wrapper around utf8, in that each tryte can be
expanded to either one or two utf8 bytes. Each tryte contains a header with
enough information to relatively easily perform the expansion. Current
four-level utf8 fits snugly into two trytes, with 2+2 bytes mapped. utf8 can
still be extended up to six bytes, as can utf9, though that is still reserved.

| Prefix | Condition | Bytes mapped | Info
|--------|-----------|--------------|
| 00     | Start/End | 1+0          |
| 01     | Start/End | 2+0          |
| 0i     | End       | 0+1          |
| 10     | Start     | 2+1          |
| 11     | Start     | 2+2          |
| 1i?    | Start     | ???          | Reserved for extensions
| i      | End       | 0+2          |

# design

The main design consideration is ease of translation to utf8. Given one tryte,
you can always repackage it as one or two valid utf8 bytes (valid in format,
missing start/end bytes may still show up).

There are some peculiarities, possibly most annoyingly that to fit trailing
utf8 bytes into this scheme, the two byte mapping end tryte can only have one
prefix trit.

All multitryte codepoints start with a one, which is nifty, but checking if a
codepoint is contained in a single tryte requires two checks, which is somewhat
slower than I would've liked. Still, to keep open the possibility of extending
the scheme, the single end tryte has to share the same leading zero as single
tryte sequences. In a trinary computer, the check can be a bit quicker,
construct a mask of 01 and filter with OPO OOO OOP (or something similar),
this should leave you with 11 only in the case of single tryte code points.

The extension reservation actually reserves the range [1ii, 1i1], probably with
each element referring to 5, 6 and 7 bytes respectively, covering the utf8
extension space. At these ranges, the first utf8 byte codes small enough values
that we can use a three trit flag without issues.

# symmetry

Currently there's a nice symmetry between start and stop conditions, in that one
start can be mapped to one end, and they always follow oneanother. With possible
extensions this might not be the case though, so to future-proof your code,
don't assume this.
