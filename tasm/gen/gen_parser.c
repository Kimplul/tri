/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "src/parser.y"


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


#line 89 "gen/gen_parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    imm = 258,                     /* imm  */
    label = 259,                   /* label  */
    str = 260,                     /* str  */
    id = 261,                      /* id  */
    COMMA = 262,                   /* ","  */
    LPAREN = 263,                  /* "("  */
    RPAREN = 264,                  /* ")"  */
    set = 265,                     /* set  */
    include = 266,                 /* include  */
    x0 = 267,                      /* x0  */
    x1 = 268,                      /* x1  */
    x2 = 269,                      /* x2  */
    x3 = 270,                      /* x3  */
    x4 = 271,                      /* x4  */
    x5 = 272,                      /* x5  */
    x6 = 273,                      /* x6  */
    x7 = 274,                      /* x7  */
    x8 = 275,                      /* x8  */
    x9 = 276,                      /* x9  */
    x10 = 277,                     /* x10  */
    x11 = 278,                     /* x11  */
    x12 = 279,                     /* x12  */
    x13 = 280,                     /* x13  */
    x14 = 281,                     /* x14  */
    x15 = 282,                     /* x15  */
    x16 = 283,                     /* x16  */
    x17 = 284,                     /* x17  */
    x18 = 285,                     /* x18  */
    x19 = 286,                     /* x19  */
    x20 = 287,                     /* x20  */
    x21 = 288,                     /* x21  */
    x22 = 289,                     /* x22  */
    x23 = 290,                     /* x23  */
    x24 = 291,                     /* x24  */
    x25 = 292,                     /* x25  */
    x26 = 293,                     /* x26  */
    x27 = 294,                     /* x27  */
    x28 = 295,                     /* x28  */
    x29 = 296,                     /* x29  */
    x30 = 297,                     /* x30  */
    x31 = 298,                     /* x31  */
    x32 = 299,                     /* x32  */
    x33 = 300,                     /* x33  */
    x34 = 301,                     /* x34  */
    x35 = 302,                     /* x35  */
    x36 = 303,                     /* x36  */
    x37 = 304,                     /* x37  */
    x38 = 305,                     /* x38  */
    x39 = 306,                     /* x39  */
    x40 = 307,                     /* x40  */
    x41 = 308,                     /* x41  */
    x42 = 309,                     /* x42  */
    x43 = 310,                     /* x43  */
    x44 = 311,                     /* x44  */
    x45 = 312,                     /* x45  */
    x46 = 313,                     /* x46  */
    x47 = 314,                     /* x47  */
    x48 = 315,                     /* x48  */
    x49 = 316,                     /* x49  */
    x50 = 317,                     /* x50  */
    x51 = 318,                     /* x51  */
    x52 = 319,                     /* x52  */
    x53 = 320,                     /* x53  */
    x54 = 321,                     /* x54  */
    x55 = 322,                     /* x55  */
    x56 = 323,                     /* x56  */
    x57 = 324,                     /* x57  */
    x58 = 325,                     /* x58  */
    x59 = 326,                     /* x59  */
    x60 = 327,                     /* x60  */
    x61 = 328,                     /* x61  */
    x62 = 329,                     /* x62  */
    x63 = 330,                     /* x63  */
    x64 = 331,                     /* x64  */
    x65 = 332,                     /* x65  */
    x66 = 333,                     /* x66  */
    x67 = 334,                     /* x67  */
    x68 = 335,                     /* x68  */
    x69 = 336,                     /* x69  */
    x70 = 337,                     /* x70  */
    x71 = 338,                     /* x71  */
    x72 = 339,                     /* x72  */
    x73 = 340,                     /* x73  */
    x74 = 341,                     /* x74  */
    x75 = 342,                     /* x75  */
    x76 = 343,                     /* x76  */
    x77 = 344,                     /* x77  */
    x78 = 345,                     /* x78  */
    x79 = 346,                     /* x79  */
    x80 = 347,                     /* x80  */
    addi = 348,                    /* addi  */
    slti = 349,                    /* slti  */
    sgei = 350,                    /* sgei  */
    seqi = 351,                    /* seqi  */
    snei = 352,                    /* snei  */
    unop = 353,                    /* unop  */
    diop = 354,                    /* diop  */
    slli = 355,                    /* slli  */
    srli = 356,                    /* srli  */
    sll = 357,                     /* sll  */
    srl = 358,                     /* srl  */
    add = 359,                     /* add  */
    sub = 360,                     /* sub  */
    slt = 361,                     /* slt  */
    sge = 362,                     /* sge  */
    seq = 363,                     /* seq  */
    sne = 364,                     /* sne  */
    lui = 365,                     /* lui  */
    auipc = 366,                   /* auipc  */
    jal = 367,                     /* jal  */
    jalr = 368,                    /* jalr  */
    beq = 369,                     /* beq  */
    bne = 370,                     /* bne  */
    blt = 371,                     /* blt  */
    bge = 372,                     /* bge  */
    ld = 373,                      /* ld  */
    st = 374,                      /* st  */
    ecall = 375,                   /* ecall  */
    ebreak = 376,                  /* ebreak  */
    pcall = 377,                   /* pcall  */
    fence = 378,                   /* fence  */
    mv = 379,                      /* mv  */
    li = 380,                      /* li  */
    la = 381,                      /* la  */
    nop = 382,                     /* nop  */
    call = 383,                    /* call  */
    ret = 384,                     /* ret  */
    ble = 385,                     /* ble  */
    bgt = 386,                     /* bgt  */
    mul = 387,                     /* mul  */
    diV = 388,                     /* diV  */
    rem = 389,                     /* rem  */
    stt = 390,                     /* stt  */
    cst = 391,                     /* cst  */
    ent = 392,                     /* ent  */
    cat = 393,                     /* cat  */
    csrrw = 394,                   /* csrrw  */
    csrrs = 395,                   /* csrrs  */
    csrrc = 396                    /* csrrc  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "src/parser.y"

	const char *str;
	enum gpr_num gpr;
	tri_t tri;

#line 283 "gen/gen_parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (void *scanner, struct parser *parser, struct asm_ctx *ctx);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_imm = 3,                        /* imm  */
  YYSYMBOL_label = 4,                      /* label  */
  YYSYMBOL_str = 5,                        /* str  */
  YYSYMBOL_id = 6,                         /* id  */
  YYSYMBOL_COMMA = 7,                      /* ","  */
  YYSYMBOL_LPAREN = 8,                     /* "("  */
  YYSYMBOL_RPAREN = 9,                     /* ")"  */
  YYSYMBOL_set = 10,                       /* set  */
  YYSYMBOL_include = 11,                   /* include  */
  YYSYMBOL_x0 = 12,                        /* x0  */
  YYSYMBOL_x1 = 13,                        /* x1  */
  YYSYMBOL_x2 = 14,                        /* x2  */
  YYSYMBOL_x3 = 15,                        /* x3  */
  YYSYMBOL_x4 = 16,                        /* x4  */
  YYSYMBOL_x5 = 17,                        /* x5  */
  YYSYMBOL_x6 = 18,                        /* x6  */
  YYSYMBOL_x7 = 19,                        /* x7  */
  YYSYMBOL_x8 = 20,                        /* x8  */
  YYSYMBOL_x9 = 21,                        /* x9  */
  YYSYMBOL_x10 = 22,                       /* x10  */
  YYSYMBOL_x11 = 23,                       /* x11  */
  YYSYMBOL_x12 = 24,                       /* x12  */
  YYSYMBOL_x13 = 25,                       /* x13  */
  YYSYMBOL_x14 = 26,                       /* x14  */
  YYSYMBOL_x15 = 27,                       /* x15  */
  YYSYMBOL_x16 = 28,                       /* x16  */
  YYSYMBOL_x17 = 29,                       /* x17  */
  YYSYMBOL_x18 = 30,                       /* x18  */
  YYSYMBOL_x19 = 31,                       /* x19  */
  YYSYMBOL_x20 = 32,                       /* x20  */
  YYSYMBOL_x21 = 33,                       /* x21  */
  YYSYMBOL_x22 = 34,                       /* x22  */
  YYSYMBOL_x23 = 35,                       /* x23  */
  YYSYMBOL_x24 = 36,                       /* x24  */
  YYSYMBOL_x25 = 37,                       /* x25  */
  YYSYMBOL_x26 = 38,                       /* x26  */
  YYSYMBOL_x27 = 39,                       /* x27  */
  YYSYMBOL_x28 = 40,                       /* x28  */
  YYSYMBOL_x29 = 41,                       /* x29  */
  YYSYMBOL_x30 = 42,                       /* x30  */
  YYSYMBOL_x31 = 43,                       /* x31  */
  YYSYMBOL_x32 = 44,                       /* x32  */
  YYSYMBOL_x33 = 45,                       /* x33  */
  YYSYMBOL_x34 = 46,                       /* x34  */
  YYSYMBOL_x35 = 47,                       /* x35  */
  YYSYMBOL_x36 = 48,                       /* x36  */
  YYSYMBOL_x37 = 49,                       /* x37  */
  YYSYMBOL_x38 = 50,                       /* x38  */
  YYSYMBOL_x39 = 51,                       /* x39  */
  YYSYMBOL_x40 = 52,                       /* x40  */
  YYSYMBOL_x41 = 53,                       /* x41  */
  YYSYMBOL_x42 = 54,                       /* x42  */
  YYSYMBOL_x43 = 55,                       /* x43  */
  YYSYMBOL_x44 = 56,                       /* x44  */
  YYSYMBOL_x45 = 57,                       /* x45  */
  YYSYMBOL_x46 = 58,                       /* x46  */
  YYSYMBOL_x47 = 59,                       /* x47  */
  YYSYMBOL_x48 = 60,                       /* x48  */
  YYSYMBOL_x49 = 61,                       /* x49  */
  YYSYMBOL_x50 = 62,                       /* x50  */
  YYSYMBOL_x51 = 63,                       /* x51  */
  YYSYMBOL_x52 = 64,                       /* x52  */
  YYSYMBOL_x53 = 65,                       /* x53  */
  YYSYMBOL_x54 = 66,                       /* x54  */
  YYSYMBOL_x55 = 67,                       /* x55  */
  YYSYMBOL_x56 = 68,                       /* x56  */
  YYSYMBOL_x57 = 69,                       /* x57  */
  YYSYMBOL_x58 = 70,                       /* x58  */
  YYSYMBOL_x59 = 71,                       /* x59  */
  YYSYMBOL_x60 = 72,                       /* x60  */
  YYSYMBOL_x61 = 73,                       /* x61  */
  YYSYMBOL_x62 = 74,                       /* x62  */
  YYSYMBOL_x63 = 75,                       /* x63  */
  YYSYMBOL_x64 = 76,                       /* x64  */
  YYSYMBOL_x65 = 77,                       /* x65  */
  YYSYMBOL_x66 = 78,                       /* x66  */
  YYSYMBOL_x67 = 79,                       /* x67  */
  YYSYMBOL_x68 = 80,                       /* x68  */
  YYSYMBOL_x69 = 81,                       /* x69  */
  YYSYMBOL_x70 = 82,                       /* x70  */
  YYSYMBOL_x71 = 83,                       /* x71  */
  YYSYMBOL_x72 = 84,                       /* x72  */
  YYSYMBOL_x73 = 85,                       /* x73  */
  YYSYMBOL_x74 = 86,                       /* x74  */
  YYSYMBOL_x75 = 87,                       /* x75  */
  YYSYMBOL_x76 = 88,                       /* x76  */
  YYSYMBOL_x77 = 89,                       /* x77  */
  YYSYMBOL_x78 = 90,                       /* x78  */
  YYSYMBOL_x79 = 91,                       /* x79  */
  YYSYMBOL_x80 = 92,                       /* x80  */
  YYSYMBOL_addi = 93,                      /* addi  */
  YYSYMBOL_slti = 94,                      /* slti  */
  YYSYMBOL_sgei = 95,                      /* sgei  */
  YYSYMBOL_seqi = 96,                      /* seqi  */
  YYSYMBOL_snei = 97,                      /* snei  */
  YYSYMBOL_unop = 98,                      /* unop  */
  YYSYMBOL_diop = 99,                      /* diop  */
  YYSYMBOL_slli = 100,                     /* slli  */
  YYSYMBOL_srli = 101,                     /* srli  */
  YYSYMBOL_sll = 102,                      /* sll  */
  YYSYMBOL_srl = 103,                      /* srl  */
  YYSYMBOL_add = 104,                      /* add  */
  YYSYMBOL_sub = 105,                      /* sub  */
  YYSYMBOL_slt = 106,                      /* slt  */
  YYSYMBOL_sge = 107,                      /* sge  */
  YYSYMBOL_seq = 108,                      /* seq  */
  YYSYMBOL_sne = 109,                      /* sne  */
  YYSYMBOL_lui = 110,                      /* lui  */
  YYSYMBOL_auipc = 111,                    /* auipc  */
  YYSYMBOL_jal = 112,                      /* jal  */
  YYSYMBOL_jalr = 113,                     /* jalr  */
  YYSYMBOL_beq = 114,                      /* beq  */
  YYSYMBOL_bne = 115,                      /* bne  */
  YYSYMBOL_blt = 116,                      /* blt  */
  YYSYMBOL_bge = 117,                      /* bge  */
  YYSYMBOL_ld = 118,                       /* ld  */
  YYSYMBOL_st = 119,                       /* st  */
  YYSYMBOL_ecall = 120,                    /* ecall  */
  YYSYMBOL_ebreak = 121,                   /* ebreak  */
  YYSYMBOL_pcall = 122,                    /* pcall  */
  YYSYMBOL_fence = 123,                    /* fence  */
  YYSYMBOL_mv = 124,                       /* mv  */
  YYSYMBOL_li = 125,                       /* li  */
  YYSYMBOL_la = 126,                       /* la  */
  YYSYMBOL_nop = 127,                      /* nop  */
  YYSYMBOL_call = 128,                     /* call  */
  YYSYMBOL_ret = 129,                      /* ret  */
  YYSYMBOL_ble = 130,                      /* ble  */
  YYSYMBOL_bgt = 131,                      /* bgt  */
  YYSYMBOL_mul = 132,                      /* mul  */
  YYSYMBOL_diV = 133,                      /* diV  */
  YYSYMBOL_rem = 134,                      /* rem  */
  YYSYMBOL_stt = 135,                      /* stt  */
  YYSYMBOL_cst = 136,                      /* cst  */
  YYSYMBOL_ent = 137,                      /* ent  */
  YYSYMBOL_cat = 138,                      /* cat  */
  YYSYMBOL_csrrw = 139,                    /* csrrw  */
  YYSYMBOL_csrrs = 140,                    /* csrrs  */
  YYSYMBOL_csrrc = 141,                    /* csrrc  */
  YYSYMBOL_YYACCEPT = 142,                 /* $accept  */
  YYSYMBOL_width = 143,                    /* width  */
  YYSYMBOL_addr = 144,                     /* addr  */
  YYSYMBOL_gpr = 145,                      /* gpr  */
  YYSYMBOL_i = 146,                        /* i  */
  YYSYMBOL_m = 147,                        /* m  */
  YYSYMBOL_a = 148,                        /* a  */
  YYSYMBOL_Zcsr = 149,                     /* Zcsr  */
  YYSYMBOL_csr = 150,                      /* csr  */
  YYSYMBOL_statement = 151,                /* statement  */
  YYSYMBOL_directive = 152,                /* directive  */
  YYSYMBOL_top = 153,                      /* top  */
  YYSYMBOL_unit = 154,                     /* unit  */
  YYSYMBOL_input = 155                     /* input  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 87 "src/parser.y"


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


#line 534 "gen/gen_parser.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  188
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   381

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  142
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  146
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   396


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   153,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   240,   243,   246,   249,   252,
     255,   258,   261,   264,   267,   270,   273,   276,   279,   282,
     285,   288,   291,   295,   298,   302,   306,   311,   315,   318,
     321,   324,   327,   330,   333,   336,   340,   343,   346,   351,
     355,   359,   361,   366,   369,   372,   376,   379,   382,   385,
     389,   392,   395,   399,   402,   403,   404,   405,   408,   409,
     412,   413,   414,   417,   418,   421,   422
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "imm", "label", "str",
  "id", "\",\"", "\"(\"", "\")\"", "set", "include", "x0", "x1", "x2",
  "x3", "x4", "x5", "x6", "x7", "x8", "x9", "x10", "x11", "x12", "x13",
  "x14", "x15", "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23",
  "x24", "x25", "x26", "x27", "x28", "x29", "x30", "x31", "x32", "x33",
  "x34", "x35", "x36", "x37", "x38", "x39", "x40", "x41", "x42", "x43",
  "x44", "x45", "x46", "x47", "x48", "x49", "x50", "x51", "x52", "x53",
  "x54", "x55", "x56", "x57", "x58", "x59", "x60", "x61", "x62", "x63",
  "x64", "x65", "x66", "x67", "x68", "x69", "x70", "x71", "x72", "x73",
  "x74", "x75", "x76", "x77", "x78", "x79", "x80", "addi", "slti", "sgei",
  "seqi", "snei", "unop", "diop", "slli", "srli", "sll", "srl", "add",
  "sub", "slt", "sge", "seq", "sne", "lui", "auipc", "jal", "jalr", "beq",
  "bne", "blt", "bge", "ld", "st", "ecall", "ebreak", "pcall", "fence",
  "mv", "li", "la", "nop", "call", "ret", "ble", "bgt", "mul", "diV",
  "rem", "stt", "cst", "ent", "cat", "csrrw", "csrrs", "csrrc", "$accept",
  "width", "addr", "gpr", "i", "m", "a", "Zcsr", "csr", "statement",
  "directive", "top", "unit", "input", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-64)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     240,   -64,    21,    23,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    27,
      27,   -64,   -64,   -64,   -64,    31,    31,    31,   -64,    31,
      31,    31,    31,    31,    31,   -64,    27,    31,   -64,    35,
      35,    35,   -64,   -64,   -64,   -64,   -64,   -64,   240,   -64,
      29,   121,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,
     -64,   -64,   -64,   -64,   118,   119,   120,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   -64,
      31,    31,   144,   145,   146,   147,   -64,   148,   151,   152,
     153,   154,   -64,   -64,   155,   156,   157,   -64,   -64,   -64,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,   164,   165,   163,
     167,    31,    31,    31,    31,   166,   168,    31,   169,   163,
     163,    31,    31,    31,    31,    31,    31,    31,    31,   170,
     171,   172,   173,   174,   175,   176,   177,   195,   196,   197,
     198,   203,   204,   206,   207,   208,   -64,   -64,   -64,   -64,
     220,   222,   224,   225,   226,   231,   232,   -64,   -64,   -64,
     -64,   229,   230,   233,   234,   235,   236,   238,   239,   244,
     245,   246,   249,   250,   251,    31,   252,   254,    31,    31,
      31,    31,    31,    31,    31,    31,    31,   163,   163,   163,
     163,   253,   255,   163,    31,    31,    31,   256,    31,    31,
      31,   -64,   -64,   -64,   -64,   -64,   -64,   247,   -64,   -64,
     -64,   -64,   -64,   -64,   -64,   -64,   -64,   -64,   162,   -64,
     -64,   -64,   -64,    31,    31,   -64,   -64,   -64,   -64,   257,
     -64,   -64,   -64,   259,   -64,   258,   260,    31,   -64,   -64,
     -64,   262,   -64
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     146,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,   126,     0,     0,   129,     0,
       0,     0,   134,   136,   135,   137,   141,   142,   143,   145,
       0,     0,   139,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,     0,     0,     0,   121,     0,     0,     0,
       0,     0,   128,   133,     0,     0,     0,   144,     1,   138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,   101,     3,   102,
       0,     0,     0,     0,     0,     0,     0,   116,   119,   118,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,   114,     0,    90,    91,
      98,    99,    92,    93,    94,    95,    96,    97,     0,   104,
     105,   106,   107,     0,     0,   122,   123,   124,   125,     0,
     130,   131,   132,     0,   103,     0,     0,     0,   115,   108,
     109,     0,   127
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -64,    -6,   -63,    -5,   -64,   -64,   -64,   -64,   -25,   -64,
     -64,   -64,    70,   -64
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,   170,   249,   144,    52,    53,    54,    55,   184,    56,
      57,    58,    59,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   171,   185,   186,    61,    62,   188,
     172,   173,   174,   169,   175,   176,   177,   178,   179,   180,
     181,   183,   182,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   189,   190,   191,   192,   187,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   217,   218,   219,   220,   221,   259,   260,   222,   223,
     224,   225,   226,   227,   228,   215,   216,   246,   247,   248,
     250,   334,   258,   255,     0,   256,     0,   269,   270,   271,
     272,   273,   274,   275,   276,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   277,   278,   279,   280,   251,   252,   253,   254,
     281,   282,   257,   283,   284,   285,   261,   262,   263,   264,
     265,   266,   267,   268,   319,   320,   321,   322,   286,   287,
     325,   288,   289,   290,   291,   292,   293,   294,     0,     0,
     295,   296,   297,   298,     1,   299,   300,   301,   302,   303,
       2,     3,   304,   305,   333,   308,   306,   309,     0,   329,
       0,   323,     0,   324,   338,   337,     0,   339,     0,   340,
     307,   342,     0,   310,   311,   312,   313,   314,   315,   316,
     317,   318,     0,     0,     0,     0,     0,     0,     0,   326,
     327,   328,     0,   330,   331,   332,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   335,   336,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   341,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,     0,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51
};

static const yytype_int16 yycheck[] =
{
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    30,    50,    51,     6,     5,     0,
      35,    36,    37,     6,    39,    40,    41,    42,    43,    44,
      46,     6,    47,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,     3,     7,     7,     7,    58,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,   219,   220,     7,     7,
       7,     7,     7,     7,     7,   170,   171,     3,     3,     6,
       3,     9,     3,     7,    -1,     7,    -1,     7,     7,     7,
       7,     7,     7,     7,     7,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,     7,     7,     7,     7,   211,   212,   213,   214,
       7,     7,   217,     7,     7,     7,   221,   222,   223,   224,
     225,   226,   227,   228,   287,   288,   289,   290,     8,     7,
     293,     7,     7,     7,     3,     3,     7,     7,    -1,    -1,
       7,     7,     7,     7,     4,     7,     7,     3,     3,     3,
      10,    11,     3,     3,     7,     3,     5,     3,    -1,     3,
      -1,     8,    -1,     8,     5,     8,    -1,     9,    -1,     9,
     275,     9,    -1,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   294,
     295,   296,    -1,   298,   299,   300,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   323,   324,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   337,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,    -1,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    10,    11,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   146,   147,   148,   149,   151,   152,   153,   154,
     155,     6,     5,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,     6,
     143,   143,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   143,   145,     6,   150,   150,   150,   154,     0,     3,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,   145,   145,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,     3,     3,     6,   144,
       3,   145,   145,   145,   145,     7,     7,   145,     3,   144,
     144,   145,   145,   145,   145,   145,   145,   145,   145,     7,
       7,     7,     7,     7,     7,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,     7,     8,     7,     7,     7,
       7,     3,     3,     7,     7,     7,     7,     7,     7,     7,
       7,     3,     3,     3,     3,     3,     5,   145,     3,     3,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   144,
     144,   144,   144,     8,     8,   144,   145,   145,   145,     3,
     145,   145,   145,     7,     9,   145,   145,     8,     5,     9,
       9,   145,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   142,   143,   144,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   147,   147,   148,   148,   148,   148,
     149,   149,   149,   150,   151,   151,   151,   151,   152,   152,
     153,   153,   153,   154,   154,   155,   155
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       4,     4,     4,     7,     6,     6,     6,     6,     8,     8,
       1,     1,     1,     1,     6,     8,     4,     1,     4,     4,
       4,     2,     6,     6,     6,     6,     1,     9,     2,     1,
       6,     6,     6,     1,     1,     1,     1,     1,     3,     2,
       1,     1,     1,     1,     2,     1,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, parser, ctx, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, parser, ctx); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser *parser, struct asm_ctx *ctx)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (ctx);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, void *scanner, struct parser *parser, struct asm_ctx *ctx)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, parser, ctx);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, void *scanner, struct parser *parser, struct asm_ctx *ctx)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, parser, ctx);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, parser, ctx); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, void *scanner, struct parser *parser, struct asm_ctx *ctx)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (parser);
  YY_USE (ctx);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, struct parser *parser, struct asm_ctx *ctx)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner, parser);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* gpr: x0  */
