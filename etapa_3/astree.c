
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
			case AST_DECLARATION: fprintf(stderr, "AST_DEC "); break;
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
			case AST_FUNPARAML: fprintf(stderr, "AST_FUNPARAML "); break;
			case AST_CMD_LIST: fprintf(stderr, "AST_CMD_LIST "); break;
      case AST_ARRAY_POS: fprintf(stderr, "AST_ARRAY_POS "); break;

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

void astPrintToFile(AST *root, FILE *output_file){
	//FILE *output_file;
	//output_file = fopen(filename, "w");
	int i;

	astPrintNodeToFile(root, output_file);

}

void astPrintNodeToFile(AST *node, FILE *output_file){
	if(node){
		switch(node->type){
			case AST_DECLARATION: astPrintNodeToFile(node->sons[0], output_file);
								astPrintNodeToFile(node->sons[1], output_file);
						break;
			case AST_VAR_DEC: fprintf(output_file, "%s: ", node->symbol->text);
					  astPrintNodeToFile(node->sons[0], output_file);
					  fprintf(output_file, " = ");
					  astPrintNodeToFile(node->sons[1], output_file);
					  fprintf(output_file, ";\n");
					  break;
			case AST_VECTOR_DEC: fprintf(output_file, "%s: ", node->symbol->text);
					  astPrintNodeToFile(node->sons[0], output_file);
					  fprintf(output_file, "[");
					  astPrintNodeToFile(node->sons[1], output_file);
					  fprintf(output_file, "]");
					  if(node->sons[2] != 0){
						fprintf(output_file, " ");
						astPrintNodeToFile(node->sons[2], output_file);
					}
					  fprintf(output_file, ";\n");
					  break;
			case AST_SYMBOL: fprintf(output_file, "%s", node->symbol->text);
					if(node->sons[0] != 0){
						fprintf(output_file, " ");
						astPrintNodeToFile(node->sons[0], output_file);
					}
					break;
			case AST_FUNC_DEC: fprintf(output_file, "\n(");
							astPrintNodeToFile(node->sons[0], output_file);
							fprintf(output_file, ") ");
							fprintf(output_file, "%s(", node->symbol->text);
							astPrintNodeToFile(node->sons[2], output_file);
							fprintf(output_file, ")");
							astPrintNodeToFile(node->sons[3], output_file);
							fprintf(output_file, "\n");
					break;
			case AST_FUNC_ARGL: fprintf(output_file, "%s:", node->sons[0]->symbol->text);
							astPrintNodeToFile(node->sons[0]->sons[0], output_file);
							if(node->sons[1] != 0)
								astPrintNodeToFile(node->sons[1], output_file);
					break;
			case AST_FUNC_ARG: fprintf(output_file, ", %s:", node->sons[0]->symbol->text);
							astPrintNodeToFile(node->sons[0]->sons[0], output_file);
							if(node->sons[1] != 0)
								astPrintNodeToFile(node->sons[1], output_file);
					break;
			case AST_BLOCK:fprintf(output_file, "{\n");
							astPrintNodeToFile(node->sons[0], output_file);
							fprintf(output_file, "\n}");
					break;
			case AST_CMD_LIST: astPrintNodeToFile(node->sons[0], output_file);
							fprintf(output_file, ";\n");
							astPrintNodeToFile(node->sons[1], output_file);
					break;
			case AST_ATRIB: fprintf(output_file, "%s=", node->symbol->text);
						astPrintNodeToFile(node->sons[0], output_file);
					break;
			case AST_VEC_ATRIB: fprintf(output_file, "%s[", node->symbol->text);
						astPrintNodeToFile(node->sons[0], output_file);
						fprintf(output_file, "]= ");
						astPrintNodeToFile(node->sons[1], output_file);
					break;
			case AST_KW_BYTE: fprintf(output_file, "byte"); break;
			case AST_KW_SHORT: fprintf(output_file, "short"); break;
			case AST_KW_LONG: fprintf(output_file, "long"); break;
			case AST_KW_FLOAT: fprintf(output_file, "float"); break;
			case AST_KW_DOUBLE: fprintf(output_file, "double"); break;
			case AST_KW_READ: fprintf(output_file, "read > ");
						fprintf(output_file, "%s", node->symbol->text);
					break;
			case AST_KW_RETURN: fprintf(output_file, "return ");
						astPrintNodeToFile(node->sons[0], output_file);
					break;
			case AST_KW_PRINT: fprintf(output_file, "print ");
						astPrintNodeToFile(node->sons[0], output_file);
					break;
      case AST_FUNPARAML:
			case AST_ARG_PRINT: astPrintNodeToFile(node->sons[0], output_file);
						if(node->sons[1] != 0){
							fprintf(output_file, ", ");
							astPrintNodeToFile(node->sons[1], output_file);
						}
					break;
			case AST_CMD_IF: fprintf(output_file, "if (");
						astPrintNodeToFile(node->sons[0], output_file);
						fprintf(output_file, ") then\n\t");
						astPrintNodeToFile(node->sons[1], output_file);
						fprintf(output_file, "\n");
						if(node->sons[2] != 0){
							fprintf(output_file, "else\n\t");
							astPrintNodeToFile(node->sons[2], output_file);
						}
					break;
			case AST_CMD_WHILE: fprintf(output_file, "while (");
						astPrintNodeToFile(node->sons[0], output_file);
						fprintf(output_file, ")\n\t");
						astPrintNodeToFile(node->sons[1], output_file);
					break;
      case AST_ADD: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " + ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_SUB: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " - ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_MUL: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " * ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_DIV: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " / ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_LESS: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " < ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_GREAT: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " > ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_NEG: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " ! ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_LE: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " <= ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_GE: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " >= ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_EQ: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " == ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_NE: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " != ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_AND: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " && ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_OR: astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " || ");
            astPrintNodeToFile(node->sons[1], output_file);
            break;
      case AST_ARRAY_POS: fprintf(output_file, "%s[", node->symbol->text);
            astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, "]");
            break;
      case AST_FUNC_CALL: fprintf(output_file, "%s(", node->symbol->text);
            astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, ")");
            break;
      case AST_EXP_P: fprintf(output_file, "( ");
            astPrintNodeToFile(node->sons[0], output_file);
            fprintf(output_file, " )");
            break;


			default: fputs("UNKNOWN", output_file); break;
		}
	}
}
#endif
