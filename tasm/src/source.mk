SOURCES		!= echo src/*.c
TASM_SOURCES	+= $(SOURCES) gen/gen_parser.c

gen/gen_parser.c: src/parser.y gen/gen_lexer.inc
	bison -Wcounterexamples -o gen/gen_parser.c src/parser.y

gen/gen_lexer.inc: src/lexer.l
	flex -o gen/gen_lexer.inc src/lexer.l
