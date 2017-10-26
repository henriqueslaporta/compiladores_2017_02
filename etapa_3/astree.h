#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_MUL 3
#define AST_ASSING 4

typedef struct ast_node{
  int type;
  HASH_NODE *symbol;
  AST *sons[MAX_SONS];
}AST;

//PROTOTYPES

AST* astCreate(int type, HASH_NODE *symbol, AST *son1, AST *son2, AST *son3, AST *son4);
void astPrint(AST *node, int level);

//END OF FILE
