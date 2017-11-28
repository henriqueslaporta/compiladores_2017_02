#ifndef GENCO_HEADER
#define GENCO_HEADER

#include "hash.h"
#include "astree.h"


#define TAC_ADD 1
#define TAC_SUB 2
#define TAC_MUL 3
#define TAC_DIV 4
#define TAC_LESS 5
#define TAC_GREAT 6
#define TAC_NEG 7
#define TAC_LE 8
#define TAC_GE 9
#define TAC_EQ 10
#define TAC_NE 11
#define TAC_AND 12
#define TAC_OR 13
#define TAC_ASS 14
#define TAC_VECWRITE 15
#define TAC_VECREAD 16
#define TAC_INPUT 17
#define TAC_OUTPUT 18
#define TAC_RETURN 19
#define TAC_JZ 20
#define TAC_JMP 21
#define TAC_LABEL 22
#define TAC_BEGINFUN 23
#define TAC_ENDFUN 24
#define TAC_CALL 25
#define TAC_ARG 26
#define TAC_SYMBOL 27


typedef struct struct_tac{
	int type;
	HASH_NODE* res;
	HASH_NODE* op1;
	HASH_NODE* op2;
	struct struct_tac* prev;
	struct struct_tac* next;
}TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tacGenerator(AST* NODE);
TAC* tacJoin(TAC* l1, TAC* l2);
void tacPrintBack(TAC* last);

#endif
