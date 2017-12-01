#include "genco.h"
#include <stdio.h>
#include <stdlib.h>

TAC* makeIfThen(TAC* code0, TAC* code1);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeFun(HASH_NODE* funSymbol, TAC* code3);
void updateFuncArgs(TAC* func, HASH_NODE* symbol);


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2){
	TAC* newtac;
	newtac = (TAC*)calloc(1,sizeof(TAC));
	newtac->type = type;
	newtac->res = res;
	newtac->op1 = op1;
	newtac->op2 = op2;
	newtac->prev = 0;
	newtac->next = 0;

	return newtac;
}

TAC* tacGenerator(AST* node){
	TAC* code[MAX_SONS];
	TAC* aux_tac;

	if(!node) return 0;

	//first generate children
	int i;
	for(i = 0; i < MAX_SONS; i++)
		code[i] = tacGenerator(node->sons[i]);

	//process this node
	switch(node->type){
		case AST_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case AST_ADD: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_ADD, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_MUL: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_MUL, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_SUB: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_SUB, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_DIV: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_DIV, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_LESS: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_LESS, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_GREAT: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_GREAT, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_NEG: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_NEG, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_LE: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_LE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_GE: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_GE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_EQ: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_EQ, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_NE: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_NE, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_OR: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_OR, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_AND: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_AND, makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)); break;
		case AST_ATRIB: return tacJoin(code[0], tacCreate(TAC_ASS, node->symbol, code[0]?code[0]->res:0, 0)); break;
		//vecwrite: load vector, value, offset
		case AST_VEC_ATRIB: return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_VECWRITE, node->symbol, code[1]?code[1]->res:0, code[0]?code[0]->res:0)); break;
		//vecread: store variable, vector, offset
		case AST_ARRAY_POS: return tacJoin(code[0], tacCreate(TAC_VECREAD, makeTemp(), node->symbol, code[0]?code[0]->res:0)); break;
		case AST_KW_READ: return tacCreate(TAC_INPUT, node->symbol, 0, 0); break;
		case AST_ARG_PRINT: return tacJoin(tacCreate(TAC_OUTPUT, code[0]?code[0]->res:0, 0, 0), code[1]); break;
		case AST_KW_RETURN: return tacJoin(code[0], tacCreate(TAC_RETURN, code[0]?code[0]->res:0, 0, 0)); break;
		case AST_CMD_IF: return makeIfThen(code[0], code[1]); break;
		case AST_CMD_WHILE: return makeWhile(code[0], code[1]); break;
		case AST_FUNC_DEC: return makeFun(node->symbol, code[3]); break;
		//inserts the name of the function to its arguments here
		case AST_FUNC_CALL: aux_tac = tacJoin(code[0], tacCreate(TAC_CALL, node->symbol, 0, 0)); updateFuncArgs(aux_tac, node->symbol); return aux_tac; break;
		//at first creates TAC_ARG without its owner function
		case AST_FUNPARAML: return tacJoin(tacJoin(code[0], tacCreate(TAC_ARG, 0, code[0]?code[0]->res:0, 0)), code[1]); break;
	}

	return tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
}

TAC* tacJoin(TAC* l1, TAC* l2){
	TAC* tac = l2;
	if(!l1) return l2;
	if(!l2) return l1;
	while(tac->prev)
		tac = tac->prev;

	tac->prev = l1;
	return l2;
}

