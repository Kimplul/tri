/* SPDX-License-Identifier: copyleft-next-0.3.1 */
/* Copyright 2023 Kim Kuparinen < kimi.h.kuparinen@gmail.com > */

%option reentrant noyywrap nounput noinput nodefault
%{
#define FROM_LEXER
#include <tasm/parser.h>

static void update_yylloc(struct parser *parser, YYLTYPE *lloc, const char *text)
{
	(void)parser;

	lloc->first_line = lloc->last_line;
	lloc->first_column = lloc->last_column;

	for (size_t i = 0; text[i] != 0; ++i) {
		if (text[i] == '\n') {
			lloc->last_line++;
			/* flex uses 1 based indexing */
			lloc->last_column = 1;
		} else {
			lloc->last_column++;
		}
	}
}

#define YY_USER_ACTION update_yylloc(parser, yylloc, yytext);
%}

%x SC_COMMENT

id	[_a-zA-Z][_a-zA-Z0-9]*
label	{id}[[:space:]]*:

dec	-?[0-9]+
tri	0t[01i]+
hept	0h[0-9A-HKMNPRTVXZa-hkmnprtvxz]+
imm	{tri}|{hept}|{dec}

str	\"(\\.|[^"\\])*\"

%%

{label} {
	/* strip trailing ':' */
	char *s = yytext + strlen(yytext);
	s[-1] = '\0';

	yylval->str = yytext;
	return label;
}

{imm} {
	yylval->tri = parse_imm(yytext);
	return imm;
}

{str} {
	/* strip leading and trailing " */
	char *s = yytext + strlen(yytext);
	s[-1] = '\0';

	yylval->str = yytext + 1;
	return str;
}

".set" {return set;}
".include" {return include;}

"x0"  {return x0;}
"x1"  {return x1;}
"x2"  {return x2;}
"x3"  {return x3;}
"x4"  {return x4;}
"x5"  {return x5;}
"x6"  {return x6;}
"x7"  {return x7;}
"x8"  {return x8;}
"x9"  {return x9;}
"x10" {return x10;}
"x11" {return x11;}
"x12" {return x12;}
"x13" {return x13;}
"x14" {return x14;}
"x15" {return x15;}
"x16" {return x16;}
"x17" {return x17;}
"x18" {return x18;}
"x19" {return x19;}
"x20" {return x20;}
"x21" {return x21;}
"x22" {return x22;}
"x23" {return x23;}
"x24" {return x24;}
"x25" {return x25;}
"x26" {return x26;}
"x27" {return x27;}
"x28" {return x28;}
"x29" {return x29;}
"x30" {return x30;}
"x31" {return x31;}
"x32" {return x32;}
"x33" {return x33;}
"x34" {return x34;}
"x35" {return x35;}
"x36" {return x36;}
"x37" {return x37;}
"x38" {return x38;}
"x39" {return x39;}
"x40" {return x40;}
"x41" {return x41;}
"x42" {return x42;}
"x43" {return x43;}
"x44" {return x44;}
"x45" {return x45;}
"x46" {return x46;}
"x47" {return x47;}
"x48" {return x48;}
"x49" {return x49;}
"x50" {return x50;}
"x51" {return x51;}
"x52" {return x52;}
"x53" {return x53;}
"x54" {return x54;}
"x55" {return x55;}
"x56" {return x56;}
"x57" {return x57;}
"x58" {return x58;}
"x59" {return x59;}
"x60" {return x60;}
"x61" {return x61;}
"x62" {return x62;}
"x63" {return x63;}
"x64" {return x64;}
"x65" {return x65;}
"x66" {return x66;}
"x67" {return x67;}
"x68" {return x68;}
"x69" {return x69;}
"x70" {return x70;}
"x71" {return x71;}
"x72" {return x72;}
"x73" {return x73;}
"x74" {return x74;}
"x75" {return x75;}
"x76" {return x76;}
"x77" {return x77;}
"x78" {return x78;}
"x79" {return x79;}
"x80" {return x80;}

"addi"	 {return addi; /* i */}
"slti"	 {return slti;}
"sgei"   {return sgei;}
"seqi"   {return seqi;}
"snei"   {return snei;}
"unop"	 {return unop;}
"diop"	 {return diop;}
"slli"	 {return slli;}
"srli"	 {return srli;}
"sll"	 {return sll;}
"srl"	 {return srl;}
"add"	 {return add;}
"sub"	 {return sub;}
"slt"	 {return slt;}
"sge"	 {return sge;}
"seq"	 {return seq;}
"sne"	 {return sne;}
"lui"	 {return lui;}
"auipc"	 {return auipc;}
"jal"	 {return jal;}
"jalr"	 {return jalr;}
"beq"	 {return beq;}
"bne"	 {return bne;}
"blt"	 {return blt;}
"bge"	 {return bge;}
"ld"	 {return ld;}
"st"	 {return st;}
"ecall"	 {return ecall;}
"ebreak" {return ebreak;}
"pcall"  {return pcall;}
"fence"  {return fence;}
"nop"    {return nop; /* meta */}
"mv"	 {return mv;}
"li"     {return li;}
"la"     {return la;}

"mul" {return mul; /* m */}
"div" {return diV;}
"rem" {return rem;}

"stt" {return stt; /* a */}
"cst" {return cst;}
"ent" {return ent;}
"cat" {return cat;}

"csrrw" {return csrrw; /* Zcsr */}
"csrrs" {return csrrs;}
"csrrc" {return csrrc;}

"//".* {/* skip line comments */}

"/*"	{BEGIN(SC_COMMENT);}
<SC_COMMENT>{
	"/*"	{++parser->comment_nesting;}
	"*"+"/"	{
		if (parser->comment_nesting)
			--parser->comment_nesting;
		else
			BEGIN(INITIAL);
	}

	"*"+ {}
	[^/*\n]+ {}
	[/] {}
	\n {}
}

{id} {
	yylval->str = yytext;
	return id;
}

"(" {return LPAREN;}
")" {return RPAREN;}
"," {return COMMA;}

[[:space:]]+	{/* skip whitespace */}

. {
	struct src_issue issue;
	issue.loc = to_src_loc(yylloc);
	issue.fctx.fbuf = parser->buf;
	issue.fctx.fname = parser->fname;
	src_issue(issue, "unexpected token: %s", yytext);
	parser->failed = true;
}
%%
