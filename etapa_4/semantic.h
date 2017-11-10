#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include <stdio.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"

void semanticSetTypes(AST* node);
void semanticCheckUndeclared(void);
void semanticCheckUsage(AST* node);
void semanticCheckOperands(AST* node);

#endif
