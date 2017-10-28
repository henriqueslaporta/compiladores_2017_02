#ifndef HASH_C
#define HASH_C

#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashInit()
{
	int i;
	for (i=0; i< HASH_SIZE; i++)
	{
	    table[i] = 0;
	}
}


void hashPrint()
{
	int i;
	HASH_NODE *n;
	for (i=0; i< HASH_SIZE; i++)
	{
	   for (n=table[i]; n; n=n->next)
	   {
	       printf ("Table[%d] has %s \t\tlen: %lu\n",i,n->text, strlen(n->text));
	   }
	}
}

int hashAddress(char *text)
{
	int address = 1;
	int i;
	for (i=0; i<strlen(text); i++)
	{
	   address = (address *text[i]) % HASH_SIZE + 1;
	}
	return address-1;
}


HASH_NODE *hashInsert (char *text, int type)
{
	HASH_NODE *newnode;
	int address = hashAddress(text);
	if ((newnode = hashFind(text)) != 0){
	   return newnode;
	}
	newnode = (HASH_NODE *) calloc (1, sizeof(HASH_NODE));
	newnode->text = (char *) calloc (strlen(text)+1, sizeof(char));
	strcpy(newnode->text, text);
        
	newnode->type = type;
	newnode->next = table[address];
	table[address] = newnode;
	return newnode;
}

HASH_NODE *hashFind (char *text)
{
	int address;
	HASH_NODE *node;
	address = hashAddress(text);
	for (node=table[address]; node; node=node->next){
		if ((strcmp (node->text,text)) == 0){
	 		return node;
	 	}
	}
	return 0;
}

#endif
