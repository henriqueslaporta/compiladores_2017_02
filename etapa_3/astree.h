
#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define MAX_SONS 4

#define AST_LCMD 	1
#define AST_CMD 	2
#define AST_SYMBOL 	3

#define AST_ADD 	4
#define AST_SUB 	5
#define AST_MUL 	6
#define AST_DIV 	7
#define AST_LESS	8
#define AST_GREAT	9
#define AST_NEG 	10
#define AST_EQ 		21
#define AST_LE 		11
#define AST_GE 		12
#define AST_NE 		13
#define AST_AND 	14
#define AST_OR 		15
#define AST_EXP_P 	22

#define AST_VAR_DEC 	23
#define AST_VECTOR_DEC 	24

#define AST_VEC_INT 	25
#define AST_VEC_REAL 	26
#define AST_VEC_CHAR	27

#define AST_KW_BYTE 	28
#define AST_KW_SHORT 	29
#define AST_KW_LONG		30
#define AST_KW_FLOAT 	31
#define AST_KW_DOUBLE	32


typedef struct ast_node{
  int type;
  HASH_NODE *symbol;
  struct asst_node* sons[MAX_SONS];
}AST;

//PROTOTYPES

AST* astCreate(int type, HASH_NODE *symbol, AST *son1, AST *son2, AST *son3, AST *son4);
void astPrint(AST *node, int level);

//END OF FILE

#endif
