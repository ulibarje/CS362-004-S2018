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
int compareGameStates(struct gameState* testG, struct gameState* origG) {

	int i, j;
	int stateSuccess = 0;

	// Tier 1
	if(!(testG->numPlayers == origG->numPlayers)) {
		stateSuccess = 1;
		printf("testG->numPlayers: %d, origG->numPlayers: %d\n", testG->numPlayers, origG->numPlayers);
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->supplyCount[i] == origG->supplyCount[i])) {
			stateSuccess = 1;
			printf("testG->supplyCount[%d]: %d, origG->supplyCount[%d]: %d\n", i, testG->supplyCount[i], i, origG->supplyCount[i]);
		}
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->embargoTokens[i] == origG->embargoTokens[i])) {
			stateSuccess = 1;
			printf("testG->embargoTokens[%d]: %d, origG->embargoTokens[%d]: %d\n", i, testG->embargoTokens[i], i, origG->embargoTokens[i]);
		}
	}

	if(!(testG->outpostPlayed == origG->outpostPlayed)) {
		stateSuccess = 1;
		printf("testG->outpostPlayed: %d, origG->outpostPlayed: %d\n", testG->outpostPlayed, origG->outpostPlayed);
	}

	if(!(testG->whoseTurn == origG->whoseTurn)) {
		stateSuccess = 1;
		printf("testG->whoseTurn: %d, origG->whoseTurn: %d\n", testG->whoseTurn, origG->whoseTurn);
	}

	if(!(testG->phase == origG->phase)) {
		stateSuccess = 1;
		printf("testG->phase: %d, origG->phase: %d\n", testG->phase, origG->phase);
	}

	if(!(testG->numActions == origG->numActions)) {
		stateSuccess = 1;
		printf("testG->numActions: %d, origG->numActions: %d\n", testG->numActions, origG->numActions);
	}

	if(!(testG->coins == origG->coins)) {
		stateSuccess = 1;
		printf("testG->coins: %d, origG->coins: %d\n", testG->coins, origG->coins);
	}

	if(!(testG->numBuys == origG->numBuys)) {
		stateSuccess = 1;
		printf("testG->numBuys: %d, origG->numBuys: %d\n", testG->numBuys, origG->numBuys);
	}

	if(!(testG->playedCardCount == origG->playedCardCount)) {
		stateSuccess = 1;
		printf("testG->playedCardCount: %d, origG->playedCardCount: %d\n", testG->playedCardCount, origG->playedCardCount);
	}

	// Tier 2
	if(stateSuccess == 0) {
		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->handCount[i] == origG->handCount[i]))
				stateSuccess = 2;
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == origG->deckCount[i]))
				stateSuccess = 2;
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->discardCount[i] == origG->discardCount[i]))
				stateSuccess = 2;
		}

		// Tier 3
		if(stateSuccess == 0) {
			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->handCount[i]; j++) {
					if(!(testG->hand[i][j] == origG->hand[i][j]))
						stateSuccess = 3;
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == origG->deck[i][j]))
						stateSuccess = 3;
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->discardCount[i]; j++) {
					if(!(testG->discard[i][j] == origG->discard[i][j]))
						stateSuccess = 3;
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


/*************************************************************************
* Name: printTestResult
*
* Description: 
*
*************************************************************************/
void printTestResult(int value) {
	switch(value) {
		case 0:
			printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
			break;
		case 1:
			printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
			break;
		case 2:
			printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
			break;
		case 3:
			printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
			break;
	}//switch
}


void printHand(struct gameState* G) {
	int i;
	for(i = 0; i < G->handCount[G->whoseTurn]; i++) {
		printf("Card %d: %d\n", i, G->hand[G->whoseTurn][i]);
	}
}

/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/

int main() {

	int card, numCards, randCard, passResult, test, toTrash;

	int numTests = 1;
	int allSuccess = 0;
	int seed = 123;
	int numPlayers = 2;
	int player = 0;
	int maxCards = 10;
	struct gameState regGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	srand(time(NULL));

	printf("============= Beginning \"%s\" test =============\n", TESTFUNC);

	/****************************************************************************************/
	/****************************************************************************************/
	for(toTrash = 0; toTrash < 2; toTrash++) {
		for(test = 0; test < numTests; test++) {
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

				for(card = 0; card < numCards; card++) {

					// printf("========== Original Hand =============\n");
					// printHand(&regGame);
					// printf("========== Test Hand =============\n");
					// printHand(&testGame);
					// printf("\n");

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
				    passResult = compareGameStates(&testGame, &regGame);
				    if(passResult != 0) { allSuccess = 1; }
				    else {
				    	printf("discardCard - PASSED: discarded position %d out of %d cards\n", randCard, testGame.handCount[player] + 1);
				    }

					if(PRINT) {
						printTestResult(passResult);
					}
				}
			}
		}
	}

	// All tests have completed, print out if all were successful, or if there was any failures.
	if(allSuccess == 0)
		printf("SUCCESS -- All Tests Passed\n");
	else
		printf("FAIL -- At Least One Case Failed\n");

	return 0;
}