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
		case AST_ATRIB: return tacJoin(code[0], tacCreate(TAC_ASS, node->symbol, code[0]?code[0]->res:0,0)); break;
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
	//if(tac->type == TAC_SYMBOL) return;

	fprintf(stderr, "TAC(");
	switch(tac->type){
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
		default: fprintf(stderr, "UNKNOWN"); break;		
	}

	if(tac->res) fprintf(stderr, "%s", tac->res->text); else fprintf(stderr, ",null");
	if(tac->op1) fprintf(stderr, "%s", tac->op1->text); else fprintf(stderr, ",null");
	if(tac->op2) fprintf(stderr, "%s", tac->op2->text); else fprintf(stderr, ",null");
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