#line 157 "src/parser.y"
                {(yyval.gpr) =  X0_NUM;}
#line 2127 "gen/gen_parser.c"
    break;

  case 5: /* gpr: x1  */
#line 158 "src/parser.y"
                {(yyval.gpr) =  X1_NUM;}
#line 2133 "gen/gen_parser.c"
    break;

  case 6: /* gpr: x2  */
#line 159 "src/parser.y"
                {(yyval.gpr) =  X2_NUM;}
#line 2139 "gen/gen_parser.c"
    break;

  case 7: /* gpr: x3  */
#line 160 "src/parser.y"
                {(yyval.gpr) =  X3_NUM;}
#line 2145 "gen/gen_parser.c"
    break;

  case 8: /* gpr: x4  */
#line 161 "src/parser.y"
                {(yyval.gpr) =  X4_NUM;}
#line 2151 "gen/gen_parser.c"
    break;

  case 9: /* gpr: x5  */
#line 162 "src/parser.y"
                {(yyval.gpr) =  X5_NUM;}
#line 2157 "gen/gen_parser.c"
    break;

  case 10: /* gpr: x6  */
#line 163 "src/parser.y"
                {(yyval.gpr) =  X6_NUM;}
#line 2163 "gen/gen_parser.c"
    break;

  case 11: /* gpr: x7  */
