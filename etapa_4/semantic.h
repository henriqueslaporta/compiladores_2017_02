#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"


#define MAX_NUM_PARAM 10
#define MAX_NUM_FUNCTIONS 100


typedef struct function_data{
	int numParam;
	int paramType[MAX_NUM_PARAM];
	HASH_NODE *function;
	struct function_data *next;
}FUNC_DATA_NODE;

typedef struct function_list{
	FUNC_DATA_NODE *first;
	FUNC_DATA_NODE *last;
}FUNC_LIST;

FUNC_LIST func_list;


int errorFlag;

void semanticSetTypes(AST* node);
void semanticCheckUndeclared(void);
void semanticCheckUsage(AST* node);
void semanticCheckOperands(AST* node);
void semanticCheckVectorIndex(AST* node);
void semanticCheckReturnType(AST* node);
void semanticCheckFuncParam(AST* node, char* function_name);
bool isNodeReal(AST *node);
void initErrorFlag(void);
int getErrorFlag(void);
void addErrorFlag(void);
void addFunction(HASH_NODE* function);
FUNC_DATA_NODE* findFunction(char* function_name);


#endif
