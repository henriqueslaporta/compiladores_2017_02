#ifndef SEMANTIC_C
#define SEMANTIC_C

#include "semantic.h"

void semanticSetTypes(AST* node){

  if(!node) return;
  //process this node
  if(node->type == AST_VAR_DEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "semantic error: identifier %s, already declared \n", node->symbol->text);
      addErrorFlag();
    }
    else{
      node->symbol->type = SYMBOL_VAR;
      if(node->sons[0]->type == AST_KW_BYTE) node->symbol->datatype = DATATYPE_BYTE;
      if(node->sons[0]->type == AST_KW_SHORT) node->symbol->datatype = DATATYPE_SHORT;
      if(node->sons[0]->type == AST_KW_LONG) node->symbol->datatype = DATATYPE_LONG;
      if(node->sons[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      if(node->sons[0]->type == AST_KW_DOUBLE) node->symbol->datatype = DATATYPE_DOUBLE;
    }
  }
  if(node->type == AST_VECTOR_DEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "semantic error: identifier %s, already declared \n", node->symbol->text);
      addErrorFlag();
    }
    else{
      node->symbol->type = SYMBOL_VEC;
      if(node->sons[0]->type == AST_KW_BYTE) node->symbol->datatype = DATATYPE_BYTE;
      if(node->sons[0]->type == AST_KW_SHORT) node->symbol->datatype = DATATYPE_SHORT;
      if(node->sons[0]->type == AST_KW_LONG) node->symbol->datatype = DATATYPE_LONG;
      if(node->sons[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      if(node->sons[0]->type == AST_KW_DOUBLE) node->symbol->datatype = DATATYPE_DOUBLE;
    }
  }
  if(node->type == AST_FUNC_DEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "Semantic ERROR: identifier %s, already declared \n", node->symbol->text);
      addErrorFlag();
    }
    else{
      node->symbol->type = SYMBOL_FUNC;
	    addFunction(node->symbol);
      if(node->sons[0]->type == AST_KW_BYTE) node->symbol->datatype = DATATYPE_BYTE;
      if(node->sons[0]->type == AST_KW_SHORT) node->symbol->datatype = DATATYPE_SHORT;
      if(node->sons[0]->type == AST_KW_LONG) node->symbol->datatype = DATATYPE_LONG;
      if(node->sons[0]->type == AST_KW_FLOAT) node->symbol->datatype = DATATYPE_FLOAT;
      if(node->sons[0]->type == AST_KW_DOUBLE) node->symbol->datatype = DATATYPE_DOUBLE;
    }
  }
  //Para declaração dos argumentos das funções como variaveis válidas
  if(node->type == AST_FUNC_ARGL || node->type == AST_FUNC_ARG){
    if(node->sons[0]->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "Semantic ERROR: identifier %s, already declared \n", node->sons[0]->symbol->text);
      addErrorFlag();
    }
    else{
      node->sons[0]->symbol->type = SYMBOL_VAR;
      if(node->sons[0]->sons[0]->type == AST_KW_BYTE) node->sons[0]->symbol->datatype = DATATYPE_BYTE;
      if(node->sons[0]->sons[0]->type == AST_KW_SHORT) node->sons[0]->symbol->datatype = DATATYPE_SHORT;
      if(node->sons[0]->sons[0]->type == AST_KW_LONG) node->sons[0]->symbol->datatype = DATATYPE_LONG;
      if(node->sons[0]->sons[0]->type == AST_KW_FLOAT) node->sons[0]->symbol->datatype = DATATYPE_FLOAT;
      if(node->sons[0]->sons[0]->type == AST_KW_DOUBLE) node->sons[0]->symbol->datatype = DATATYPE_DOUBLE;
	    func_list.last->numParam ++;
	    func_list.last->paramType[func_list.last->numParam - 1] = node->sons[0]->symbol->datatype;
    }
  }


  int i;
  for(i=0; i<MAX_SONS; i++){
    semanticSetTypes(node->sons[i]);
  }
}

void semanticCheckUndeclared(void){
  	int i;
	HASH_NODE *node;
	for(i=0; i<HASH_SIZE; i++)
		for(node=table[i]; node; node=node->next)
			if(node->type ==  SYMBOL_IDENTIFIER){
				fprintf (stderr,"Semantic ERROR: identifier %s, not declared \n",node->text);
				addErrorFlag();
			}
}

