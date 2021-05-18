all: biflex

y.tab.c: parser.y
	bison -dy parser.y

lex.yy.c: lexer.l
	flex lexer.l

biflex: ast.c lex.yy.c y.tab.c
	gcc ast.c lex.yy.c y.tab.c -lfl -o biflex
	make clean-temp


clean-temp:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f lex.yy.c

clean:
	make clean-temp
	rm -f biflex