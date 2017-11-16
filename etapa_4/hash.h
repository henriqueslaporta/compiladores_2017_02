#ifndef HASH_HEADER
#define HASH_HEADER


#define SYMBOL_LITINT 1   //isso ta aqui pq o do johann ta assim
#define SYMBOL_ID 2				//acho que tem que tirar isso pq vai ser usado os definidos no parser.y

#define SYMBOL_VAR 3
#define SYMBOL_VEC 4
#define SYMBOL_FUNC 5

#define DATATYPE_BYTE 1
#define DATATYPE_SHORT 2
#define DATATYPE_LONG 3
#define DATATYPE_FLOAT 4
#define DATATYPE_DOUBLE 5

#define SYMBOL_LST_INT 2
#define HASH_SIZE 997

typedef struct hash_node
{
	char *text;
	int type;
	int datatype;
	struct hash_node *next;
} HASH_NODE;

HASH_NODE *table[HASH_SIZE];


void hashInit();
void hashPrint();
int hashAddress(char *text);
HASH_NODE *hashInsert (char *text, int type);
HASH_NODE *hashFind (char *text);

void initMe();
int getLineNumber();
int isRunning();


#endif