void semanticCheckUsage(AST* node){
  if(!node) return;
  //process this node

  	//check if variables calls are calling variables
    if(node->type == AST_ATRIB){
      if(node->symbol->type != SYMBOL_VAR){
        fprintf(stderr, "Semantic ERROR: identifier %s must be a variable\n", node->symbol->text);
        addErrorFlag();
      }
    }

    //check if vectors calls are calling vectors
    if(node->type == AST_VEC_ATRIB){
      if(node->symbol->type != SYMBOL_VEC){
        fprintf(stderr, "Semantic ERROR: identifier %s must be a vector\n", node->symbol->text);
        addErrorFlag();
      }
    }

    //check if vectors calls are calling vectors and if it's index is valid
    if(node->type == AST_ARRAY_POS){
      if(node->symbol->type != SYMBOL_VEC){
        fprintf(stderr, "Semantic ERROR: identifier %s must be a vector\n", node->symbol->text);
        addErrorFlag();
      }
      else semanticCheckVectorIndex(node);
    }

    //check if functions calls are calling functions and if it's arguments are valid
    if(node->type == AST_FUNC_CALL){
      if(node->symbol->type != SYMBOL_FUNC){
        fprintf(stderr, "Semantic ERROR: identifier %s must be a function\n", node->symbol->text);
        addErrorFlag();
      }
      else semanticCheckFuncParam(node->sons[0], node->symbol->text);
    }

    int i;
    for(i=0; i<MAX_SONS; i++){
      semanticCheckUsage(node->sons[i]);
    }/**/
}

void semanticCheckOperands(AST* node){ //OPERANDOS DE OPERADORES LÓGICOS PODEM SER ARITIMETICOS
  if(!node) return;
  //process this node

  //check operands of arithmetical operators
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV){
  	int sons0 = node->sons[0]->type;
  	int sons1 = node->sons[1]->type;

  	//check first operands
    if(sons0 == AST_LESS || sons0 == AST_GREAT || sons0 == AST_NEG || sons0 == AST_LE || sons0 == AST_GE || sons0 == AST_EQ || sons0 == AST_NE || sons0 == AST_AND || sons0 == AST_OR){
		fprintf(stderr, "Semantic ERROR: the left operand cannot be  logical (<, >, !, <=, >=, ==, !=, &&, ||)\n");
		addErrorFlag();
    }
    //check second operand
    if(sons1 == AST_LESS || sons1 == AST_GREAT || sons1 == AST_NEG || sons1 == AST_LE || sons1 == AST_GE || sons1 == AST_EQ || sons1 == AST_NE || sons1 == AST_AND || sons1 == AST_OR){
		fprintf(stderr, "Semantic ERROR: the right operand cannot be logical (<, >, !, <=, >=, ==, !=, &&, ||)\n");
		addErrorFlag();
    }
  }
  //check operands of logical operators
  if(node->type == AST_LESS || node->type == AST_GREAT || node->type == AST_NEG || node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR){
  	int sons0 = node->sons[0]->type;
  	int sons1 = node->sons[1]->type;

  	//check first operands
    if(sons0 == AST_ADD || sons0 == AST_SUB || sons0 == AST_MUL || sons0 == AST_DIV){
		fprintf(stderr, "Semantic ERROR: the left operand cannot be arithmetical (+, -, *, /)\n");
		addErrorFlag();
    }
    //check second operand
    if(sons1 == AST_ADD || sons1 == AST_SUB || sons1 == AST_MUL || sons1 == AST_DIV){
		fprintf(stderr, "Semantic ERROR: the right operand cannot be arithmetical (+, -, *, /)\n");
		addErrorFlag();
    }
  }

  int i;
  for(i=0; i<MAX_SONS; i++){
    semanticCheckOperands(node->sons[i]);
  }/**/
}

void semanticCheckVectorIndex(AST* node){

  if(isNodeInt(node->sons[0]) == false){
    fprintf(stderr, "Semantic ERROR: the vector index must be an integer value\n");
    addErrorFlag();
  }
  /**/
}

