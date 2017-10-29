
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
			fprintf(stderr, "   ");
		}
		
		switch (node->type){
			case AST_DEC: fprintf(stderr, "AST_DEC "); break;	
			case AST_SYMBOL: fprintf(stderr, "SYMBOL "); break;
			case AST_ADD: fprintf(stderr, "AST_ADD "); break;
			case AST_SUB: fprintf(stderr, "AST_SUB "); break;
			case AST_MUL: fprintf(stderr, "AST_MUL "); break;
			case AST_DIV: fprintf(stderr, "AST_DIV "); break;
			case AST_LESS: fprintf(stderr, "AST_LESS "); break;
			case AST_GREAT: fprintf(stderr, "AST_GREAT "); break;
			case AST_NEG: fprintf(stderr, "AST_NEG "); break;
			case AST_EQ: fprintf(stderr, "AST_EQ "); break;
			case AST_LE: fprintf(stderr, "AST_LE "); break;
			case AST_GE: fprintf(stderr, "AST_GE "); break;
			case AST_NE: fprintf(stderr, "AST_NE "); break;
			case AST_AND: fprintf(stderr, "AST_AND "); break;
			case AST_OR: fprintf(stderr, "AST_OR "); break;
			case AST_VAR_DEC: fprintf(stderr, "AST_VAR_DEC "); break;
			case AST_VECTOR_DEC: fprintf(stderr, "AST_VECTOR_DEC "); break;
			case AST_VEC_INT: fprintf(stderr, "AST_VEC_INT "); break;
			case AST_VEC_REAL: fprintf(stderr, "AST_VEC_REAL "); break;
			case AST_VEC_CHAR: fprintf(stderr, "AST_VEC_CHAR "); break;
			case AST_KW_BYTE: fprintf(stderr, "AST_KW_BYTE "); break;
			case AST_KW_SHORT: fprintf(stderr, "AST_KW_SHORT "); break;
			case AST_KW_LONG: fprintf(stderr, "AST_KW_LONG "); break;
			case AST_KW_FLOAT: fprintf(stderr, "AST_KW_FLOAT "); break;
			case AST_KW_DOUBLE: fprintf(stderr, "AST_KW_DOUBLE "); break;
			case AST_KW_READ: fprintf(stderr, "AST_KW_READ "); break;
			case AST_KW_RETURN: fprintf(stderr, "AST_KW_RETURN "); break;
			case AST_KW_PRINT: fprintf(stderr, "AST_KW_PRINT "); break;
			case AST_ARG_PRINT: fprintf(stderr, "AST_ARG_PRINT "); break;
			case AST_FUNC_DEC: fprintf(stderr, "AST_FUNC_DEC "); break;
			case AST_FUNC_ARGL: fprintf(stderr, "AST_FUNC_ARGL "); break;
			case AST_BLOCK: fprintf(stderr, "AST_BLOCK "); break;
			case AST_ATRIB: fprintf(stderr, "AST_ATRIB "); break;
			case AST_VEC_ATRIB: fprintf(stderr, "AST_VEC_ATRIB "); break;
			case AST_CMD_IF: fprintf(stderr, "AST_CMD_IF "); break;
			case AST_CMD_WHILE: fprintf(stderr, "AST_CMD_WHILE "); break;			
			
			default: fprintf(stderr, "UNKNOWN"); break;
		}
		
		if(node->symbol){
			fprintf(stderr, "%s\n", node->symbol->text);
		}else{
			fprintf(stderr, "\n");
		}
		
		for(i=0; i<MAX_SONS; ++i){
			astPrint(node->sons[i],level+1);
		}
		
	}	
}
#endif
