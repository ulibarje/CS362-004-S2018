/* Name: unittest1
 * Author: Jesse Ulibarri
 * CS362 - Assignment 3
 * Test For: "discardCard"
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define PRINT 0

#define TESTFUNC "discardCard"


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
		if(PRINT) {
			printf(GRN "TEST PASSED " RESET);
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 0;
	}
	else {
		if(PRINT) {
			printf(RED "TEST FAILED " RESET);
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 1;
	}
}

/*************************************************************************
* Name: compareGameStates
*
* Description: This function compares the test game state object with 
*	a reference game state object. This function only tests the
*	parameters that are not explicitly tested in the test case. This
*	function serves as a check for the parameters that shouldn't have
*	changed after running the "function-under-test", but this check makes
*	sure of that. The commented out regions are those that are explicitly
*	checked in the test case, and thus, do not need to be tested again.
*
*************************************************************************/
int compareGameStates(struct gameState* testG, struct gameState* refG) {

	int i, j;
	int stateSuccess = 0;

	// Tier 1
	if(!(testG->numPlayers == refG->numPlayers)) {
		stateSuccess = 1;
		printf("FAILED: testG->numPlayers: %d, refG->numPlayers: %d\n", testG->numPlayers, refG->numPlayers);
		
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->supplyCount[i] == refG->supplyCount[i])) {
		stateSuccess = 1;
			printf("FAILED: testG->supplyCount[%d]: %d, refG->supplyCount[%d]: %d\n", i, testG->supplyCount[i], i, refG->supplyCount[i]);
		}
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->embargoTokens[i] == refG->embargoTokens[i])) {
		stateSuccess = 1;
			printf("FAILED: testG->embargoTokens[%d]: %d, refG->embargoTokens[%d]: %d\n", i, testG->embargoTokens[i], i, refG->embargoTokens[i]);
		}
	}

	if(!(testG->outpostPlayed == refG->outpostPlayed)) {
		stateSuccess = 1;
		printf("FAILED: testG->outpostPlayed: %d, refG->outpostPlayed: %d\n", testG->outpostPlayed, refG->outpostPlayed);
	}

	if(!(testG->whoseTurn == refG->whoseTurn)) {
		stateSuccess = 1;
		printf("FAILED: testG->whoseTurn: %d, refG->whoseTurn: %d\n", testG->whoseTurn, refG->whoseTurn);
	}

	if(!(testG->phase == refG->phase)) {
		stateSuccess = 1;
		printf("FAILED: testG->phase: %d, refG->phase: %d\n", testG->phase, refG->phase);
	}

	if(!(testG->numActions == refG->numActions)) {
		stateSuccess = 1;
		printf("FAILED: testG->numActions: %d, refG->numActions: %d\n", testG->numActions, refG->numActions);
	}

	if(!(testG->coins == refG->coins)) {
		stateSuccess = 1;
		printf("FAILED: testG->coins: %d, refG->coins: %d\n", testG->coins, refG->coins);
	}

	if(!(testG->numBuys == refG->numBuys)) {
		stateSuccess = 1;
		printf("FAILED: testG->numBuys: %d, refG->numBuys: %d\n", testG->numBuys, refG->numBuys);
	}

	if(!(testG->playedCardCount == refG->playedCardCount)) {
		stateSuccess = 1;
		printf("FAILED: testG->playedCardCount: %d, refG->playedCardCount: %d\n", testG->playedCardCount, refG->playedCardCount);
	}

	// Tier 2
	if(stateSuccess == 0) {
		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->handCount[i] == refG->handCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->handCount[player = %d]: %d, refG->handCount[player = %d]: %d\n", i, testG->handCount[i], i, refG->handCount[i]);
			}
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == refG->deckCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->deckCount[player = %d]: %d, refG->deckCount[player = %d]: %d\n", i, testG->deckCount[i], i, refG->deckCount[i]);
			}
		}

		for(i = 0; i < testG->playedCardCount; i++) {
			if(!(testG->playedCards[i] == refG->playedCards[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->playedCards[%d]: %d, refG->playedCards[%d]: %d\n", i, testG->playedCards[i], i, refG->playedCards[i]);
			}
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->discardCount[i] == refG->discardCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->discardCount[player = %d]: %d, refG->discardCount[player = %d]: %d\n", i, testG->discardCount[i], i, refG->discardCount[i]);
			}
		}

		// Tier 3
		if(stateSuccess == 0) {
			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->handCount[i]; j++) {
					if(!(testG->hand[i][j] == refG->hand[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->hand[player = %d][%d]: %d, refG->hand[player = %d][%d]: %d\n", i, j, testG->hand[i][j], i, j, refG->hand[i][j]);
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == refG->deck[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->deck[player = %d][%d]: %d, refG->deck[player = %d][%d]: %d\n", i, j, testG->deck[i][j], i, j, refG->deck[i][j]);
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->discardCount[i]; j++) {
					if(!(testG->discard[i][j] == refG->discard[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->discard[player = %d][%d]: %d, refG->discard[player = %d][%d]: %d\n", i, j, testG->discard[i][j], i, j, refG->discard[i][j]);
					}
				}
			}
		}
		else {
			return stateSuccess;
		}
	}
	else {
		return stateSuccess;
	}

	return stateSuccess;
}



/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/

int main() {

	int card, numCards, randCard, toTrash;

	int allSuccess = 0, testSuccess = 0;
	int seed = 123;
	int numPlayers = 2;
	int player = 0;
	int maxCards = 10;
	struct gameState regGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	srand(time(NULL));

	printf("***************************************************************************\n");
	printf("********************** BEGINNING \"%s\" TEST ***********************\n", TESTFUNC);
	printf("***************************************************************************\n\n");

	printf("Description:\n");
	printf("Test initializes a game with a variable number of random cards to start. We start\n");
	printf("with 1 card in hand, run the discard card test, re-initialize game with 2 random\n");
	printf("cards in hand, and re-run the discard test. This is repeated up to 10 cards in\n");
	printf("hand, and then starts over. The second time around, the cards are trashed instead\n");
	printf("of simply discarding them. The test manually discards or trashes the card using\n");
	printf("a reference gamestate, and then compares the entire gamestate to the test gamestate\n");
	printf("that used the \"discardCard\" function\n\n");

	/****************************************************************************************/
	/****************************************************************************************/
	for(toTrash = 0; toTrash < 2; toTrash++) {

		if(toTrash)
			printf("Testing \"%s\" with \"toTrash\" option ON...\n", TESTFUNC);
		else
			printf("Testing \"%s\" with \"toTrash\" option OFF...\n", TESTFUNC);

		for(numCards = 1; numCards <= maxCards; numCards++) {
			// printf("Number of cards: %d, test number: %d, toTrash: %d\n", numCards, test, toTrash);

			memset(&testGame, '\0', sizeof(struct gameState));
			initializeGame(numPlayers, useCards, seed, &testGame);
			testGame.handCount[player] = 0;
			for(card = 0; card < numCards; card++) {
				do {
					randCard = rand() % treasure_map;
				} while(testGame.supplyCount[randCard] != -1);

				testGame.hand[player][card] = randCard;
				testGame.handCount[player]++;
			}
			memcpy(&regGame, &testGame, sizeof(struct gameState));
			testSuccess = 0;

			for(card = 0; card < numCards; card++) {

				randCard = rand() % testGame.handCount[player];
				discardCard(randCard, player, &testGame, toTrash); // The function-under-test

				// Manually discard the same card from our reference game so that we can compare
				// the two gamestates to determine if the function is working correctly.
				if(toTrash == 0) {
		      		regGame.playedCards[regGame.playedCardCount] = regGame.hand[player][randCard]; 
		      		regGame.playedCardCount++;
		      	}

				regGame.hand[player][randCard] = -1;
			  	if (randCard == (regGame.handCount[player] - 1)) {
			      	regGame.handCount[player]--;
			    }
			  	else {
			      regGame.hand[player][randCard] = regGame.hand[player][(regGame.handCount[player] - 1)];
			      regGame.hand[player][regGame.handCount[player] - 1] = -1;
			      regGame.handCount[player]--;
			    }

			    // Compare the two game states and make sure that they are the same
			    if(compareGameStates(&testGame, &regGame)) {
			    	allSuccess = 1;
			    	testSuccess = 1;
			    }
			}

			if(testSuccess == 0) { 
		    	printf("Test with %d cards	--->	PASSED\n", numCards);
		    }
		    else {
		    	printf("Test with %d cards	--->	FAILED\n", numCards);
			}
		}

		printf("\n");
	}

	printf("**************************************************\n");
	// All tests have completed, print out if all were successful, or if there was any failures.
	if(allSuccess == 0)
		printf("\"%s\" unit test		---> 	PASSED\n", TESTFUNC);
	else
		printf("\"%s\" unit test		---> 	FAILED\n", TESTFUNC);
	printf("**************************************************\n");
	printf("\n");

	return 0;
}