void semanticCheckReturnType(AST* node){
  if(!node) return;

  if(node->type == AST_FUNC_DEC){
    semanticCheckReturnType(node->sons[3]);
    return;
  }
  if(node->type == AST_KW_RETURN){
    //check the type of the expression that is being returned
    //in our case, the defined types are interchangeable
    if(isNodeReal(node->sons[0]) == false){
      fprintf(stderr, "Semantic ERROR: invalid return type\n");
  		addErrorFlag();
      return;
    }
  }

  for(int i=0; i<MAX_SONS; i++){
    semanticCheckReturnType(node->sons[i]);
  }/**/
}

void semanticCheckFuncParam(AST* node, char* function_name){
	AST* current_node;
	current_node = node;
	int param_count = 0;

	FUNC_DATA_NODE* func_data;
	func_data = findFunction(function_name);
  if(func_data == NULL) return;

	int numParam = func_data->numParam;

	while(current_node!=NULL && param_count<=numParam){
      //check the parameter's type
      //in our case, the defined types are interchangeable
			if(isNodeReal(current_node->sons[0]) == false){
				fprintf(stderr, "Semantic ERROR: invalid function parameter type (parameter %i)\n", param_count + 1);
  			addErrorFlag();
			}
			param_count++;
			current_node = current_node->sons[1];
	}
	if(param_count > numParam){
		fprintf(stderr, "Semantic ERROR: too many arguments at %s\n", function_name);
  		addErrorFlag();
	}
	if(param_count < numParam){
		fprintf(stderr, "Semantic ERROR: missing arguments at %s\n", function_name);
  		addErrorFlag();
	}/**/
}

bool isNodeReal(AST *node){
  if(!node) return false;

  //literals, variables, access to array and function calls are all real values
  if(node->type == AST_SYMBOL || node->type == AST_ARRAY_POS || node->type == AST_FUNC_CALL)
    return true;
  //logical operations do not return real values
  if(node->type == AST_LESS || node->type == AST_GREAT || node->type == AST_NEG || node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR)
    return false;
  //arithmetical operations must be checked
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV)
    return isNodeReal(node->sons[0]) && isNodeReal(node->sons[1]);
  //expressions between parentesis must be checked
  if(node->type == AST_EXP_P)
    isNodeReal(node->sons[0]);
}

bool isNodeInt(AST *node){
  if(!node) return false;

  //literas, variables, access to array and function can be float or integer
  if(node->type == AST_SYMBOL || node->type == AST_ARRAY_POS || node->type == AST_FUNC_CALL)
    if(node->symbol->datatype == DATATYPE_BYTE || node->symbol->datatype == DATATYPE_SHORT || node->symbol->datatype == DATATYPE_LONG || node->symbol->type == SYMBOL_LIT_INT || node->symbol->type == SYMBOL_LIT_CHAR)
      return true;
    else
      return false;
  //logical operations do not return integer values
  if(node->type == AST_LESS || node->type == AST_GREAT || node->type == AST_NEG || node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR)
    return false;
  //arithmetical operations must be checked
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV)
    return isNodeInt(node->sons[0]) && isNodeInt(node->sons[1]);
  //expressions between parentesis must be checked
  if(node->type == AST_EXP_P)
    isNodeInt(node->sons[0]);
}

void initErrorFlag(void){
	errorFlag = 0;
}

int getErrorFlag(void){
	return errorFlag;
}

void addErrorFlag(void){
	errorFlag++;
}

void addFunction(HASH_NODE* function){
	FUNC_DATA_NODE* newNode;
	newNode = (FUNC_DATA_NODE*) calloc(1, sizeof(FUNC_DATA_NODE));
	newNode->function = function;
	newNode->numParam = 0;
	newNode->next = NULL;

	if(func_list.first == NULL){
		func_list.first = newNode;
		func_list.last = newNode;
	}
	else{
		func_list.last->next = newNode;
		func_list.last = newNode;
	}
}

FUNC_DATA_NODE* findFunction(char* function_name){
	FUNC_DATA_NODE* current_func = func_list.first;
  bool found = false;

	while(current_func != NULL && found == false){
		if(strcmp(current_func->function->text, function_name) == 0)
			found = true;
		else
			current_func = current_func->next;
	}
  return current_func;
}


#endif