#line 164 "src/parser.y"
                {(yyval.gpr) =  X7_NUM;}
#line 2169 "gen/gen_parser.c"
    break;

  case 12: /* gpr: x8  */
#line 165 "src/parser.y"
                {(yyval.gpr) =  X8_NUM;}
#line 2175 "gen/gen_parser.c"
    break;

  case 13: /* gpr: x9  */
#line 166 "src/parser.y"
                {(yyval.gpr) =  X9_NUM;}
#line 2181 "gen/gen_parser.c"
    break;

  case 14: /* gpr: x10  */
#line 167 "src/parser.y"
                {(yyval.gpr) = X10_NUM;}
#line 2187 "gen/gen_parser.c"
    break;

  case 15: /* gpr: x11  */
#line 168 "src/parser.y"
                {(yyval.gpr) = X11_NUM;}
#line 2193 "gen/gen_parser.c"
    break;

  case 16: /* gpr: x12  */
#line 169 "src/parser.y"
                {(yyval.gpr) = X12_NUM;}
#line 2199 "gen/gen_parser.c"
    break;

  case 17: /* gpr: x13  */
#line 170 "src/parser.y"
                {(yyval.gpr) = X13_NUM;}
#line 2205 "gen/gen_parser.c"
    break;

  case 18: /* gpr: x14  */
