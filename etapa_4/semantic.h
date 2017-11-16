#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include <stdbool.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"

int errorFlag;

void semanticSetTypes(AST* node);
void semanticCheckUndeclared(void);
void semanticCheckUsage(AST* node);
void semanticCheckOperands(AST* node);
void semanticCheckVectorIndex(AST* node);
void semanticCheckReturnType(AST* node);
bool isNodeReal(AST *node);
void initErrorFlag(void);
int getErrorFlag(void);
void addErrorFlag(void);

#endif