void tacPrintSingle(TAC* tac){
	if(!tac) return;
	if(tac->type == TAC_SYMBOL) return;

	fprintf(stderr, "TAC(");
	switch(tac->type){
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL "); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD "); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB "); break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL "); break;
		case TAC_DIV: fprintf(stderr, "TAC_DIV "); break;
		case TAC_LESS: fprintf(stderr, "TAC_LESS "); break;
		case TAC_GREAT: fprintf(stderr, "TAC_GREAT "); break;
		case TAC_NEG: fprintf(stderr, "TAC_NEG "); break;
		case TAC_LE: fprintf(stderr, "TAC_LE "); break;
		case TAC_GE: fprintf(stderr, "TAC_GE "); break;
		case TAC_EQ: fprintf(stderr, "TAC_EQ "); break;
		case TAC_NE: fprintf(stderr, "TAC_NE "); break;
		case TAC_OR: fprintf(stderr, "TAC_OR "); break;
		case TAC_AND: fprintf(stderr, "TAC_AND "); break;
		case TAC_ASS: fprintf(stderr, "TAC_ASS "); break;
		case TAC_VECWRITE: fprintf(stderr, "TAC_VECWRITE "); break;
		case TAC_VECREAD: fprintf(stderr, "TAC_VECREAD "); break;
		case TAC_INPUT: fprintf(stderr, "TAC_INPUT "); break;
		case TAC_OUTPUT: fprintf(stderr, "TAC_OUTPUT "); break;
		case TAC_RETURN: fprintf(stderr, "TAC_RETURN "); break;
		case TAC_JZ: fprintf(stderr, "TAC_JZ "); break;
		case TAC_JMP: fprintf(stderr, "TAC_JMP "); break;
		case TAC_LABEL: fprintf(stderr, "TAC_LABEL "); break;
		case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN "); break;
		case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN "); break;
		case TAC_CALL: fprintf(stderr, "TAC_CALL "); break;
		case TAC_ARG: fprintf(stderr, "TAC_ARG "); break;
		default: fprintf(stderr, "UNKNOWN "); break;
	}

	if(tac->res) fprintf(stderr, "%s ", tac->res->text); else fprintf(stderr, ",null");
	if(tac->op1) fprintf(stderr, "%s ", tac->op1->text); else fprintf(stderr, ",null");
	if(tac->op2) fprintf(stderr, "%s ", tac->op2->text); else fprintf(stderr, ",null");
	fprintf(stderr, "\n");
}

void tacPrintBack(TAC* last){
	TAC* tac;
	for(tac = last; tac != NULL; tac = tac->prev)
		tacPrintSingle(tac);
}

TAC* tacInvertList(TAC* last){
	TAC* aux_tac, *curr_tac;

	if(!last) return last;

	aux_tac = last;
	for(curr_tac = last->prev; curr_tac; curr_tac = curr_tac->prev){
		curr_tac->next = aux_tac;
		aux_tac = aux_tac->prev;
	}

	return aux_tac;
}

void tacPrintForward(TAC* first){
	TAC* tac;
	for(tac = first; tac != NULL; tac = tac->next)
			tacPrintSingle(tac);

}

TAC* makeIfThen(TAC* code0, TAC* code1){
	TAC* newJumpTac = 0;
	TAC* newLabelTac = 0;

	HASH_NODE* newLabel;

	newLabel = makeLabel();

	newJumpTac = tacCreate(TAC_JZ, newLabel, code0?code0->res:0, 0);
	newLabelTac = tacCreate(TAC_LABEL, newLabel, 0, 0);

	return tacJoin(tacJoin(tacJoin(code0, newJumpTac), code1), newLabelTac);
}

TAC* makeWhile(TAC* code0, TAC* code1){
	TAC* preConditionLabelTac = 0;
	TAC* postBlockLabelTac = 0;
	TAC* JmpTac = 0;
	TAC* JzTac = 0;


	HASH_NODE* newPreConditionLabel;
	HASH_NODE* newPostBlockLabel;

	newPreConditionLabel = makeLabel();
	newPostBlockLabel = makeLabel();

	preConditionLabelTac = tacCreate(TAC_LABEL, newPreConditionLabel, 0, 0);
	postBlockLabelTac = tacCreate(TAC_LABEL, newPostBlockLabel, 0, 0);
	JmpTac = tacCreate(TAC_JMP, newPreConditionLabel, 0, 0);
	JzTac = tacCreate(TAC_JZ, newPostBlockLabel, code0?code0->res:0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(preConditionLabelTac, code0), JzTac), code1), JmpTac), postBlockLabelTac);
}

TAC* makeFun(HASH_NODE* funSymbol, TAC* code3){
	TAC* beginFunTac = 0;
	TAC* endFunTac = 0;

	beginFunTac = tacCreate(TAC_BEGINFUN, funSymbol, 0, 0);
	endFunTac = tacCreate(TAC_ENDFUN, funSymbol, 0, 0);

	return tacJoin(tacJoin(beginFunTac, code3), endFunTac);
}

//update the TAC_ARGs with its owner's name 
void updateFuncArgs(TAC* func, HASH_NODE* symbol){
	TAC* curr_arg;
	curr_arg = func;

	if(!curr_arg) return;

	while(curr_arg->prev != NULL){
		curr_arg = curr_arg->prev;

		if(curr_arg->type == TAC_ARG)
			curr_arg->res = symbol;
	}
}
