#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "genco.h"
#include "y.tab.h"

#define NUMBER_OF_STRINGS 30
#define STRING_LENGTH 200

char strings[NUMBER_OF_STRINGS][STRING_LENGTH+1];

int findString(char *stringName);

void asmGenerator(char *filename, TAC* code);