#line 171 "src/parser.y"
                {(yyval.gpr) = X14_NUM;}
#line 2211 "gen/gen_parser.c"
    break;

  case 19: /* gpr: x15  */
#line 172 "src/parser.y"
                {(yyval.gpr) = X15_NUM;}
#line 2217 "gen/gen_parser.c"
    break;

  case 20: /* gpr: x16  */
#line 173 "src/parser.y"
                {(yyval.gpr) = X16_NUM;}
#line 2223 "gen/gen_parser.c"
    break;

  case 21: /* gpr: x17  */
#line 174 "src/parser.y"
                {(yyval.gpr) = X17_NUM;}
#line 2229 "gen/gen_parser.c"
    break;

  case 22: /* gpr: x18  */
#line 175 "src/parser.y"
                {(yyval.gpr) = X18_NUM;}
#line 2235 "gen/gen_parser.c"
    break;

  case 23: /* gpr: x19  */
#line 176 "src/parser.y"
                {(yyval.gpr) = X19_NUM;}
#line 2241 "gen/gen_parser.c"
    break;

  case 24: /* gpr: x20  */
#line 177 "src/parser.y"
                {(yyval.gpr) = X20_NUM;}
#line 2247 "gen/gen_parser.c"
    break;

  case 25: /* gpr: x21  */
