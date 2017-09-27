etapa1: lex.yy.o hash.o main.o
	gcc lex.yy.o hash.o main.o -o etapa1

lex.yy.o: lex.yy.c
	gcc lex.yy.c -c

hash.o: hash.c
	gcc hash.c -c

main.o: main.c
	gcc main.c -c

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa1 lex.yy.c *.o
