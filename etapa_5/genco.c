#include "genco.h"
#include <stdio.h>
#include <stdlib.h>

TAC* makeIfThen(TAC* code0, TAC* code1);


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

	if(!node) return 0;

	//first generate children
	for(int i = 0; i < MAX_SONS; i++)
		code[i] = tacGenerator(node->sons[i]);

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
	for(tac = last; tac; tac = tac->prev)
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