#line 178 "src/parser.y"
                {(yyval.gpr) = X21_NUM;}
#line 2253 "gen/gen_parser.c"
    break;

  case 26: /* gpr: x22  */
#line 179 "src/parser.y"
                {(yyval.gpr) = X22_NUM;}
#line 2259 "gen/gen_parser.c"
    break;

  case 27: /* gpr: x23  */
#line 180 "src/parser.y"
                {(yyval.gpr) = X23_NUM;}
#line 2265 "gen/gen_parser.c"
    break;

  case 28: /* gpr: x24  */
#line 181 "src/parser.y"
                {(yyval.gpr) = X24_NUM;}
#line 2271 "gen/gen_parser.c"
    break;

  case 29: /* gpr: x25  */
#line 182 "src/parser.y"
                {(yyval.gpr) = X25_NUM;}
#line 2277 "gen/gen_parser.c"
    break;

  case 30: /* gpr: x26  */
#line 183 "src/parser.y"
                {(yyval.gpr) = X26_NUM;}
#line 2283 "gen/gen_parser.c"
    break;

  case 31: /* gpr: x27  */
#line 184 "src/parser.y"
                {(yyval.gpr) = X27_NUM;}
#line 2289 "gen/gen_parser.c"
    break;

  case 32: /* gpr: x28  */
#line 185 "src/parser.y"
                {(yyval.gpr) = X28_NUM;}
#line 2295 "gen/gen_parser.c"
    break;

  case 33: /* gpr: x29  */
#line 186 "src/parser.y"
                {(yyval.gpr) = X29_NUM;}
#line 2301 "gen/gen_parser.c"
    break;

  case 34: /* gpr: x30  */
#line 187 "src/parser.y"
                {(yyval.gpr) = X30_NUM;}
#line 2307 "gen/gen_parser.c"
    break;

  case 35: /* gpr: x31  */
#line 188 "src/parser.y"
                {(yyval.gpr) = X31_NUM;}
#line 2313 "gen/gen_parser.c"
    break;

  case 36: /* gpr: x32  */
#line 189 "src/parser.y"
                {(yyval.gpr) = X32_NUM;}
#line 2319 "gen/gen_parser.c"
    break;

  case 37: /* gpr: x33  */
#line 190 "src/parser.y"
                {(yyval.gpr) = X33_NUM;}
#line 2325 "gen/gen_parser.c"
    break;

  case 38: /* gpr: x34  */
#line 191 "src/parser.y"
                {(yyval.gpr) = X34_NUM;}
#line 2331 "gen/gen_parser.c"
    break;

  case 39: /* gpr: x35  */
#line 192 "src/parser.y"
                {(yyval.gpr) = X35_NUM;}
#line 2337 "gen/gen_parser.c"
    break;

  case 40: /* gpr: x36  */
#line 193 "src/parser.y"
                {(yyval.gpr) = X36_NUM;}
#line 2343 "gen/gen_parser.c"
    break;

  case 41: /* gpr: x37  */
#line 194 "src/parser.y"
                {(yyval.gpr) = X37_NUM;}
#line 2349 "gen/gen_parser.c"
    break;

  case 42: /* gpr: x38  */
#line 195 "src/parser.y"
                {(yyval.gpr) = X38_NUM;}
#line 2355 "gen/gen_parser.c"
    break;

  case 43: /* gpr: x39  */
#line 196 "src/parser.y"
                {(yyval.gpr) = X39_NUM;}
#line 2361 "gen/gen_parser.c"
    break;

  case 44: /* gpr: x40  */
#line 197 "src/parser.y"
                {(yyval.gpr) = X40_NUM;}
#line 2367 "gen/gen_parser.c"
    break;

  case 45: /* gpr: x41  */
#line 198 "src/parser.y"
                {(yyval.gpr) = X41_NUM;}
#line 2373 "gen/gen_parser.c"
    break;

  case 46: /* gpr: x42  */
#line 199 "src/parser.y"
                {(yyval.gpr) = X42_NUM;}
