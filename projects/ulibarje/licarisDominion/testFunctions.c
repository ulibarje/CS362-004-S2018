//Name

#include "testFunctions.h"


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
		if(PRINT)
			printf("PASSED\n");
		return 0;
	}
	else {
		if(PRINT) {
			printf("FAILED ---> ");
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 1;
	}
}


/*************************************************************************
* Name: printHand
*
* Description: 
*
*************************************************************************/
void printHand(struct gameState* G) {
	int i;
	for(i = 0; i < G->handCount[G->whoseTurn]; i++) {
		printf("Card %d: %d\n", i, G->hand[G->whoseTurn][i]);
	}
}


/*************************************************************************
* Name: randomGamestate
*
* Description: This function generates a random gamestate with 2 to
*	MAX_PLAYERS players, 0 to 15 cards in the deck and discard piles,
*	and 4 to 8 cards in the hand.
*
*************************************************************************/
void randomGamestate(struct gameState* G, int* cards, int* gameCards) {
	int p, d, h, dc;
	int numPlayers;

	do {
		numPlayers = (int)floor(Random() * MAX_PLAYERS);
	} while(numPlayers < 2);

	initializeGame(numPlayers, gameCards, 123, G);

	for(p = 0; p < numPlayers; p++) {
		G->deckCount[p] = (int)floor(Random() * 15);
		G->handCount[p] = (int)floor((Random() * 4) + 4);
		G->discardCount[p] = (int)floor(Random() * 15);

		for(d = 0; d < G->deckCount[p]; d++) {
			G->deck[p][d] = cards[(int)floor(Random() * 17)];
		}

		for(h = 0; h < G->handCount[p]; h++) {
			G->hand[p][h] = cards[(int)floor(Random() * 17)];
		}

		for(dc = 0; dc < G->discardCount[p]; dc++) {
			G->discard[p][dc] = cards[(int)floor(Random() * 17)];
		}

		updateCoins(p, G, 0);
	}
	G->supplyCount[estate] = (int)floor(Random() * 7) + 1;
}//randGamestate


/*************************************************************************
* Name: randGamestate
*
* Description: This function generates a random gamestate with 2 to
*	MAX_PLAYERS players, 0 to 15 cards in the deck and discard piles,
*	and 4 to 8 cards in the hand.
*
*************************************************************************/
void randGamestate(struct gameState* G, int* cards, int* gameCards) {
	int p, d, h, dc;
	int numPlayers;

	do {
		numPlayers = rand() % MAX_PLAYERS;
	} while(numPlayers < 2);

	initializeGame(numPlayers, gameCards, 123, G);

	for(p = 0; p < numPlayers; p++) {
		G->deckCount[p] = (rand() % 15);
		G->handCount[p] = (rand() % 4) + 4;
		G->discardCount[p] = (rand() % 13) + 2;

		for(d = 0; d < G->deckCount[p]; d++) {
			G->deck[p][d] = cards[rand() % 17];
		}

		for(h = 0; h < G->handCount[p]; h++) {
			G->hand[p][h] = cards[rand() % 17];
		}

		for(dc = 0; dc < G->discardCount[p]; dc++) {
			G->discard[p][dc] = cards[rand() % 17];
		}

		updateCoins(p, G, 0);
	}
	G->supplyCount[estate] = (rand() % 8);
}//randGamestate

/*************************************************************************
* Name: printGS
*
* Description: 
*
*************************************************************************/
void printGS(struct gameState* G, const char* GS) {
	int i, p;

	printf("****** Printing the gamestate struct for \"%s\" ******\n", GS);
	printf("Num Players: %d\n", G->numPlayers);
	printf("*** Supply Count ***\n");
	for(i = 0; i < treasure_map + 1; i++)
		printf("	Card: %d, Supply Count: %d\n", i, G->supplyCount[i]);
	printf("\n");
	printf("*** Embargo Tokens ***\n");
	for(i = 0; i < treasure_map + 1; i++)
		printf("	Card: %d, Embargo Tokens: %d\n", i, G->embargoTokens[i]);
	printf("\n");
	printf("Outpost Played: %d\n", G->outpostPlayed);
	printf("Outpost Turn: %d\n", G->outpostTurn);
	printf("Whos Turn: %d\n", G->whoseTurn);
	printf("Phase: %d\n", G->phase);
	printf("Num Actions: %d\n", G->numActions);
	printf("Coins: %d\n", G->coins);
	printf("Num Buys: %d\n", G->numBuys);
	printf("\n");

	// Print the hand
	for(p = 0; p < G->numPlayers; p++) {
		printf("*** Hand of Player %d ***\n", p);
		printf("Player %d hand count: %d\n", p, G->handCount[p]);
		for(i = 0; i < G->handCount[p]; i++) {
			printf("	Hand %d: %d\n", i, G->hand[p][i]);
		}
		printf("\n");
	}

	// Print the deck
	for(p = 0; p < G->numPlayers; p++) {
		printf("*** Deck of Player %d ***\n", p);
		printf("Player %d deck count: %d\n", p, G->deckCount[p]);
		for(i = 0; i < G->deckCount[p]; i++) {
			printf("	Deck %d: %d\n", i, G->deck[p][i]);
		}
		printf("\n");
	}

	// Print the discard
	for(p = 0; p < G->numPlayers; p++) {
		printf("*** Discard of Player %d ***\n", p);
		printf("Player %d discard count: %d\n", p, G->discardCount[p]);
		for(i = 0; i < G->discardCount[p]; i++) {
			printf("	Card %d: %d\n", i, G->discard[p][i]);
		}
		printf("\n");
	}

	// Print the played cards counts
	printf("*** Played Cards ***\n");
	printf("Played Cards Count: %d\n", G->playedCardCount);
	for(i = 0; i < G->playedCardCount; i++) 
		printf("	Card %d: %d\n", i, G->playedCards[i]);
	printf("\n");
}//printGS