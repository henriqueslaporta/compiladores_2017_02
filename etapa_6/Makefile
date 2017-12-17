etapa6: y.tab.o lex.yy.o hash.o main.o astree.o semantic.o genco.o
	gcc y.tab.o lex.yy.o hash.o main.o astree.o semantic.o genco.o  -o etapa6

lex.yy.o: lex.yy.c
	gcc lex.yy.c -c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -r solved parser.y

hash.o: hash.c
	gcc hash.c -c

astree.o: astree.c
	gcc -c astree.c

semantic.o: semantic.c
	gcc -c semantic.c

genco.o: genco.c
	gcc -c genco.c

main.o: main.c
	gcc main.c -c

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa6 lex.yy.c *.o y.tab.c y.tab.h y.output