#line 2379 "gen/gen_parser.c"
    break;

  case 47: /* gpr: x43  */
#line 200 "src/parser.y"
                {(yyval.gpr) = X43_NUM;}
#line 2385 "gen/gen_parser.c"
    break;

  case 48: /* gpr: x44  */
#line 201 "src/parser.y"
                {(yyval.gpr) = X44_NUM;}
#line 2391 "gen/gen_parser.c"
    break;

  case 49: /* gpr: x45  */
#line 202 "src/parser.y"
                {(yyval.gpr) = X45_NUM;}
#line 2397 "gen/gen_parser.c"
    break;

  case 50: /* gpr: x46  */
#line 203 "src/parser.y"
                {(yyval.gpr) = X46_NUM;}
#line 2403 "gen/gen_parser.c"
    break;

  case 51: /* gpr: x47  */
#line 204 "src/parser.y"
                {(yyval.gpr) = X47_NUM;}
#line 2409 "gen/gen_parser.c"
    break;

  case 52: /* gpr: x48  */
#line 205 "src/parser.y"
                {(yyval.gpr) = X48_NUM;}
#line 2415 "gen/gen_parser.c"
    break;

  case 53: /* gpr: x49  */
#line 206 "src/parser.y"
                {(yyval.gpr) = X49_NUM;}
#line 2421 "gen/gen_parser.c"
    break;

  case 54: /* gpr: x50  */
#line 207 "src/parser.y"
                {(yyval.gpr) = X50_NUM;}
#line 2427 "gen/gen_parser.c"
    break;

  case 55: /* gpr: x51  */
#line 208 "src/parser.y"
                {(yyval.gpr) = X51_NUM;}
#line 2433 "gen/gen_parser.c"
    break;

  case 56: /* gpr: x52  */
#line 209 "src/parser.y"
                {(yyval.gpr) = X52_NUM;}
#line 2439 "gen/gen_parser.c"
    break;

  case 57: /* gpr: x53  */
#line 210 "src/parser.y"
                {(yyval.gpr) = X53_NUM;}
#line 2445 "gen/gen_parser.c"
    break;

  case 58: /* gpr: x54  */
#line 211 "src/parser.y"
                {(yyval.gpr) = X54_NUM;}
#line 2451 "gen/gen_parser.c"
    break;

  case 59: /* gpr: x55  */
#line 212 "src/parser.y"
                {(yyval.gpr) = X55_NUM;}
#line 2457 "gen/gen_parser.c"
    break;

  case 60: /* gpr: x56  */
#line 213 "src/parser.y"
                {(yyval.gpr) = X56_NUM;}
#line 2463 "gen/gen_parser.c"
    break;

  case 61: /* gpr: x57  */
#line 214 "src/parser.y"
                {(yyval.gpr) = X57_NUM;}
#line 2469 "gen/gen_parser.c"
    break;

  case 62: /* gpr: x58  */
#line 215 "src/parser.y"
                {(yyval.gpr) = X58_NUM;}
#line 2475 "gen/gen_parser.c"
    break;

  case 63: /* gpr: x59  */
#line 216 "src/parser.y"
                {(yyval.gpr) = X59_NUM;}
#line 2481 "gen/gen_parser.c"
    break;

  case 64: /* gpr: x60  */
#line 217 "src/parser.y"
                {(yyval.gpr) = X60_NUM;}
#line 2487 "gen/gen_parser.c"
    break;

  case 65: /* gpr: x61  */
#line 218 "src/parser.y"
                {(yyval.gpr) = X61_NUM;}
#line 2493 "gen/gen_parser.c"
    break;

  case 66: /* gpr: x62  */
#line 219 "src/parser.y"
                {(yyval.gpr) = X62_NUM;}
#line 2499 "gen/gen_parser.c"
    break;

  case 67: /* gpr: x63  */
#line 220 "src/parser.y"
                {(yyval.gpr) = X63_NUM;}
#line 2505 "gen/gen_parser.c"
    break;

  case 68: /* gpr: x64  */
#line 221 "src/parser.y"
                {(yyval.gpr) = X64_NUM;}
#line 2511 "gen/gen_parser.c"
    break;

  case 69: /* gpr: x65  */
#line 222 "src/parser.y"
                {(yyval.gpr) = X65_NUM;}
#line 2517 "gen/gen_parser.c"
    break;

  case 70: /* gpr: x66  */
#line 223 "src/parser.y"
                {(yyval.gpr) = X66_NUM;}
#line 2523 "gen/gen_parser.c"
    break;

  case 71: /* gpr: x67  */
#line 224 "src/parser.y"
                {(yyval.gpr) = X67_NUM;}
#line 2529 "gen/gen_parser.c"
    break;

  case 72: /* gpr: x68  */
#line 225 "src/parser.y"
                {(yyval.gpr) = X68_NUM;}
#line 2535 "gen/gen_parser.c"
    break;

  case 73: /* gpr: x69  */
#line 226 "src/parser.y"
                {(yyval.gpr) = X69_NUM;}
#line 2541 "gen/gen_parser.c"
    break;

  case 74: /* gpr: x70  */
#line 227 "src/parser.y"
                {(yyval.gpr) = X70_NUM;}
#line 2547 "gen/gen_parser.c"
    break;

  case 75: /* gpr: x71  */
#line 228 "src/parser.y"
                {(yyval.gpr) = X71_NUM;}
#line 2553 "gen/gen_parser.c"
    break;

  case 76: /* gpr: x72  */
#line 229 "src/parser.y"
                {(yyval.gpr) = X72_NUM;}
#line 2559 "gen/gen_parser.c"
    break;

  case 77: /* gpr: x73  */
#line 230 "src/parser.y"
                {(yyval.gpr) = X73_NUM;}
#line 2565 "gen/gen_parser.c"
    break;

  case 78: /* gpr: x74  */
#line 231 "src/parser.y"
                {(yyval.gpr) = X74_NUM;}
#line 2571 "gen/gen_parser.c"
    break;

  case 79: /* gpr: x75  */
#line 232 "src/parser.y"
                {(yyval.gpr) = X75_NUM;}
#line 2577 "gen/gen_parser.c"
    break;

  case 80: /* gpr: x76  */
#line 233 "src/parser.y"
                {(yyval.gpr) = X76_NUM;}
#line 2583 "gen/gen_parser.c"
    break;

  case 81: /* gpr: x77  */
#line 234 "src/parser.y"
                {(yyval.gpr) = X77_NUM;}
#line 2589 "gen/gen_parser.c"
    break;

  case 82: /* gpr: x78  */
#line 235 "src/parser.y"
                {(yyval.gpr) = X78_NUM;}
