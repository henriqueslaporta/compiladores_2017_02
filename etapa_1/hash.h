#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LST_INT 2
#define HASH_SIZE 997

typedef struct hash_node
{
	char *text;
	int type;
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

