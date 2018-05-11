//


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define PRINT 	0

int assertTrue(int test, int expect);
void printHand(struct gameState* G);
void randomGamestate(struct gameState* G, int* cards, int* gameCards);
void randGamestate(struct gameState* G, int* cards, int* gameCards);
void printGS(struct gameState* G, const char* GS);