run: phase2
	./phase2 input.txt
clean : 
	rm phase2

phase2: lex.yy.c syntax_anal.tab.c
	gcc syntax_anal.tab.c lex.yy.c syntax_functions.c intermediate.c -o phase2 -lm

lex.yy.c: lexical_anal.l
	flex lexical_anal.l

suntax_anal.tab.c: syntax_anal.yy
	bison -v -d syntax_anal.y
	
