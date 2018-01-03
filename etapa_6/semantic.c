#ifndef SEMANTIC_C
#define SEMANTIC_C

#include "semantic.h"

void semanticSetTypes(AST* node){

  if(!node) return;
  //process this node
  if(node->type == AST_VAR_DEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "Semantic ERROR Line %d: identifier %s, already declared \n",node->line, node->symbol->text);
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
      fprintf(stderr, "Semantic ERROR Line %d: identifier %s, already declared \n", node->line, node->symbol->text);
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
      fprintf(stderr, "Semantic ERROR Line %d: identifier %s, already declared \n", node->line, node->symbol->text);
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
      fprintf(stderr, "Semantic ERROR Line %d: identifier %s, already declared \n", node->line, node->sons[0]->symbol->text);
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
				fprintf (stderr,"Semantic ERROR Line %d: identifier %s, not declared \n",node->line, node->text);
				addErrorFlag();
			}
}

void semanticCheckUsage(AST* node){
  if(!node) return;
  //process this node

  	//check if variables calls are calling variables
    if(node->type == AST_ATRIB){
      if(node->symbol->type != SYMBOL_VAR){
        fprintf(stderr, "Semantic ERROR Line %d: identifier %s must be a variable\n", node->line, node->symbol->text);
        addErrorFlag();
      }
      //check if the variable and expression are the same type
      if(node->symbol->datatype == DATATYPE_BYTE || node->symbol->datatype == DATATYPE_SHORT || node->symbol->datatype == DATATYPE_LONG)
        if(isNodeInt(node->sons[0]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: variable and expression type do not agree\n", node->line);
          addErrorFlag();
        }
      if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->datatype == DATATYPE_DOUBLE)
        if(isNodeReal(node->sons[0]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: variable and expression type do not agree\n", node->line);
          addErrorFlag();
        }
    }

    //check if vectors calls are calling vectors
    if(node->type == AST_VEC_ATRIB){
      if(node->symbol->type != SYMBOL_VEC){
        fprintf(stderr, "Semantic ERROR Line %d: identifier %s must be a vector\n",node->line, node->symbol->text);
        addErrorFlag();
      }
      //check if the vector and expression are the same type
      if(node->symbol->datatype == DATATYPE_BYTE || node->symbol->datatype == DATATYPE_SHORT || node->symbol->datatype == DATATYPE_LONG)
        if(isNodeInt(node->sons[0]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: vector and expression type do not agree\n", node->line);
          addErrorFlag();
        }
      if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->datatype == DATATYPE_DOUBLE)
        if(isNodeReal(node->sons[0]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: vector and expression type do not agree\n", node->line);
          addErrorFlag();
        }
    }

    //check if vectors calls are calling vectors and if it's index is valid
    if(node->type == AST_ARRAY_POS){
      if(node->symbol->type != SYMBOL_VEC){
        fprintf(stderr, "Semantic ERROR Line %d: identifier %s must be a vector\n",  node->line, node->symbol->text);
        addErrorFlag();
      }
      else semanticCheckVectorIndex(node);
    }

    //check if functions calls are calling functions and if it's arguments are valid
    if(node->type == AST_FUNC_CALL){
      if(node->symbol->type != SYMBOL_FUNC){
        fprintf(stderr, "Semantic ERROR Line %d: identifier %s must be a function\n",  node->line, node->symbol->text);
        addErrorFlag();
      }
      else semanticCheckFuncParam(node->sons[0], node->symbol->text, node->line);
    }

    //check if variables declarations and literal are the same type
    if(node->type == AST_VAR_DEC){
      if(node->symbol->datatype == DATATYPE_BYTE || node->symbol->datatype == DATATYPE_SHORT || node->symbol->datatype == DATATYPE_LONG)
        if(isNodeInt(node->sons[1]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: variable and literal type do not agree\n", node->line);
          addErrorFlag();
        }
      if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->datatype == DATATYPE_DOUBLE)
        if(isNodeReal(node->sons[1]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: variable and literal type do not agree\n", node->line);
          addErrorFlag();
        }
    }

    //check if vectors declarations and literals are the same type
    if(node->type == AST_VECTOR_DEC){
      AST* current_node;
      current_node = node->sons[2];
      int pos = 0;

      while(current_node != NULL){
        if(node->symbol->datatype == DATATYPE_BYTE || node->symbol->datatype == DATATYPE_SHORT || node->symbol->datatype == DATATYPE_LONG)
          if(isNodeInt(current_node) == false){
            fprintf(stderr, "Semantic ERROR Line %d: vector and literal_%d type do not agree\n", node->line, pos+1);
            addErrorFlag();
          }
        if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->datatype == DATATYPE_DOUBLE)
          if(isNodeReal(current_node) == false){
            fprintf(stderr, "Semantic ERROR Line %d: vector and literal_%d type do not agree\n", node->line, pos+1);
            addErrorFlag();
          }
          current_node = current_node->sons[0];
          pos++;
      }
    }

    /*if(node->type == AST_KW_PRINT){
        AST* current_node;
        current_node = node->sons[0];
        int arg_total = 0, arg_count = 0;

        while(current_node != NULL && current_node->type == AST_ARG_PRINT){
          if(current_node->sons[0] != NULL){
            if(current_node->sons[0]->symbol->type == SYMBOL_LIT_STRING){
              //number of int arguments
              arg_total = arg_total + str_in_str_count("%d", current_node->sons[0]->symbol->text);
            }
            else arg_count++;

            current_node = current_node->sons[1];
          }
        }

        if(arg_total != arg_count){
          fprintf(stderr, "Semantic ERROR Line %d: invalid number of print arguments\n", node->line);
          addErrorFlag();
        }
    }/**/

    int i;
    for(i=0; i<MAX_SONS; i++){
      semanticCheckUsage(node->sons[i]);
    }/**/
}

void semanticCheckOperands(AST* node){
  if(!node) return;
  //process this node

  //check operands of arithmetical and logical operators
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV ||
  node->type == AST_LESS || node->type == AST_GREAT || node->type == AST_NEG || node->type == AST_LE ||
  node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR){

    AST *opLeft = node->sons[0];
    AST *opRight = node->sons[1];

    int opLeftType = opLeft->type;
  	int opRightType = opRight->type;
    //in case sons are an expression between parentesis
    while(opLeftType == AST_EXP_P){
      opLeft = opLeft->sons[0];
      opLeftType = opLeft->type;
    }
    while(opRightType == AST_EXP_P){
      opRight = opRight->sons[0];
      opRightType = opRight->type;
    }

  	//check first operands
    if(opLeftType == AST_LESS || opLeftType == AST_GREAT || opLeftType == AST_NEG || opLeftType == AST_LE || opLeftType == AST_GE || opLeftType == AST_EQ || opLeftType == AST_NE || opLeftType == AST_AND || opLeftType == AST_OR){
		fprintf(stderr, "Semantic ERROR Line %d: the left operand cannot be  logical (<, >, !, <=, >=, ==, !=, &&, ||)\n", node->line);
		addErrorFlag();
    }
    //check second operand
    if(opRightType == AST_LESS || opRightType == AST_GREAT || opRightType == AST_NEG || opRightType == AST_LE || opRightType == AST_GE || opRightType == AST_EQ || opRightType == AST_NE || opRightType == AST_AND || opRightType == AST_OR){
		fprintf(stderr, "Semantic ERROR Line %d: the right operand cannot be logical (<, >, !, <=, >=, ==, !=, &&, ||)\n", node->line);
		addErrorFlag();
    }
  }

  //check if operands of conditions are boolean
  if(node->type == AST_CMD_IF || node->type == AST_CMD_WHILE){
      AST *sons0 = node->sons[0];
      int sons0type = sons0->type;
      //in case son is an expression between parentesis
      while(sons0type == AST_EXP_P){
        sons0 = sons0->sons[0];
        sons0type = sons0->type;
      }

      if(sons0type != AST_LESS && sons0type != AST_GREAT && sons0type != AST_NEG && sons0type != AST_LE && sons0type != AST_GE && sons0type != AST_EQ && sons0type != AST_NE && sons0type != AST_AND && sons0type != AST_OR){
        fprintf(stderr, "Semantic ERROR Line %d: condition must return a boolean value\n", node->line);
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
    fprintf(stderr, "Semantic ERROR Line %d: the vector index must be an integer value\n", node->line);
    addErrorFlag();
  }
  /**/
}

void semanticCheckReturnType(AST* node){
  if(!node) return;

  /*if(node->type == AST_FUNC_DEC){
    semanticCheckReturnType(node->sons[3]);
    return;
  }*/
  if(node->type == AST_KW_RETURN){
    //check the type of the expression that is being returned
    //in this case, the defined types are interchangeable
    if(isNodeReal(node->sons[0]) == false && isNodeInt(node->sons[0]) == false){
      fprintf(stderr, "Semantic ERROR Line %d: invalid return type\n", node->line);
  		addErrorFlag();
      return;
    }
  }

	int i;
  for(i=0; i<MAX_SONS; i++){
    semanticCheckReturnType(node->sons[i]);
  }/**/
}

void semanticCheckFuncParam(AST* node, char* function_name, int line){
	AST* current_node;
	current_node = node;
	int param_count = 0;

	FUNC_DATA_NODE* func_data;
	func_data = findFunction(function_name);
  if(func_data == NULL) return;

	int numParam = func_data->numParam;

	while(current_node!=NULL && param_count<=numParam){
      //check the parameter's type
      //if it is real
      if(func_data->paramType[param_count] == DATATYPE_FLOAT || func_data->paramType[param_count] == DATATYPE_DOUBLE)
  			if(isNodeReal(current_node->sons[0]) == false){
  				fprintf(stderr, "Semantic ERROR Line %d: invalid function parameter type (parameter %i)\n",line, param_count + 1);
    			addErrorFlag();
  			}
      //or if it is integer
      if(func_data->paramType[param_count] == DATATYPE_BYTE || func_data->paramType[param_count] == DATATYPE_SHORT || func_data->paramType[param_count] == DATATYPE_LONG)
        if(isNodeInt(current_node->sons[0]) == false){
          fprintf(stderr, "Semantic ERROR Line %d: invalid function parameter type (parameter %i)\n",line, param_count + 1);
          addErrorFlag();
        }
			param_count++;
			current_node = current_node->sons[1];
	}
	if(param_count > numParam){
		fprintf(stderr, "Semantic ERROR Line %d: too many arguments at %s\n", line, function_name);
  		addErrorFlag();
	}
	if(param_count < numParam){
		fprintf(stderr, "Semantic ERROR Line %d: missing arguments at %s\n", line, function_name);
  		addErrorFlag();
	}/**/
}

bool isNodeReal(AST *node){
  if(!node) return false;

  //literas, variables, access to array and function can be float or integer
  if(node->type == AST_SYMBOL || node->type == AST_ARRAY_POS || node->type == AST_FUNC_CALL)
    if(node->symbol->datatype == DATATYPE_FLOAT || node->symbol->datatype == DATATYPE_DOUBLE || node->symbol->type == SYMBOL_LIT_REAL)
      return true;
    else
      return false;
  //logical operations do not return real values
  if(node->type == AST_LESS || node->type == AST_GREAT || node->type == AST_NEG || node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_NE || node->type == AST_AND || node->type == AST_OR)
    return false;
  //arithmetical operations must be checked
  if(node->type == AST_ADD || node->type == AST_SUB || node->type == AST_MUL || node->type == AST_DIV)
    return isNodeReal(node->sons[0]) || isNodeReal(node->sons[1]);
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

//counts the number of a substring in a string
int str_in_str_count(char* substr, char* str){

  int substr_len = strlen(substr);
  int count = 0;

  char *tmp = str;

  if (substr_len)
      while ((tmp = strstr(tmp, substr))){
          tmp += substr_len;
          count++;
        }

  return count;
}



#endif