#line 2595 "gen/gen_parser.c"
    break;

  case 83: /* gpr: x79  */
#line 236 "src/parser.y"
                {(yyval.gpr) = X79_NUM;}
#line 2601 "gen/gen_parser.c"
    break;

  case 84: /* gpr: x80  */
#line 237 "src/parser.y"
                {(yyval.gpr) = X80_NUM;}
#line 2607 "gen/gen_parser.c"
    break;

  case 85: /* i: addi gpr "," gpr "," imm  */
#line 241 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_ADDI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2613 "gen/gen_parser.c"
    break;

  case 86: /* i: slti gpr "," gpr "," imm  */
#line 244 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SLTI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2619 "gen/gen_parser.c"
    break;

  case 87: /* i: sgei gpr "," gpr "," imm  */
#line 247 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SGEI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2625 "gen/gen_parser.c"
    break;

  case 88: /* i: seqi gpr "," gpr "," imm  */
#line 250 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SEQI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2631 "gen/gen_parser.c"
    break;

  case 89: /* i: snei gpr "," gpr "," imm  */
#line 253 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SNEI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2637 "gen/gen_parser.c"
    break;

  case 90: /* i: slli gpr "," gpr "," imm  */
#line 256 "src/parser.y"
        {check_shift((yyvsp[0].tri)); emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SLLI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2643 "gen/gen_parser.c"
    break;

  case 91: /* i: srli gpr "," gpr "," imm  */
#line 259 "src/parser.y"
        {check_shift((yyvsp[0].tri)); emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_SRLI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2649 "gen/gen_parser.c"
    break;

  case 92: /* i: add gpr "," gpr "," gpr  */
#line 262 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_ADD, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2655 "gen/gen_parser.c"
    break;

  case 93: /* i: sub gpr "," gpr "," gpr  */
#line 265 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SUB, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2661 "gen/gen_parser.c"
    break;

  case 94: /* i: slt gpr "," gpr "," gpr  */
#line 268 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SLT, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2667 "gen/gen_parser.c"
    break;

  case 95: /* i: sge gpr "," gpr "," gpr  */
#line 271 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SGE, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2673 "gen/gen_parser.c"
    break;

  case 96: /* i: seq gpr "," gpr "," gpr  */
#line 274 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SEQ, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2679 "gen/gen_parser.c"
    break;

  case 97: /* i: sne gpr "," gpr "," gpr  */
#line 277 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SNE, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2685 "gen/gen_parser.c"
    break;

  case 98: /* i: sll gpr "," gpr "," gpr  */
#line 280 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SLL, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2691 "gen/gen_parser.c"
    break;

  case 99: /* i: srl gpr "," gpr "," gpr  */
#line 283 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_SRL, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2697 "gen/gen_parser.c"
    break;

  case 100: /* i: lui gpr "," imm  */
#line 286 "src/parser.y"
        {emit_u(ctx, OPCODE_LUI, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2703 "gen/gen_parser.c"
    break;

  case 101: /* i: auipc gpr "," imm  */
#line 289 "src/parser.y"
        {emit_u(ctx, OPCODE_AUIPC, (yyvsp[-2].gpr), (yyvsp[0].tri));}
#line 2709 "gen/gen_parser.c"
    break;

  case 102: /* i: jal gpr "," addr  */
#line 292 "src/parser.y"
        {emit_reloc(ctx, RELOC_J, (yyvsp[0].str));
	 emit_u(ctx, OPCODE_JAL, (yyvsp[-2].gpr), 0);}
#line 2716 "gen/gen_parser.c"
    break;

  case 103: /* i: jalr gpr "," imm "(" gpr ")"  */
#line 296 "src/parser.y"
        {emit_i(ctx, OPCODE_JALR, (yyvsp[-5].gpr), 0, (yyvsp[-1].gpr), (yyvsp[-3].tri));}
#line 2722 "gen/gen_parser.c"
    break;

  case 104: /* i: beq gpr "," gpr "," addr  */
#line 299 "src/parser.y"
        {emit_reloc(ctx, RELOC_B, (yyvsp[0].str));
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BEQ, (yyvsp[-4].gpr), (yyvsp[-2].gpr), 0);}
#line 2729 "gen/gen_parser.c"
    break;

  case 105: /* i: bne gpr "," gpr "," addr  */
#line 303 "src/parser.y"
        {emit_reloc(ctx, RELOC_B, (yyvsp[0].str));
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BNE, (yyvsp[-4].gpr), (yyvsp[-2].gpr), 0);}
#line 2736 "gen/gen_parser.c"
    break;

  case 106: /* i: blt gpr "," gpr "," addr  */
#line 307 "src/parser.y"
        {emit_reloc(ctx, RELOC_B, (yyvsp[0].str));
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BLT, (yyvsp[-4].gpr), (yyvsp[-2].gpr), 0);
	 }
#line 2744 "gen/gen_parser.c"
    break;

  case 107: /* i: bge gpr "," gpr "," addr  */
#line 312 "src/parser.y"
        {emit_reloc(ctx, RELOC_B, (yyvsp[0].str));
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BGE, (yyvsp[-4].gpr), (yyvsp[-2].gpr), 0);}
#line 2751 "gen/gen_parser.c"
    break;

  case 108: /* i: ld width gpr "," imm "(" gpr ")"  */
#line 316 "src/parser.y"
        {emit_i(ctx, OPCODE_LOAD, (yyvsp[-5].gpr), check_width((yyvsp[-6].str)), (yyvsp[-1].gpr), (yyvsp[-3].tri));}
#line 2757 "gen/gen_parser.c"
    break;

  case 109: /* i: st width gpr "," imm "(" gpr ")"  */
#line 319 "src/parser.y"
        {emit_s(ctx, OPCODE_STORE, check_width((yyvsp[-6].str)), (yyvsp[-5].gpr), (yyvsp[-1].gpr), (yyvsp[-3].tri));}
#line 2763 "gen/gen_parser.c"
    break;

  case 110: /* i: ecall  */
#line 322 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_ECALL, X0_NUM, 0);}
#line 2769 "gen/gen_parser.c"
    break;

  case 111: /* i: ebreak  */
#line 325 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_EBREAK, X0_NUM, 0);}
#line 2775 "gen/gen_parser.c"
    break;

  case 112: /* i: pcall  */
#line 328 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, X0_NUM, SYSTEM_PCALL, X0_NUM, 0);}
#line 2781 "gen/gen_parser.c"
    break;

  case 113: /* i: fence  */
#line 331 "src/parser.y"
        {emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_FENCE, X0_NUM, 0); /* still todo */}
