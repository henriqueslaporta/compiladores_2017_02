
#ifndef ASTREE_C
#define ASTREE_C

#include <stdio.h>
#include <stdlib.h>

#include "astree.h"
#include "hash.h"

AST* astCreate(int type, HASH_NODE *symbol, AST *son0, AST *son1, AST *son2, AST *son3){
  AST *new_node;
  new_node = (AST*) calloc (1, sizeof(AST));

  new_node->type = type;
  new_node->symbol = symbol;
  new_node->sons[0] = son0;
  new_node->sons[1] = son1;
  new_node->sons[2] = son2;
  new_node->sons[3] = son3;

  return new_node;
}

void astPrint(AST *node, int level){
	int i;
	if(node){
		for (i=0; i<level; ++i){
			fprintf(stderr, "");
		}
		
		fprintf(stderr, "AST( ");
		
		switch (node->type){
			case AST_SYMBOL: fprintf(stderr, "SYMBOL,"); break;
			case AST_ADD: fprintf(stderr, "AST_ADD,"); break;
			case AST_MUL: fprintf(stderr, "AST_MUL,"); break;
			default: fprintf(stderr, "UNKNOWN"); break;
		}
		
		if(node->symbol){
			fprintf(stderr, "%s\n", node->symbol->text);
		}else{
			fprintf(stderr, "\n");
		}
		
		for(i=0; i<MAX_SONS; ++i){
			astPrint(node->sons[i],0);
		}
		
	}	
}
#endif
