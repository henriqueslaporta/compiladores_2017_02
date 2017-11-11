#ifndef SEMANTIC_C
#define SEMANTIC_C

#include "semantic.h"

void semanticSetTypes(AST* node){

  if(!node) return;
  //process this node
  if(node->type == AST_VAR_DEC){
    if(node->symbol->type != SYMBOL_IDENTIFIER){
      fprintf(stderr, "semantic error: identifier %s, already declared \n", node->symbol->text);
      exit(4); //ta aqui por enquanto, tirar depois, os outros exit(4) também
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
      exit(4); //ta aqui por enquanto, tirar depois, os outros exit(4) também
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
      exit(4); //ta aqui por enquanto, tirar depois, os outros exit(4) também
    }
    else{
      node->symbol->type = SYMBOL_FUNC;
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
      exit(4); //ta aqui por enquanto, tirar depois, os outros exit(4) também
    }
    else{
      node->sons[0]->symbol->type = SYMBOL_VAR;
      if(node->sons[0]->sons[0]->type == AST_KW_BYTE) node->sons[0]->symbol->datatype = DATATYPE_BYTE;
      if(node->sons[0]->sons[0]->type == AST_KW_SHORT) node->sons[0]->symbol->datatype = DATATYPE_SHORT;
      if(node->sons[0]->sons[0]->type == AST_KW_LONG) node->sons[0]->symbol->datatype = DATATYPE_LONG;
      if(node->sons[0]->sons[0]->type == AST_KW_FLOAT) node->sons[0]->symbol->datatype = DATATYPE_FLOAT;
      if(node->sons[0]->sons[0]->type == AST_KW_DOUBLE) node->sons[0]->symbol->datatype = DATATYPE_DOUBLE;
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
			if(node->type ==  SYMBOL_IDENTIFIER) //ERRO esta aqui ainda não revisei
				fprintf (stderr,"Semantic ERROR: identifier %s, not declared \n",node->text);
}

void semanticCheckUsage(AST* node){
  /*if(!node) return;
  //process this node

  //check left-hand side for scalar
  if(node->type == AST_SYMBOL){
    if(node->symbol->type != SYMBOL_VAR){
      fprintf(stderr, "Semantic ERROR: identifier %s must be scalar left\n", node->symbol->text);
      exit(4);
    }
  }
    //check right-hand side for scalar
    if(node->type == AST_SYMBOL){
      if(node->symbol->type != SYMBOL_VAR && node->symbol->type !=SYMBOL_LIT_INT){
        fprintf(stderr, "Semantic ERROR: identifier %s must be scalar right\n", node->symbol->text);
        exit(4);
      }
    }
    //chack if functions calls are calling functions
    if(node->type == AST_FUNC_CALL){
      if(node->symbol->type != SYMBOL_FUNC){
        fprintf(stderr, "Semantic ERROR: identifier %s must be scalar\n", node->symbol->text);
        exit(4);//trocar por um flag que conta o nro de erros e salvar em que linha da o erro
      }
    }
    int i;
    for(i=0; i<MAX_SONS; i++){
      semanticCheckUsage(node->sons[i]);
    }/**/
}

void semanticCheckOperands(AST* node){
  /*if(!node) return;
  //process this node

  //check operands of arithmetical operators
  if(node->type == AST_ADD || node->type == AST_MUL){
    //check first operands
    if(node->son[0]->type == AST_GREAT){ //adicionar outros operadores logicos, no programa do johann só tinha >
      fprintf(stderr, "Semantic ERROR: left operand of cannot be >\n");
			exit(4);
    }
    //check second operand
    if(node->son[1]->type == AST_GREAT){
      fprintf(stderr, "Semantic ERROR: left operand of cannot be >\n");
			exit(4);
    }
  }
  //check operands of logical operators

  //check assigment (real to real, int to int)

  int i;
  for(i=0; i<MAX_SONS; i++){ //é melhor colocar a recursão no inicio ao invés de aqui
    semanticCheckUsage(node->son[i]);
  }/**/
}
#endif