#line 2787 "gen/gen_parser.c"
    break;

  case 114: /* i: unop gpr "," gpr "," str  */
#line 334 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-4].gpr), OP_IMM_UNOP, (yyvsp[-2].gpr), check_nop((yyvsp[0].str)));}
#line 2793 "gen/gen_parser.c"
    break;

  case 115: /* i: diop gpr "," gpr "," gpr "," str  */
#line 337 "src/parser.y"
        {emit_d(ctx, OPCODE_DIOP, (yyvsp[-6].gpr), (yyvsp[-4].gpr), (yyvsp[-2].gpr), check_nop3((yyvsp[0].str)));}
#line 2799 "gen/gen_parser.c"
    break;

  case 116: /* i: mv gpr "," gpr  */
#line 341 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-2].gpr), OP_IMM_ADDI, (yyvsp[0].gpr), 0);}
#line 2805 "gen/gen_parser.c"
    break;

  case 117: /* i: nop  */
#line 344 "src/parser.y"
        {emit_i(ctx, OPCODE_OP_IMM, X0_NUM, OP_IMM_ADDI, X0_NUM, 0);}
#line 2811 "gen/gen_parser.c"
    break;

  case 118: /* i: la gpr "," addr  */
#line 347 "src/parser.y"
        {emit_reloc(ctx, RELOC_LA, (yyvsp[0].str));
	 emit_u(ctx, OPCODE_LUI, (yyvsp[-2].gpr), 0);
	 emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-2].gpr), OP_IMM_ADDI, (yyvsp[-2].gpr), 0);}
#line 2819 "gen/gen_parser.c"
    break;

  case 119: /* i: li gpr "," imm  */
#line 352 "src/parser.y"
        {/** @todo skip lui if we can avoid it? */
	 emit_u(ctx, OPCODE_LUI, (yyvsp[-2].gpr), tri_sr((yyvsp[0].tri), 9));
	 emit_i(ctx, OPCODE_OP_IMM, (yyvsp[-2].gpr), OP_IMM_ADDI, (yyvsp[-2].gpr), tri_mask((yyvsp[0].tri), 9));}
#line 2827 "gen/gen_parser.c"
    break;

  case 120: /* i: call gpr "," addr  */
#line 356 "src/parser.y"
        {emit_reloc(ctx, RELOC_CALL, (yyvsp[0].str));
	 emit_u(ctx, OPCODE_AUIPC, (yyvsp[-2].gpr), 0);
	 emit_i(ctx, OPCODE_JALR, (yyvsp[-2].gpr), 0, (yyvsp[-2].gpr), 0);}
#line 2835 "gen/gen_parser.c"
    break;

  case 121: /* i: ret gpr  */
#line 360 "src/parser.y"
        {emit_i(ctx, OPCODE_JALR, X0_NUM, 0, (yyvsp[0].gpr), 0);}
#line 2841 "gen/gen_parser.c"
    break;

  case 122: /* i: ble gpr "," gpr "," addr  */
#line 362 "src/parser.y"
        {emit_reloc(ctx, RELOC_B, (yyvsp[0].str));
	 emit_s(ctx, OPCODE_BRANCH, BRANCH_BGE, (yyvsp[-2].gpr), (yyvsp[-4].gpr), 0);}
#line 2848 "gen/gen_parser.c"
    break;

  case 123: /* m: mul gpr "," gpr "," gpr  */
#line 367 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_MUL, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2854 "gen/gen_parser.c"
    break;

  case 124: /* m: diV gpr "," gpr "," gpr  */
#line 370 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_DIV, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2860 "gen/gen_parser.c"
    break;

  case 125: /* m: rem gpr "," gpr "," gpr  */
#line 373 "src/parser.y"
        {emit_r(ctx, OPCODE_OP, (yyvsp[-4].gpr), OP_DIV, (yyvsp[-2].gpr), (yyvsp[0].gpr), 0);}
#line 2866 "gen/gen_parser.c"
    break;

  case 126: /* a: stt  */
#line 377 "src/parser.y"
        {emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_STT, X0_NUM, 0);}
#line 2872 "gen/gen_parser.c"
    break;

  case 127: /* a: cst width "," gpr "," imm "(" gpr ")"  */
#line 380 "src/parser.y"
        {emit_s(ctx, OPCODE_STORE, STORE_CST | check_width((yyvsp[-7].str)), (yyvsp[-5].gpr), (yyvsp[-1].gpr), (yyvsp[-3].tri));}
#line 2878 "gen/gen_parser.c"
    break;

  case 128: /* a: ent gpr  */
#line 383 "src/parser.y"
        {emit_i(ctx, OPCODE_MEM, (yyvsp[0].gpr), MEM_ENT, X0_NUM, 0);}
#line 2884 "gen/gen_parser.c"
    break;

  case 129: /* a: cat  */
#line 386 "src/parser.y"
        {emit_i(ctx, OPCODE_MEM, X0_NUM, MEM_CAT, X0_NUM, 0);}
#line 2890 "gen/gen_parser.c"
    break;

  case 130: /* Zcsr: csrrw csr "," gpr "," gpr  */
#line 390 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, (yyvsp[-2].gpr), SYSTEM_CSRRW, (yyvsp[0].gpr), check_csr((yyvsp[-4].str)));}
#line 2896 "gen/gen_parser.c"
    break;

  case 131: /* Zcsr: csrrs csr "," gpr "," gpr  */
#line 393 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, (yyvsp[-2].gpr), SYSTEM_CSRRS, (yyvsp[0].gpr), check_csr((yyvsp[-4].str)));}
#line 2902 "gen/gen_parser.c"
    break;

  case 132: /* Zcsr: csrrc csr "," gpr "," gpr  */
#line 396 "src/parser.y"
        {emit_i(ctx, OPCODE_SYSTEM, (yyvsp[-2].gpr), SYSTEM_CSRRC, (yyvsp[0].gpr), check_csr((yyvsp[-4].str)));}
#line 2908 "gen/gen_parser.c"
    break;

  case 139: /* directive: include str  */
#line 409 "src/parser.y"
                      {process_file(ctx, (yyvsp[0].str));}
#line 2914 "gen/gen_parser.c"
    break;

  case 140: /* top: label  */
#line 412 "src/parser.y"
                {emit_label(ctx, (yyvsp[0].str));}
#line 2920 "gen/gen_parser.c"
    break;


#line 2924 "gen/gen_parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, parser, ctx, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, parser, ctx);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, parser, ctx);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, parser, ctx, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, parser, ctx);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, parser, ctx);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 424 "src/parser.y"


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
